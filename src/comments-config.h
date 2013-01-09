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

#ifndef __COMMENTS_CONFIG_H__
#define	__COMMENTS_CONFIG_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define COMMENTS_CONFIG_TYPE            (comments_config_get_type ())
#define COMMENTS_CONFIG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), COMMENTS_CONFIG_TYPE, CommentsConfig))
#define COMMENTS_CONFIG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), COMMENTS_CONFIG_TYPE, CommentsConfigClass))
#define IS_COMMENTS_CONFIG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), COMMENTS_CONFIG_TYPE))
#define IS_COMMENTS_CONFIG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), COMMENTS_CONFIG_TYPE))

typedef struct _CommentsConfig CommentsConfig;
typedef struct _CommentsConfigClass CommentsConfigClass;

struct _CommentsConfig
{
  GObject parent_instance;
};

struct _CommentsConfigClass
{
  GObjectClass parent_class;
};

GType comments_config_get_type (void) G_GNUC_CONST;

CommentsConfig*  comments_config_new             (void);

const gchar*     comments_config_get_file_types  (CommentsConfig *config);
void             comments_config_set_file_types  (CommentsConfig *config,
                                                  const gchar    *file_types);
const gchar*     comments_config_get_start       (CommentsConfig *config);
void             comments_config_set_start       (CommentsConfig *config,
                                                  const gchar    *start);
const gchar*     comments_config_get_end         (CommentsConfig *config);
void             comments_config_set_end         (CommentsConfig *config,
                                                  const gchar    *end);

G_END_DECLS

#endif /* __COMMENTS_CONFIG_H__ */
