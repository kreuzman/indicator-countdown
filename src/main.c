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

#include "countdown.h"
#include "indicator.h"

static const char *GSETTINS_SCHEMA_ID = "com.kreuzman.indicator.countdown";
static GSettings *settings;
static Indicator *indicator_countdown;
static Countdown *countdown;

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
    indicator_finish_countdown(indicator_countdown);
}

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);

    settings = g_settings_new(GSETTINS_SCHEMA_ID);
    signed long timout = g_settings_get_int(settings, "timeout");

    countdown = countdown_new_from_seconds(timout);
    countdown_set_tick_callback(countdown, on_countdown_tick);
    countdown_set_finished_callback(countdown, on_countdown_finish);

    indicator_countdown = indicator_new(timout);
    indicator_set_on_start(indicator_countdown, on_countdown_start);
    indicator_set_on_stop(indicator_countdown, on_countdown_stop);

    gtk_main();

    countdown_destroy(countdown);

    return 0;
}
