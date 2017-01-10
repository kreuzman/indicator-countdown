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

#ifndef INDICATOR_COUNTDOWN_PREFERENCES_DIALOG_H
#define INDICATOR_COUNTDOWN_PREFERENCES_DIALOG_H

typedef struct PreferencesDialog PreferencesDialog;

PreferencesDialog *preferences_dialog_new();

void preferences_dialog_destroy(PreferencesDialog *preferences_dialog);

void preferences_dialog_show(PreferencesDialog *preferences_dialog);

void preferences_dialog_close(PreferencesDialog *preferences_dialog);

#endif //INDICATOR_COUNTDOWN_PREFERENCES_DIALOG_H
