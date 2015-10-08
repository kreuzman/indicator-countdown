/*
 * Copyright (C) 2015 Michal Kreuzman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michal Kreuzman <michal.kreuzman@gmail.com>
 */

#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>
#include <libnotify/notify.h>

static unsigned int const COUNTDOWN_PICS_COUNT = 30;

static AppIndicator* indicator;
static unsigned int timeout_id;
static signed long start_time = 0;
static unsigned int timeout_seconds = 120; // TODO must be configurable

static void start (GtkAction* action);
static void reset (GtkAction* action);

static void show_notification() {
    NotifyNotification* notification;
    gboolean success;
    GError* error = NULL;

    notify_init ("countdown-indicator");
    notification = notify_notification_new("Countdown",
                                           "It's time!",
                                           "countdown-status");

    success = notify_notification_show(notification, &error);
    notify_uninit ();
}

static gboolean time_handler(gpointer data) {
    signed long actual = g_get_monotonic_time();
    int seconds = timeout_seconds * 1000 * 1000;
    if (actual - start_time > seconds) {
        show_notification();
        reset(NULL);

        return FALSE;
    }

    double ratio = (actual - start_time) / (double) seconds;
    int pic = (COUNTDOWN_PICS_COUNT * ratio) + 1;

    char str[12];
    sprintf(str, "countdown-%02d", pic);
    app_indicator_set_icon(indicator, str);

    return TRUE;
}

static void start(GtkAction* action)
{
    reset(NULL);
    start_time = g_get_monotonic_time();
    timeout_id = g_timeout_add(100, time_handler, NULL);
}

static void reset(GtkAction* action)
{
    if (timeout_id > 0) {
        g_source_remove(timeout_id);
        timeout_id = 0;
    }
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

    GtkWidget* indicator_menu;
    GtkActionGroup* action_group;
    GtkUIManager* uim;
    GError* error = NULL;

    gtk_init (&argc, &argv);

    action_group = gtk_action_group_new ("AppActions");
    gtk_action_group_add_actions (action_group,
                                  entries, n_entries, NULL);

    uim = gtk_ui_manager_new ();
    gtk_ui_manager_insert_action_group (uim, action_group, 0);

    if (!gtk_ui_manager_add_ui_from_string (uim, ui_info, -1, &error)) {
        g_message ("Failed to build menus: %s\n", error->message);
        g_error_free (error);
        error = NULL;
    }

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
