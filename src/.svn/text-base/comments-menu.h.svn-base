/*
 * Copyright (C) 2010 - Jeff Johnston
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __COMMENTS_MENU_H__
#define	__COMMENTS_MENU_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define COMMENTS_MENU_TYPE            (comments_menu_get_type ())
#define COMMENTS_MENU(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), COMMENTS_MENU_TYPE, CommentsMenu))
#define COMMENTS_MENU_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), COMMENTS_MENU_TYPE, CommentsMenuClass))
#define IS_COMMENTS_MENU(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), COMMENTS_MENU_TYPE))
#define IS_COMMENTS_MENU_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), COMMENTS_MENU_TYPE))

typedef struct _CommentsMenu CommentsMenu;
typedef struct _CommentsMenuClass CommentsMenuClass;

struct _CommentsMenu
{
  GtkMenuItem parent_instance;
};

struct _CommentsMenuClass
{
  GtkMenuItemClass parent_class;

  void (*comment) (CommentsMenu *menu);
  void (*uncomment) (CommentsMenu *menu);
};

GType comments_menu_get_type (void) G_GNUC_CONST;
  
GtkWidget*  comments_menu_new  (GtkAccelGroup *accel_group);
                                            
G_END_DECLS

#endif /* __COMMENTS_MENU_H__ */
