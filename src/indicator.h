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
#ifndef INDICATOR_H_
#define INDICATOR_H_

typedef struct Indicator Indicator;

#include <libappindicator/app-indicator.h>
#include <gtk/gtk.h>

Indicator *indicator_new(signed long timeout);

void indicator_destroy(Indicator *indicator);

void indicator_set_start_pressed_callback(Indicator *indicator, void (*on_start)());

void indicator_set_stop_pressed_callback(Indicator *indicator, void (*on_stop)());

void indicator_update_elapsed_time(Indicator *indicator, signed long time_elapsed);

void indicator_finish_countdown(Indicator *indicator);

#endif //INDICATOR_H_
