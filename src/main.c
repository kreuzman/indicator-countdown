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
#include <libnotify/notify.h>

#include "countdown.h"
#include "indicator.h"

static const char *GSETTINS_SCHEMA_ID = "com.kreuzman.indicator.countdown";
static GSettings *settings;
static Indicator *indicator_countdown;
static Countdown *countdown;

static void show_notification();

static void on_countdown_start() {
    countdown_start(countdown);
}

static void on_countdown_stop() {
    countdown_reset(countdown);
}

static void on_countdown_tick() {
    indicator_update_elapsed_time(indicator_countdown, countdown_get_elapsed_time_percent(countdown));
}

static void on_countdown_finish() {
    show_notification();
    indicator_finish_countdown(indicator_countdown);
}

static void show_notification() {
    notify_init("countdown-indicator");

    GError *error = NULL;
    NotifyNotification *notification = notify_notification_new("Countdown", "It's time!", "countdown-status");
    notify_notification_show(notification, &error);

    notify_uninit();
}

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    settings = g_settings_new(GSETTINS_SCHEMA_ID);
    signed long timout = g_settings_get_int(settings, "timeout");

    countdown = countdown_new_from_seconds(timout);
    countdown_tick_callback_add(countdown, on_countdown_tick);
    countdown_finished_callback_add(countdown, on_countdown_finish);

    indicator_countdown = indicator_new(timout);
    indicator_start_pressed_callback_add(indicator_countdown, on_countdown_start);
    indicator_stop_pressed_callback(indicator_countdown, on_countdown_stop);

    gtk_main();

    countdown_destroy(countdown);
    indicator_destroy(indicator_countdown);

    return 0;
}
