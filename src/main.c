#include <stdio.h>
#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>

AppIndicator *indicator;
int i = 1;
unsigned int timeoutId;
signed long startTime = 0;
static void start (GtkAction* action);
static void reset (GtkAction* action);
static void show_notification();
static void close_notification();

gboolean time_handler(gpointer data) {
    signed long actual = g_get_monotonic_time();
    int seconds = 120 * 1000 * 1000;
    if (actual - startTime > seconds) {
        i = 1;
        app_indicator_set_icon(indicator, "countdown-30");
        show_notification();

        return FALSE;
    }

    double ratio = (actual - startTime) / (double) seconds;
    int pic = (30 * ratio) + 1;

    char str[12];
    sprintf(str, "countdown-%02d", pic);
    app_indicator_set_icon(indicator, str);

    return TRUE;
}

static void show_notification() {
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new (NULL,
                                     GTK_DIALOG_DESTROY_WITH_PARENT,
                                     GTK_MESSAGE_INFO,
                                     GTK_BUTTONS_CLOSE,
                                     "It's Time!",
                                     NULL);

    g_signal_connect (dialog, "response", G_CALLBACK (close_notification), NULL);

    gtk_widget_show (dialog);
}

static void close_notification(GtkWidget* widget) {
    app_indicator_set_icon(indicator, "countdown");
    gtk_widget_destroy(widget);
}

static void start (GtkAction* action)
{
    startTime = g_get_monotonic_time();
    timeoutId = g_timeout_add(100, time_handler, NULL);
}

static void reset (GtkAction* action)
{
    g_source_remove(timeoutId);
    app_indicator_set_icon(indicator, "countdown");
}

static GtkActionEntry entries[] = {
    { "Start", "start", "_Start", "", "Start", G_CALLBACK (start) },
    { "Reset", "reset", "_Reset", "", "Reset", G_CALLBACK (reset) },
    { "Quit", "application-exit", "_Quit", "", "Quit", G_CALLBACK (gtk_main_quit) },
};
static guint n_entries = G_N_ELEMENTS (entries);

static const gchar *ui_info =
"<ui>"
"  <popup name='IndicatorPopup'>"
"    <menuitem action='Start' />"
"    <menuitem action='Reset' />"
"    <menuitem action='Quit' />"
"  </popup>"
"</ui>";

int main(int argc, char** argv) {

    GtkWidget *indicator_menu;
    GtkActionGroup *action_group;
    GtkUIManager *uim;
    GError *error = NULL;

    gtk_init (&argc, &argv);

    action_group = gtk_action_group_new ("AppActions");
    gtk_action_group_add_actions (action_group,
                                  entries, n_entries, NULL);

    uim = gtk_ui_manager_new ();
    gtk_ui_manager_insert_action_group (uim, action_group, 0);

    if (!gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error))
      {
        g_message ("Failed to build menus: %s\n", error->message);
        g_error_free (error);
        error = NULL;
      }


    /* Indicator */
    indicator = app_indicator_new("countdown-indicator",
                                  "countdown",
                                  APP_INDICATOR_CATEGORY_APPLICATION_STATUS);

    indicator_menu = gtk_ui_manager_get_widget (uim, "/ui/IndicatorPopup");

    app_indicator_set_status (indicator, APP_INDICATOR_STATUS_ACTIVE);
    // app_indicator_set_attention_icon (indicator, "countdown-indicator");

    app_indicator_set_menu (indicator, GTK_MENU (indicator_menu));

    gtk_main ();

    return 0;
}
