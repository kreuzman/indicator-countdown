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
#include "settings.h"

const char *KEY_TIMEOUT = "timeout";
const char *KEY_NOTIFICATON_SUMMARY = "notification-summary";
const char *KEY_NOTIFICATON_BODY = "notification-body";

static const char *GSETTINS_GENERAL_SCHEMA_ID = "com.kreuzman.indicator.countdown.general";
static const char *GSETTINS_PRESET1_SCHEMA_ID = "com.kreuzman.indicator.countdown.presets.preset1";

static GSettings *_general_settings = NULL;
static GSettings *_preset1_settings = NULL;

void settings_init() {
    if (_general_settings == NULL) {
        _general_settings = g_settings_new(GSETTINS_GENERAL_SCHEMA_ID);
    }

    if (_preset1_settings == NULL) {
        _preset1_settings = g_settings_new(GSETTINS_PRESET1_SCHEMA_ID);
    }
}

GSettings *settings_general() {
    return _general_settings;
}

GSettings *settings_countdown_preset1() {
    return _preset1_settings;
}
