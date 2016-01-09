/*
 * Copyright (C) 2015 Michal Kreuzman
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

const gchar *menu_glade =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<!-- Generated with glade 3.16.1 -->"
"<interface>"
"  <requires lib=\"gtk+\" version=\"3.10\"/>"
"  <object class=\"GtkMenuBar\" id=\"menubar\">"
"    <property name=\"visible\">True</property>"
"    <property name=\"can_focus\">False</property>"
"    <child>"
"      <object class=\"GtkMenuItem\" id=\"menuitem\">"
"        <property name=\"visible\">True</property>"
"        <property name=\"can_focus\">False</property>"
"        <property name=\"label\" translatable=\"yes\">Countdown</property>"
"        <property name=\"use_underline\">True</property>"
"        <child type=\"submenu\">"
"          <object class=\"GtkMenu\" id=\"indicator_menu\">"
"            <property name=\"visible\">True</property>"
"            <property name=\"can_focus\">False</property>"
"            <child>"
"              <object class=\"GtkMenuItem\" id=\"menuitem_start\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"label\" translatable=\"yes\">Start</property>"
"                <signal name=\"activate\" handler=\"on_menuitem_start_activate\" swapped=\"no\"/>"
"              </object>"
"            </child>"
"            <child>"
"              <object class=\"GtkMenuItem\" id=\"menuitem_reset\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"label\" translatable=\"yes\">Reset</property>"
"                <signal name=\"activate\" handler=\"on_menuitem_reset_activate\" swapped=\"no\"/>"
"              </object>"
"            </child>"
"            <child>"
"              <object class=\"GtkSeparatorMenuItem\" id=\"menuitem_separator1\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"              </object>"
"            </child>"
"            <child>"
"              <object class=\"GtkMenuItem\" id=\"menuitem_timeout\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"sensitive\">False</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"margin_top\">6</property>"
"                <property name=\"resize_mode\">queue</property>"
"                <property name=\"label\" translatable=\"yes\">00:00</property>"
"              </object>"
"            </child>"
"            <child>"
"              <object class=\"GtkSeparatorMenuItem\" id=\"menuitem_separator2\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"              </object>"
"            </child>"
"            <child>"
"              <object class=\"GtkMenuItem\" id=\"menuitem_about\">"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"label\" translatable=\"yes\">About</property>"
"                <property name=\"use_underline\">True</property>"
"              </object>"
"            </child>"
"            <child>"
"              <object class=\"GtkImageMenuItem\" id=\"menuitem_quit\">"
"                <property name=\"label\">gtk-quit</property>"
"                <property name=\"visible\">True</property>"
"                <property name=\"can_focus\">False</property>"
"                <property name=\"use_underline\">True</property>"
"                <property name=\"use_stock\">True</property>"
"                <signal name=\"activate\" handler=\"gtk_main_quit\" swapped=\"no\"/>"
"              </object>"
"            </child>"
"          </object>"
"        </child>"
"      </object>"
"    </child>"
"  </object>"
"</interface>";
