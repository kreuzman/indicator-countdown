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
#include <gtk/gtk.h>
#include <libappindicator/app-indicator.h>

#include "indicator.h"
#include "about_dialog.h"
#include "preferences_dialog.h"
#include "settings.h"

extern const char *KEY_APPINDICATOR_COUNTDOWN_VISIBLE;
extern const char *KEY_TIMEOUT;
extern const signed long ONE_SECOND_MICRO;

static const char *ICON_NAME = "countdown";

static GtkMenu *menu_init(Indicator *indicator);

static AppIndicator *app_indicator_init(GtkMenu *menu);

static void start_countdown(GtkButton *button, gpointer data);

static void stop_countdown(GtkButton *button, gpointer data);

static void show_preferences_dialog(GtkButton *button, gpointer data);

static void show_about_dialog(GtkButton *button, gpointer data);

static void quit(GtkButton *button, gpointer data);

static const char *resolve_icon_name(unsigned int percent);

static const char *time_as_string(signed long time);

static void timeout_changed(gpointer data);

static void update_start_menu_item_label(Indicator *indicator);

struct Indicator {
    signed long timeout;
    AppIndicator *app_indicator;
    GtkMenu *menu;
    GtkMenuItem *start_menu_item;
    PreferencesDialog *preferences_dialog;
    AboutDialog *about_dialog;

    void (*start_button_press_callback)();

    void (*stop_pressed_callback)();
};

Indicator *indicator_new(signed long timeout) {
    struct Indicator *indicator = (struct Indicator *) malloc(sizeof(struct Indicator));
    indicator->timeout = timeout;

    indicator->preferences_dialog = NULL;
    indicator->about_dialog = NULL;

    indicator->menu = menu_init(indicator);
    indicator->app_indicator = app_indicator_init(indicator->menu);

    indicator->start_button_press_callback = NULL;
    indicator->stop_pressed_callback = NULL;

    return indicator;
}

void indicator_destroy(Indicator *indicator) {
    if (indicator->about_dialog != NULL) {
        about_dialog_destroy(indicator->about_dialog);
    }

    if (indicator->preferences_dialog != NULL) {
        preferences_dialog_destroy(indicator->preferences_dialog);
    }

    gtk_widget_destroy(GTK_WIDGET (indicator->menu));
    g_object_unref(G_OBJECT (indicator->app_indicator));

    free(indicator);
}

void indicator_update_elapsed_time(Indicator *indicator, signed long time_elapsed) {
    unsigned int percent_elapsed = (unsigned int) (time_elapsed / ((double) indicator->timeout) * 100);

    const char *icon_name = resolve_icon_name(percent_elapsed);
    app_indicator_set_icon(indicator->app_indicator, icon_name);
    free((void *) icon_name);

    if (g_settings_get_boolean(settings_general(), KEY_APPINDICATOR_COUNTDOWN_VISIBLE)) {
        const char *indicator_label = time_as_string(indicator->timeout - time_elapsed);
        app_indicator_set_label(indicator->app_indicator, indicator_label, NULL);
        free((void *) indicator_label);
    } else {
        app_indicator_set_label(indicator->app_indicator, NULL, NULL);
    }
}

void indicator_finish_countdown(Indicator *indicator) {
    app_indicator_set_icon(indicator->app_indicator, ICON_NAME);
    app_indicator_set_label(indicator->app_indicator, NULL, NULL);
}

void indicator_set_start_pressed_callback(Indicator *indicator, void (*start_button_press_callback)()) {
    indicator->start_button_press_callback = start_button_press_callback;
}

void indicator_set_stop_pressed_callback(Indicator *indicator, void (*stop_pressed_callback)()) {
    indicator->stop_pressed_callback = stop_pressed_callback;
}

void indicator_set_timeout(Indicator *indicator, signed long timeout) {
    indicator->timeout = timeout;
}

/*
 * UI functions
 */
static AppIndicator *app_indicator_init(GtkMenu *menu) {
    AppIndicator *indicator = app_indicator_new("countdown-indicator", ICON_NAME,
                                                APP_INDICATOR_CATEGORY_APPLICATION_STATUS);
    app_indicator_set_status(indicator, APP_INDICATOR_STATUS_ACTIVE);
    app_indicator_set_attention_icon(indicator, "countdown-indicator");
    app_indicator_set_menu(indicator, menu);

    return indicator;
}

