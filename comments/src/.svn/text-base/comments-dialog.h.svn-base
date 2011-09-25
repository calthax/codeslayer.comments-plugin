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

#ifndef __COMMENTS_DIALOG_H__
#define	__COMMENTS_DIALOG_H__

#include <gtk/gtk.h>
#include <codeslayer/codeslayer.h>
#include <codeslayer/codeslayer-utils.h>

G_BEGIN_DECLS

#define COMMENTS_DIALOG_TYPE            (comments_dialog_get_type ())
#define COMMENTS_DIALOG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), COMMENTS_DIALOG_TYPE, CommentsDialog))
#define COMMENTS_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), COMMENTS_DIALOG_TYPE, CommentsDialogClass))
#define IS_COMMENTS_DIALOG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), COMMENTS_DIALOG_TYPE))
#define IS_COMMENTS_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), COMMENTS_DIALOG_TYPE))

typedef struct _CommentsDialog CommentsDialog;
typedef struct _CommentsDialogClass CommentsDialogClass;

struct _CommentsDialog
{
  GtkDialog parent_instance;
};

struct _CommentsDialogClass
{
  GtkDialogClass parent_class;
};

GType comments_dialog_get_type (void) G_GNUC_CONST;
     
GtkWidget*  comments_dialog_new (CodeSlayer *codeslayer, 
                                 GList      **configurations);

G_END_DECLS

#endif /* __COMMENTS_DIALOG_H__ */
