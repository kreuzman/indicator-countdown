/*
 * Copyright (C) 2017 Michal Kreuzman
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

#include "settings.h"
#include "countdown.h"
#include "indicator.h"

extern const char *KEY_TIMEOUT;
extern const char *KEY_NOTIFICATON_SUMMARY;
extern const char *KEY_NOTIFICATON_BODY;
extern const char *KEY_NOTIFICATION_VISIBLE;
extern const signed long ONE_SECOND_MICRO;

static Indicator *indicator_countdown;
static Countdown *countdown;

static const char *APP_NAME = "countdown-indicator";
static const char *NOTIFICATION_ICON = "countdown-status";

static void show_notification() {
    notify_init(APP_NAME);

    char *summary = g_settings_get_string(settings_countdown_preset1(), KEY_NOTIFICATON_SUMMARY);
    char *body = g_settings_get_string(settings_countdown_preset1(), KEY_NOTIFICATON_BODY);
    NotifyNotification *notification = notify_notification_new(summary, body, NOTIFICATION_ICON);
    notify_notification_show(notification, NULL);

    notify_uninit();
}

static void on_countdown_tick() {
    indicator_update_elapsed_time(indicator_countdown, countdown_get_elapsed_time(countdown));
}

static void on_countdown_finish() {
    indicator_finish_countdown(indicator_countdown);
    if (g_settings_get_boolean(settings_general(), KEY_NOTIFICATION_VISIBLE)) {
        show_notification();
    }

    countdown_destroy(countdown);
}

static void on_countdown_start() {
    signed long timeout = g_settings_get_int(settings_countdown_preset1(), KEY_TIMEOUT) * ONE_SECOND_MICRO;

    countdown = countdown_new(timeout);
    countdown_tick_callback_add(countdown, on_countdown_tick);
    countdown_finished_callback_add(countdown, on_countdown_finish);

    countdown_start(countdown);
    indicator_set_timeout(indicator_countdown, timeout);
}

static void on_countdown_stop() {
    countdown_reset(countdown);
    countdown_destroy(countdown);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
    settings_init();

    signed long timeout = g_settings_get_int(settings_countdown_preset1(), KEY_TIMEOUT) * ONE_SECOND_MICRO;

    indicator_countdown = indicator_new(timeout);
    indicator_set_start_pressed_callback(indicator_countdown, on_countdown_start);
    indicator_set_stop_pressed_callback(indicator_countdown, on_countdown_stop);

    gtk_main();

    indicator_destroy(indicator_countdown);

    return 0;
}
