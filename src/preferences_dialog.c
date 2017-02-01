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
#include <stdlib.h>

#include "preferences_dialog.h"
#include "settings.h"

static const gchar *PREFERENCES_DIALOG_GLADE =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                "<!-- Generated with glade 3.18.3 -->"
                "<interface>"
                "  <requires lib=\"gtk+\" version=\"3.12\"/>"
                "  <object class=\"GtkDialog\" id=\"preferences_dialog\">"
                "    <property name=\"can_focus\">False</property>"
                "    <property name=\"type_hint\">dialog</property>"
                "    <child internal-child=\"vbox\">"
                "      <object class=\"GtkBox\" id=\"dialog-vbox1\">"
                "        <property name=\"can_focus\">False</property>"
                "        <property name=\"orientation\">vertical</property>"
                "        <property name=\"spacing\">2</property>"
                "        <child internal-child=\"action_area\">"
                "          <object class=\"GtkButtonBox\" id=\"dialog-action_area1\">"
                "            <property name=\"can_focus\">False</property>"
                "            <property name=\"layout_style\">end</property>"
                "            <child>"
                "              <placeholder/>"
                "            </child>"
                "            <child>"
                "              <object class=\"GtkButton\" id=\"close_button\">"
                "                <property name=\"label\" translatable=\"yes\">Close</property>"
                "                <property name=\"visible\">True</property>"
                "                <property name=\"can_focus\">True</property>"
                "                <property name=\"receives_default\">True</property>"
                "                <property name=\"xalign\">0.49000000953674316</property>"
                "                <signal name=\"clicked\" handler=\"on_close_button_clicked\" swapped=\"no\"/>"
                "              </object>"
                "              <packing>"
                "                <property name=\"expand\">True</property>"
                "                <property name=\"fill\">True</property>"
                "                <property name=\"position\">1</property>"
                "              </packing>"
                "            </child>"
                "          </object>"
                "          <packing>"
                "            <property name=\"expand\">False</property>"
                "            <property name=\"fill\">False</property>"
                "            <property name=\"position\">0</property>"
                "          </packing>"
                "        </child>"
                "        <child>"
                "          <object class=\"GtkBox\" id=\"box1\">"
                "            <property name=\"visible\">True</property>"
                "            <property name=\"can_focus\">False</property>"
                "            <property name=\"orientation\">vertical</property>"
                "            <child>"
                "              <object class=\"GtkFrame\" id=\"frame3\">"
                "                <property name=\"visible\">True</property>"
                "                <property name=\"can_focus\">False</property>"
                "                <property name=\"margin_right\">5</property>"
                "                <property name=\"label_xalign\">0</property>"
                "                <property name=\"shadow_type\">none</property>"
                "                <child>"
                "                  <object class=\"GtkAlignment\" id=\"alignment3\">"
                "                    <property name=\"visible\">True</property>"
                "                    <property name=\"can_focus\">False</property>"
                "                    <property name=\"left_padding\">12</property>"
                "                    <child>"
                "                      <object class=\"GtkGrid\" id=\"grid1\">"
                "                        <property name=\"visible\">True</property>"
                "                        <property name=\"can_focus\">False</property>"
                "                        <property name=\"row_spacing\">10</property>"
                "                        <property name=\"column_spacing\">5</property>"
                "                        <property name=\"column_homogeneous\">True</property>"
                "                        <child>"
                "                          <object class=\"GtkSpinButton\" id=\"spinbutton1\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">True</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">0</property>"
                "                            <property name=\"top_attach\">1</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkSpinButton\" id=\"spinbutton2\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">True</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">1</property>"
                "                            <property name=\"top_attach\">1</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkSpinButton\" id=\"spinbutton3\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">True</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">2</property>"
                "                            <property name=\"top_attach\">1</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkLabel\" id=\"label4\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">False</property>"
                "                            <property name=\"halign\">start</property>"
                "                            <property name=\"label\" translatable=\"yes\">Hours:</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">0</property>"
                "                            <property name=\"top_attach\">0</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkLabel\" id=\"label5\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">False</property>"
                "                            <property name=\"halign\">start</property>"
                "                            <property name=\"label\" translatable=\"yes\">Minutes:</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">1</property>"
                "                            <property name=\"top_attach\">0</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkLabel\" id=\"label6\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">False</property>"
                "                            <property name=\"halign\">start</property>"
                "                            <property name=\"label\" translatable=\"yes\">Seconds:</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">2</property>"
                "                            <property name=\"top_attach\">0</property>"
                "                          </packing>"
                "                        </child>"
                "                      </object>"
                "                    </child>"
                "                  </object>"
                "                </child>"
                "                <child type=\"label\">"
                "                  <object class=\"GtkLabel\" id=\"label3\">"
                "                    <property name=\"visible\">True</property>"
                "                    <property name=\"can_focus\">False</property>"
                "                    <property name=\"ypad\">5</property>"
                "                    <property name=\"label\" translatable=\"yes\">Remaind me in...</property>"
                "                    <attributes>"
                "                      <attribute name=\"weight\" value=\"bold\"/>"
                "                    </attributes>"
                "                  </object>"
                "                </child>"
                "              </object>"
                "              <packing>"
                "                <property name=\"expand\">False</property>"
                "                <property name=\"fill\">True</property>"
                "                <property name=\"padding\">5</property>"
                "                <property name=\"position\">0</property>"
                "              </packing>"
                "            </child>"
                "            <child>"
                "              <object class=\"GtkFrame\" id=\"frame2\">"
                "                <property name=\"visible\">True</property>"
                "                <property name=\"can_focus\">False</property>"
                "                <property name=\"margin_right\">5</property>"
                "                <property name=\"label_xalign\">0</property>"
                "                <property name=\"shadow_type\">none</property>"
                "                <child>"
                "                  <object class=\"GtkAlignment\" id=\"alignment2\">"
                "                    <property name=\"visible\">True</property>"
                "                    <property name=\"can_focus\">False</property>"
                "                    <property name=\"left_padding\">12</property>"
                "                    <child>"
                "                      <object class=\"GtkGrid\" id=\"grid2\">"
                "                        <property name=\"visible\">True</property>"
                "                        <property name=\"can_focus\">False</property>"
                "                        <property name=\"opacity\">0.96000000089406967</property>"
                "                        <property name=\"hexpand\">True</property>"
                "                        <property name=\"vexpand\">False</property>"
                "                        <property name=\"resize_mode\">immediate</property>"
                "                        <property name=\"row_spacing\">10</property>"
                "                        <property name=\"column_spacing\">5</property>"
                "                        <property name=\"column_homogeneous\">True</property>"
                "                        <child>"
                "                          <object class=\"GtkLabel\" id=\"label7\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">False</property>"
                "                            <property name=\"halign\">start</property>"
                "                            <property name=\"label\" translatable=\"yes\">Autostart:</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">0</property>"
                "                            <property name=\"top_attach\">0</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkLabel\" id=\"label8\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">False</property>"
                "                            <property name=\"halign\">start</property>"
                "                            <property name=\"label\" translatable=\"yes\">Show countdown in notification area:</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">0</property>"
                "                            <property name=\"top_attach\">1</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkLabel\" id=\"label9\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">False</property>"
                "                            <property name=\"halign\">start</property>"
                "                            <property name=\"label\" translatable=\"yes\">Show notifications:</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">0</property>"
                "                            <property name=\"top_attach\">2</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkSwitch\" id=\"switch_autostart\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">True</property>"
                "                            <property name=\"halign\">end</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">1</property>"
                "                            <property name=\"top_attach\">0</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkSwitch\" id=\"switch_show_countdown\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">True</property>"
                "                            <property name=\"halign\">end</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">1</property>"
                "                            <property name=\"top_attach\">1</property>"
                "                          </packing>"
                "                        </child>"
                "                        <child>"
                "                          <object class=\"GtkSwitch\" id=\"switch_show_notifications\">"
                "                            <property name=\"visible\">True</property>"
                "                            <property name=\"can_focus\">True</property>"
                "                            <property name=\"halign\">end</property>"
                "                          </object>"
                "                          <packing>"
                "                            <property name=\"left_attach\">1</property>"
                "                            <property name=\"top_attach\">2</property>"
                "                          </packing>"
                "                        </child>"
                "                      </object>"
                "                    </child>"
                "                  </object>"
                "                </child>"
                "                <child type=\"label\">"
                "                  <object class=\"GtkLabel\" id=\"label2\">"
                "                    <property name=\"visible\">True</property>"
                "                    <property name=\"can_focus\">False</property>"
                "                    <property name=\"ypad\">5</property>"
                "                    <property name=\"label\" translatable=\"yes\">Options</property>"
                "                    <attributes>"
                "                      <attribute name=\"weight\" value=\"bold\"/>"
                "                    </attributes>"
                "                  </object>"
                "                </child>"
                "              </object>"
                "              <packing>"
                "                <property name=\"expand\">False</property>"
                "                <property name=\"fill\">True</property>"
                "                <property name=\"padding\">5</property>"
                "                <property name=\"position\">1</property>"
                "              </packing>"
                "            </child>"
                "            <child>"
                "              <object class=\"GtkFrame\" id=\"frame1\">"
                "                <property name=\"visible\">True</property>"
                "                <property name=\"can_focus\">False</property>"
                "                <property name=\"margin_right\">7</property>"
                "                <property name=\"label_xalign\">0</property>"
                "                <property name=\"shadow_type\">none</property>"
                "                <child>"
                "                  <object class=\"GtkAlignment\" id=\"alignment1\">"
                "                    <property name=\"visible\">True</property>"
                "                    <property name=\"can_focus\">False</property>"
                "                    <property name=\"left_padding\">12</property>"
                "                    <child>"
                "                      <object class=\"GtkTextView\" id=\"textview_notification_text\">"
                "                        <property name=\"visible\">True</property>"
                "                        <property name=\"can_focus\">True</property>"
                "                        <property name=\"pixels_below_lines\">60</property>"
                "                      </object>"
                "                    </child>"
                "                  </object>"
                "                </child>"
                "                <child type=\"label\">"
                "                  <object class=\"GtkLabel\" id=\"label1\">"
                "                    <property name=\"visible\">True</property>"
                "                    <property name=\"can_focus\">False</property>"
                "                    <property name=\"ypad\">5</property>"
                "                    <property name=\"label\" translatable=\"yes\">Notification text</property>"
                "                    <attributes>"
                "                      <attribute name=\"weight\" value=\"bold\"/>"
                "                    </attributes>"
                "                  </object>"
                "                </child>"
                "              </object>"
                "              <packing>"
                "                <property name=\"expand\">False</property>"
                "                <property name=\"fill\">True</property>"
                "                <property name=\"padding\">5</property>"
                "                <property name=\"position\">2</property>"
                "              </packing>"
                "            </child>"
                "          </object>"
                "          <packing>"
                "            <property name=\"expand\">False</property>"
                "            <property name=\"fill\">True</property>"
                "            <property name=\"position\">1</property>"
                "          </packing>"
                "        </child>"
                "      </object>"
                "    </child>"
                "  </object>"
                "</interface>";

