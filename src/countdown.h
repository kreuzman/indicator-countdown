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
#ifndef COUNTDOWN_H_
#define COUNTDOWN_H_

#include <stdbool.h>

typedef struct Countdown Countdown;

Countdown *countdown_new(signed long duration);

Countdown *countdown_new_from_seconds(signed long duration);

void countdown_destroy(Countdown *countdown);

void countdown_tick_callback_add(Countdown *countdown, void (*tick_callback)());

void countdown_finished_callback_add(Countdown *countdown, void (*finished_callback)());

void countdown_start(Countdown *countdown);

void countdown_reset(Countdown *countdown);

bool countdown_is_finished(Countdown *countdown);

signed long countdown_get_duration(Countdown *countdown);

signed long countdown_get_elapsed_time(Countdown *countdown);

unsigned int countdown_get_elapsed_time_percent(Countdown *countdown);

#endif //COUNTDOWN_H_