static GtkMenu *menu_init(Indicator *indicator) {
    GtkMenu *indicator_menu = GTK_MENU (gtk_menu_new());
    indicator->start_menu_item = GTK_MENU_ITEM (gtk_menu_item_new_with_label("Start"));
    GtkMenuItem *stop_menu_item = GTK_MENU_ITEM (gtk_menu_item_new_with_label("Stop"));
    GtkMenuItem *preferences_menu_item = GTK_MENU_ITEM (gtk_menu_item_new_with_label("Preferences"));
    GtkMenuItem *about_menu_item = GTK_MENU_ITEM (gtk_menu_item_new_with_label("About"));
    GtkMenuItem *quit_menu_item = GTK_MENU_ITEM (gtk_menu_item_new_with_label("Quit"));

    gtk_menu_shell_append(GTK_MENU_SHELL (indicator_menu), GTK_WIDGET (indicator->start_menu_item));
    gtk_menu_shell_append(GTK_MENU_SHELL (indicator_menu), GTK_WIDGET (stop_menu_item));
    gtk_menu_shell_append(GTK_MENU_SHELL (indicator_menu), GTK_WIDGET (preferences_menu_item));
    gtk_menu_shell_append(GTK_MENU_SHELL (indicator_menu), GTK_WIDGET (about_menu_item));
    gtk_menu_shell_append(GTK_MENU_SHELL (indicator_menu), GTK_WIDGET (quit_menu_item));

    g_signal_connect(indicator->start_menu_item, "activate", G_CALLBACK(start_countdown), indicator);
    g_signal_connect(stop_menu_item, "activate", G_CALLBACK(stop_countdown), indicator);
    g_signal_connect(preferences_menu_item, "activate", G_CALLBACK(show_preferences_dialog), indicator);
    g_signal_connect(about_menu_item, "activate", G_CALLBACK(show_about_dialog), indicator);
    g_signal_connect(quit_menu_item, "activate", G_CALLBACK(quit), indicator);

    gtk_widget_show_all(GTK_WIDGET (indicator_menu));

    update_start_menu_item_label(indicator);

    return indicator_menu;
}

/*
 * Menu callbacks
 */
static void start_countdown(GtkButton *button, gpointer data) {
    Indicator *indicator = data;
    app_indicator_set_icon(indicator->app_indicator, "countdown-00");
    indicator->start_button_press_callback();
}

static void stop_countdown(GtkButton *button, gpointer data) {
    Indicator *indicator = data;
    app_indicator_set_icon(indicator->app_indicator, ICON_NAME);
    app_indicator_set_label(indicator->app_indicator, NULL, NULL);
    indicator->stop_pressed_callback();
}

static void show_preferences_dialog(GtkButton *button, gpointer data) {
    Indicator *indicator = data;
    if (indicator->preferences_dialog == NULL) {
        indicator->preferences_dialog = preferences_dialog_new();
        preferences_dialog_set_timeout_change_callback(indicator->preferences_dialog, timeout_changed, indicator);
    }

    preferences_dialog_show(indicator->preferences_dialog);
}

static void show_about_dialog(GtkButton *button, gpointer data) {
    Indicator *indicator = data;
    if (indicator->about_dialog == NULL) {
        indicator->about_dialog = about_dialog_new();
    }

    about_dialog_show(indicator->about_dialog);
}

static void quit(GtkButton *button, gpointer data) {
    Indicator *indicator = data;

    if (indicator->preferences_dialog != NULL) {
        preferences_dialog_close(indicator->preferences_dialog);
    }

    if (indicator->about_dialog != NULL) {
        about_dialog_close(indicator->about_dialog);
    }

    gtk_main_quit();
}

/*
 * Util functions
 */
static const char *time_as_string(signed long time) {
    time /= 1000000;
    int seconds = (int) (time % 60);
    int minutes = (int) ((time / 60) % 60);
    int hours = (int) ((time / 60 / 60) % 60);

    char *buffer = malloc(9);
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

    return buffer;
}

static const char *resolve_icon_name(unsigned int percent) {
    unsigned int icon_percent = (percent % 2 == 0) ? percent : percent - 1;

    char *buffer = malloc(12);
    sprintf(buffer, "countdown-%02d", icon_percent);

    return buffer;
}

static void timeout_changed(gpointer data) {
    Indicator *indicator = data;
    update_start_menu_item_label(indicator);
}

static void update_start_menu_item_label(Indicator *indicator) {
    signed long timeout = g_settings_get_int(settings_countdown_preset1(), KEY_TIMEOUT) * ONE_SECOND_MICRO;

    const char *start_label = time_as_string(timeout);
    gtk_menu_item_set_label(indicator->start_menu_item, start_label);
    free((void *) start_label);
}
