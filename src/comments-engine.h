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

#ifndef __COMMENTS_ENGINE_H__
#define	__COMMENTS_ENGINE_H__

#include <gtk/gtk.h>
#include <codeslayer/codeslayer.h>

G_BEGIN_DECLS

#define COMMENTS_ENGINE_TYPE            (comments_engine_get_type ())
#define COMMENTS_ENGINE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), COMMENTS_ENGINE_TYPE, CommentsEngine))
#define COMMENTS_ENGINE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), COMMENTS_ENGINE_TYPE, CommentsEngineClass))
#define IS_COMMENTS_ENGINE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), COMMENTS_ENGINE_TYPE))
#define IS_COMMENTS_ENGINE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), COMMENTS_ENGINE_TYPE))

typedef struct _CommentsEngine CommentsEngine;
typedef struct _CommentsEngineClass CommentsEngineClass;

struct _CommentsEngine
{
  GObject parent_instance;
};

struct _CommentsEngineClass
{
  GObjectClass parent_class;
};

GType comments_engine_get_type (void) G_GNUC_CONST;

CommentsEngine*  comments_engine_new           (CodeSlayer     *codeslayer,
                                                GtkWidget      *menu);
                                        
void             comments_engine_load_configs  (CommentsEngine *engine);

void             comments_engine_open_dialog   (CommentsEngine *engine);

G_END_DECLS

#endif /* _COMMENTS_ENGINE_H */