extern const char *KEY_TIMEOUT;
extern const char *KEY_NOTIFICATON_BODY;
extern const char *KEY_AUTOSTART;
extern const char *KEY_APPINDICATOR_COUNTDOWN_VISIBLE;
extern const char *KEY_NOTIFICATION_VISIBLE;

static void timeout_sp_value_changed(GtkSpinButton *button, PreferencesDialog *preferences_dialog);

static void update_timeout_spin_buttons(PreferencesDialog *preferences_dialog, int timeout);

struct PreferencesDialog {
    GtkDialog *dialog;
    GtkSpinButton *hours_sb;
    GtkSpinButton *minutes_sb;
    GtkSpinButton *seconds_sb;

    void (*timeout_change_callback)(gpointer data);

    gpointer timeout_change_callback_data;
};

PreferencesDialog *preferences_dialog_new() {
    struct PreferencesDialog *preferences_dialog = (struct PreferencesDialog *) malloc(
            sizeof(struct PreferencesDialog));

    preferences_dialog->dialog = NULL;
    preferences_dialog->timeout_change_callback = NULL;
    preferences_dialog->timeout_change_callback_data = NULL;

    return preferences_dialog;
}

void preferences_dialog_destroy(PreferencesDialog *preferences_dialog) {
    free(preferences_dialog);
}

