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

static unsigned int const COUNTDOWN_PICS_COUNT = 60;

static AppIndicator* indicator;
static unsigned int timeout_id;
static signed long start_time = 0;
static unsigned int timeout_seconds = 120;

static void start();
static void reset();

extern const gchar *menu_glade;

void on_menuitem_start_activate() {
    start();
}

void on_menuitem_reset_activate() {
    reset();
}

static void show_notification() {
    NotifyNotification *notification;
    GError *error = NULL;

    notify_init ("countdown-indicator");
    notification = notify_notification_new("Countdown",
                                           "It's time!",
                                           "countdown-status");

    notify_notification_show(notification, &error);
    notify_uninit ();
}

static gboolean time_handler(gpointer data) {
    signed long actual = g_get_monotonic_time();
    int seconds = timeout_seconds * 1000 * 1000;
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

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *indicator_menu;

    gtk_init(&argc, &argv);

    // Indicator menu
    builder = gtk_builder_new_from_string(menu_glade, -1);
    indicator_menu = GTK_WIDGET(gtk_builder_get_object(builder, "indicator_menu"));
    gtk_builder_connect_signals(builder, NULL);

    // Indicator
    indicator = app_indicator_new("countdown-indicator", "countdown",
                                  APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_attention_icon(indicator, "countdown-indicator");
    app_indicator_set_menu(indicator, GTK_MENU (indicator_menu));

    gtk_main();

    return 0;
}
