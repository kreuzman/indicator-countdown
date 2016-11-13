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

#include <stdlib.h>
#include <gtk/gtk.h>

#include "about_dialog.h"

static const gchar *ABOUT_DIALOG_GLADE =
        "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
                "<!-- Generated with glade 3.16.1 -->"
                "<interface>"
                "  <requires lib=\"gtk+\" version=\"3.10\"/>"
                "  <object class=\"GtkAboutDialog\" id=\"about_dialog\">"
                "    <property name=\"can_focus\">False</property>"
                "    <property name=\"halign\">baseline</property>"
                "    <property name=\"title\" translatable=\"yes\">About Countdown Indicator</property>"
                "    <property name=\"window_position\">center</property>"
                "    <property name=\"icon_name\">appointment-soon</property>"
                "    <property name=\"type_hint\">dialog</property>"
                "    <property name=\"gravity\">north-east</property>"
                "    <property name=\"program_name\">Countdown Indicator</property>"
                "    <property name=\"version\">1.0</property>"
                "    <property name=\"copyright\" translatable=\"yes\">@ 2016 Michal Kreuzman</property>"
                "    <property name=\"comments\" translatable=\"yes\">A countdown timer capable of notify after given time passed.</property>"
                "    <property name=\"license\" translatable=\"yes\">This program is free software; you can redistribute it and/or modify"
                "it under the terms of the GNU General Public License as published by"
                "the Free Software Foundation; version 3."

                "This program is distributed in the hope that it will be useful,"
                "but WITHOUT ANY WARRANTY; without even the implied warranty of"
                "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the"
                "GNU General Public License for more details."

                "You should have received a copy of the GNU General Public License"
                "along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.</property>"
                "    <property name=\"authors\">Michal Kreuzman</property>"
                "    <property name=\"logo_icon_name\">appointment-soon</property>"
                "    <property name=\"wrap_license\">True</property>"
                "    <property name=\"license_type\">custom</property>"
                "    <child internal-child=\"vbox\">"
                "      <object class=\"GtkBox\" id=\"aboutdialog-vbox\">"
                "        <property name=\"can_focus\">False</property>"
                "        <property name=\"orientation\">vertical</property>"
                "        <property name=\"spacing\">2</property>"
                "        <property name=\"baseline_position\">top</property>"
                "        <child internal-child=\"action_area\">"
                "          <object class=\"GtkButtonBox\" id=\"aboutdialog-action_area\">"
                "            <property name=\"can_focus\">False</property>"
                "            <property name=\"layout_style\">end</property>"
                "          </object>"
                "          <packing>"
                "            <property name=\"expand\">False</property>"
                "            <property name=\"fill\">True</property>"
                "            <property name=\"pack_type\">end</property>"
                "            <property name=\"position\">0</property>"
                "          </packing>"
                "        </child>"
                "        <child>"
                "          <placeholder/>"
                "        </child>"
                "      </object>"
                "    </child>"
                "  </object>"
                "</interface>";

struct AboutDialog {
    GtkDialog *dialog;
};

AboutDialog *about_dialog_new() {
    struct AboutDialog *about_dialog = (struct AboutDialog *) malloc(sizeof(struct AboutDialog));
    about_dialog->dialog = NULL;
    return about_dialog;
}

void about_dialog_show(AboutDialog *about_dialog) {
    if (about_dialog->dialog != NULL) {
        gtk_window_present(GTK_WINDOW (about_dialog->dialog));
        return;
    }

    GtkBuilder *builder = gtk_builder_new_from_string(ABOUT_DIALOG_GLADE, -1);
    about_dialog->dialog = GTK_DIALOG (gtk_builder_get_object(builder, "about_dialog"));
    g_object_unref(G_OBJECT (builder));

    gtk_dialog_run(about_dialog->dialog);
    gtk_widget_destroy(GTK_WIDGET (about_dialog->dialog));
}