void preferences_dialog_show(PreferencesDialog *preferences_dialog) {
    if (preferences_dialog->dialog != NULL) {
        gtk_window_present(GTK_WINDOW (preferences_dialog->dialog));
        return;
    }

    GtkBuilder *builder = gtk_builder_new_from_file("../resources/preferences_dialog_gui.glade");
    // GtkBuilder *builder = gtk_builder_new_from_string(PREFERENCES_DIALOG_GLADE, -1);
    preferences_dialog->dialog = GTK_DIALOG (gtk_builder_get_object(builder, "preferences_dialog"));
    preferences_dialog->hours_sb = GTK_SPIN_BUTTON (gtk_builder_get_object(builder, "spinbutton_hours"));
    preferences_dialog->minutes_sb = GTK_SPIN_BUTTON (gtk_builder_get_object(builder, "spinbutton_minutes"));
    preferences_dialog->seconds_sb = GTK_SPIN_BUTTON (gtk_builder_get_object(builder, "spinbutton_seconds"));

    int timeout = g_settings_get_int(settings_countdown_preset1(), KEY_TIMEOUT);
    update_timeout_spin_buttons(preferences_dialog, timeout);

    g_signal_connect(preferences_dialog->seconds_sb, "value-changed", G_CALLBACK(timeout_sp_value_changed),
                     preferences_dialog);
    g_signal_connect(preferences_dialog->minutes_sb, "value-changed", G_CALLBACK(timeout_sp_value_changed),
                     preferences_dialog);
    g_signal_connect(preferences_dialog->hours_sb, "value-changed", G_CALLBACK(timeout_sp_value_changed),
                     preferences_dialog);

    g_settings_bind(
            settings_general(),
            KEY_AUTOSTART,
            gtk_builder_get_object(builder, "switch_autostart"),
            "active",
            G_SETTINGS_BIND_DEFAULT
    );
    g_settings_bind(
            settings_general(),
            KEY_APPINDICATOR_COUNTDOWN_VISIBLE,
            gtk_builder_get_object(builder, "switch_show_countdown"),
            "active",
            G_SETTINGS_BIND_DEFAULT
    );
    g_settings_bind(
            settings_general(),
            KEY_NOTIFICATION_VISIBLE,
            gtk_builder_get_object(builder, "switch_show_notifications"),
            "active",
            G_SETTINGS_BIND_DEFAULT
    );
    g_settings_bind(
            settings_countdown_preset1(),
            KEY_NOTIFICATON_BODY,
            gtk_text_view_get_buffer(GTK_TEXT_VIEW (gtk_builder_get_object(builder, "textview_notification_message"))),
            "text",
            G_SETTINGS_BIND_DEFAULT
    );

    g_object_unref(G_OBJECT (builder));

    gtk_dialog_run(preferences_dialog->dialog);
    gtk_widget_destroy(GTK_WIDGET (preferences_dialog->dialog));
    preferences_dialog->dialog = NULL;
}

