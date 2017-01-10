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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>

#include "countdown.h"

static const int ONE_SECOND_MICRO = 1000000;

struct Countdown {
    signed long duration;
    signed long start;
    signed long end;
    unsigned int timeout_id;

    void (*countdown_tick_callback)();
    void (*countdown_finished_callback)();
};

static gboolean time_handler(gpointer data) {
    Countdown *countdown = data;
    countdown->countdown_tick_callback();

    if (countdown_is_finished(countdown)) {
        countdown_reset(countdown);
        countdown->countdown_finished_callback();
        return false;
    }

    return true;
}

Countdown *countdown_new(signed long duration) {
    struct Countdown *result = (struct Countdown *) malloc(sizeof(struct Countdown));
    result->duration = duration;
    result->start = 0;
    result->end = 0;
    result->timeout_id = 0;

    return result;
}

Countdown *countdown_new_from_seconds(signed long duration_seconds) {
    return countdown_new(duration_seconds * ONE_SECOND_MICRO);
}

void countdown_destroy(Countdown *countdown) {
    free(countdown);
}

void countdown_tick_callback_add(Countdown *countdown, void (*tick_callback)()) {
    countdown->countdown_tick_callback = tick_callback;
}

void countdown_finished_callback_add(Countdown *countdown, void (*finished_callback)()) {
    countdown->countdown_finished_callback = finished_callback;
}

void countdown_start(Countdown *countdown) {
    countdown->start = g_get_monotonic_time();
    countdown->end = countdown->start + countdown->duration;
    countdown->timeout_id = g_timeout_add(100, time_handler, countdown);
}

void countdown_reset(Countdown *countdown) {
    if (countdown->timeout_id > 0) {
        g_source_remove(countdown->timeout_id);
        countdown->timeout_id = 0;
    }
}

bool countdown_is_finished(Countdown *countdown) {
    return (countdown->end <= g_get_monotonic_time());
}

signed long countdown_get_duration(Countdown *countdown) {
    return countdown->duration;
}

signed long countdown_get_elapsed_time(Countdown *countdown) {
    if (countdown->start != 0) {
        return g_get_monotonic_time() - countdown->start;
    }

    return 0;
}

unsigned int countdown_get_elapsed_time_percent(Countdown *countdown) {
    return (unsigned int) (countdown_get_elapsed_time(countdown) / (double) countdown_get_duration(countdown) * 100);
}
