/*
 * Copyright (C) 2016 Michal Kreuzman
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

static const unsigned int COUNTDOWN_PICS_COUNT = 60;

static AppIndicator* indicator;
static GSettings *gsettings;
static GtkMenuItem *menuitem_start;
static GtkDialog *about_dialog;
static unsigned int timeout_id;
static signed long start_time = 0;
static unsigned int timeout;

static void start();
static void reset();

extern const gchar *menu_glade;
extern const gchar *menu_glade;

void on_menuitem_start_activate() {
    start();
}

void on_menuitem_reset_activate()
{
    reset();
}

void on_menuitem_about_activate()
{
    gtk_dialog_run(about_dialog);
    gtk_widget_hide(GTK_WIDGET (about_dialog));
}

static void show_notification()
{
    NotifyNotification *notification;
    GError *error = NULL;

    notify_init("countdown-indicator");
    notification = notify_notification_new("Countdown",
                                           "It's time!",
                                           "countdown-status");

    notify_notification_show(notification, &error);
    notify_uninit ();
}

static gboolean time_handler(gpointer data)
{
    signed long actual = g_get_monotonic_time();
    int seconds = timeout * 1000;
    if (actual - start_time > seconds) {
        show_notification();
        reset();

        return FALSE;
    }

    double ratio = (actual - start_time) / (double) seconds;
    int pic = (COUNTDOWN_PICS_COUNT * ratio) + 1;

    char str[12];
    sprintf(str, "countdown-%02d", pic);
    app_indicator_set_icon(indicator, str);

    return TRUE;
}

static void start()
{
    reset();
    start_time = g_get_monotonic_time();
    timeout_id = g_timeout_add(100, time_handler, NULL);
}

static void reset()
{
    if (timeout_id > 0) {
        g_source_remove(timeout_id);
        timeout_id = 0;
    }

    app_indicator_set_icon(indicator, "countdown");
}

static void update_timeout_label () {
    int timeout = timeout = g_settings_get_int(gsettings, "timeout") / 1000;
    int seconds = timeout % 60;
    int minutes = (timeout / 60) % 60;
    int hours = (minutes / 60 / 60) % 60;

    char time_str[9];
    sprintf(time_str, "%02d:%02d:%02d", hours, minutes, seconds);

    gtk_menu_item_set_label(menuitem_start, time_str);
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *indicator_menu;

    gtk_init(&argc, &argv);

    gsettings = g_settings_new("com.kreuzman.indicator.countdown");
    timeout = g_settings_get_int(gsettings, "timeout");

    // Indicator menu
    builder = gtk_builder_new_from_string(menu_glade, -1);
    gtk_builder_connect_signals(builder, NULL);
    indicator_menu = GTK_WIDGET (gtk_builder_get_object(builder, "indicator_menu"));
    menuitem_start = GTK_MENU_ITEM (gtk_builder_get_object(builder, "menuitem_start"));

    update_timeout_label();

    // About dialog
    about_dialog = GTK_DIALOG (gtk_builder_get_object(builder, "about_dialog"));

    // Indicator
    indicator = app_indicator_new("countdown-indicator", "countdown",
                                  APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_attention_icon(indicator, "countdown-indicator");
    app_indicator_set_menu(indicator, GTK_MENU (indicator_menu));

    gtk_main();

    return 0;
}
