/*
 * Copyright (C) 2010 - Jeff Johnston
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.remove_group_item
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <gdk/gdkkeysyms.h>
#include <codeslayer/codeslayer.h>
#include "comments-menu.h"

static void comments_menu_class_init  (CommentsMenuClass *klass);
static void comments_menu_init        (CommentsMenu      *menu);
static void comments_menu_finalize    (CommentsMenu      *menu);

static void comment_action            (CommentsMenu      *menu);
static void uncomment_action          (CommentsMenu      *menu);
static void add_menu_items            (CommentsMenu      *menu,
                                       GtkWidget         *submenu,
                                       GtkAccelGroup     *accel_group);

enum
{
  COMMENT,
  UNCOMMENT,
  LAST_SIGNAL
};

static guint comments_menu_signals[LAST_SIGNAL] = { 0 };

G_DEFINE_TYPE (CommentsMenu, comments_menu, GTK_TYPE_MENU_ITEM)

static void
comments_menu_class_init (CommentsMenuClass *klass)
{
  comments_menu_signals[COMMENT] =
    g_signal_new ("comment", 
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                  G_STRUCT_OFFSET (CommentsMenuClass, comment),
                  NULL, NULL, 
                  g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

  comments_menu_signals[UNCOMMENT] =
    g_signal_new ("uncomment", 
                  G_TYPE_FROM_CLASS (klass),
                  G_SIGNAL_RUN_LAST | G_SIGNAL_NO_RECURSE | G_SIGNAL_NO_HOOKS,
                  G_STRUCT_OFFSET (CommentsMenuClass, uncomment),
                  NULL, NULL, 
                  g_cclosure_marshal_VOID__VOID, G_TYPE_NONE, 0);

  G_OBJECT_CLASS (klass)->finalize = (GObjectFinalizeFunc) comments_menu_finalize;
}

static void
comments_menu_init (CommentsMenu *menu)
{
  gtk_menu_item_set_label (GTK_MENU_ITEM (menu), "Comments");
}

static void
comments_menu_finalize (CommentsMenu *menu)
{
  G_OBJECT_CLASS (comments_menu_parent_class)->finalize (G_OBJECT (menu));
}

GtkWidget*
comments_menu_new (GtkAccelGroup *accel_group)
{
  GtkWidget *menu;
  GtkWidget *submenu;

  menu = g_object_new (comments_menu_get_type (), NULL);
  
  submenu = gtk_menu_new ();
  gtk_menu_item_set_submenu (GTK_MENU_ITEM (menu), submenu);
  
  add_menu_items (COMMENTS_MENU (menu), submenu, accel_group);

  return menu;
}

static void
add_menu_items (CommentsMenu  *menu,
                GtkWidget     *submenu,
                GtkAccelGroup *accel_group)
{
  GtkWidget *comment_item;
  GtkWidget *uncomment_item;

  comment_item = codeslayer_menu_item_new_with_label ("Comment");
  gtk_widget_add_accelerator (comment_item, "activate", accel_group, 
                              GDK_KEY_slash, GDK_CONTROL_MASK, 
                              GTK_ACCEL_VISIBLE);  
  gtk_menu_shell_append (GTK_MENU_SHELL (submenu), comment_item);

  uncomment_item = codeslayer_menu_item_new_with_label ("Uncomment");
  gtk_widget_add_accelerator (uncomment_item, "activate", accel_group, 
                              GDK_KEY_backslash, GDK_CONTROL_MASK, 
                              GTK_ACCEL_VISIBLE);  
  gtk_menu_shell_append (GTK_MENU_SHELL (submenu), uncomment_item);
  
  g_signal_connect_swapped (G_OBJECT (comment_item), "activate", 
                            G_CALLBACK (comment_action), menu);
   
  g_signal_connect_swapped (G_OBJECT (uncomment_item), "activate", 
                            G_CALLBACK (uncomment_action), menu);
}

static void 
comment_action (CommentsMenu *menu) 
{
  g_signal_emit_by_name ((gpointer) menu, "comment");
}

static void 
uncomment_action (CommentsMenu *menu) 
{
  g_signal_emit_by_name ((gpointer) menu, "uncomment");
}
