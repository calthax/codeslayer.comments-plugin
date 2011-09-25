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

#ifndef __COMMENTS_CONFIGURATION_H__
#define	__COMMENTS_CONFIGURATION_H__

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define COMMENTS_CONFIGURATION_TYPE            (comments_configuration_get_type ())
#define COMMENTS_CONFIGURATION(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), COMMENTS_CONFIGURATION_TYPE, CommentsConfiguration))
#define COMMENTS_CONFIGURATION_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), COMMENTS_CONFIGURATION_TYPE, CommentsConfigurationClass))
#define IS_COMMENTS_CONFIGURATION(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), COMMENTS_CONFIGURATION_TYPE))
#define IS_COMMENTS_CONFIGURATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), COMMENTS_CONFIGURATION_TYPE))

typedef struct _CommentsConfiguration CommentsConfiguration;
typedef struct _CommentsConfigurationClass CommentsConfigurationClass;

struct _CommentsConfiguration
{
  GObject parent_instance;
};

struct _CommentsConfigurationClass
{
  GObjectClass parent_class;
};

GType comments_configuration_get_type (void) G_GNUC_CONST;

CommentsConfiguration*  comments_configuration_new                       (void);

const gchar*            comments_configuration_get_file_types  (CommentsConfiguration *configuration);
void                    comments_configuration_set_file_types  (CommentsConfiguration *configuration,
                                                                const gchar           *file_types);
const gchar*            comments_configuration_get_start       (CommentsConfiguration *configuration);
void                    comments_configuration_set_start       (CommentsConfiguration *configuration,
                                                                const gchar           *start);
const gchar*            comments_configuration_get_end         (CommentsConfiguration *configuration);
void                    comments_configuration_set_end         (CommentsConfiguration *configuration,
                                                                const gchar           *end);

G_END_DECLS

#endif /* __COMMENTS_CONFIGURATION_H__ */