void preferences_dialog_close(PreferencesDialog *preferences_dialog) {
    if (preferences_dialog->dialog != NULL) {
        gtk_dialog_response(preferences_dialog->dialog, GTK_RESPONSE_CLOSE);
    }
}

void preferences_dialog_set_timeout_change_callback(PreferencesDialog *pref_dialog, void (*callback)(gpointer),
                                                    gpointer data) {
    pref_dialog->timeout_change_callback = callback;
    pref_dialog->timeout_change_callback_data = data;
}

static void timeout_sp_value_changed(GtkSpinButton *button, PreferencesDialog *preferences_dialog) {
    gdouble seconds = gtk_spin_button_get_value(preferences_dialog->seconds_sb);
    gdouble minutes = gtk_spin_button_get_value(preferences_dialog->minutes_sb);
    gdouble hours = gtk_spin_button_get_value(preferences_dialog->hours_sb);

    int timeout = (int) (seconds + (minutes * 60) + (hours * 60 * 60));
    if (timeout > 86400) {
        timeout = 86400;
    }

    update_timeout_spin_buttons(preferences_dialog, timeout);
    g_settings_set_int(settings_countdown_preset1(), KEY_TIMEOUT, timeout);

    if (preferences_dialog->timeout_change_callback != NULL) {
        preferences_dialog->timeout_change_callback(preferences_dialog->timeout_change_callback_data);
    }
}

static void update_timeout_spin_buttons(PreferencesDialog *preferences_dialog, int timeout) {
    int seconds = timeout % 60;
    int minutes = (timeout / 60) % 60;
    int hours = (timeout / 60 / 60) % 60;

    gtk_spin_button_set_value(preferences_dialog->seconds_sb, seconds);
    gtk_spin_button_set_value(preferences_dialog->minutes_sb, minutes);
    gtk_spin_button_set_value(preferences_dialog->hours_sb, hours);
}
