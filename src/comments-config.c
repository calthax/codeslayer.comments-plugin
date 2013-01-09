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

#include "comments-config.h"

static void comments_config_class_init    (CommentsConfigClass *klass);
static void comments_config_init          (CommentsConfig      *config);
static void comments_config_finalize      (CommentsConfig      *config);
static void comments_config_get_property  (GObject             *object, 
                                           guint                prop_id,
                                           GValue              *value,
                                           GParamSpec          *pspec);
static void comments_config_set_property  (GObject             *object, 
                                           guint                prop_id,
                                           const GValue        *value,
                                           GParamSpec          *pspec);

#define COMMENTS_CONFIG_GET_PRIVATE(obj) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), COMMENTS_CONFIG_TYPE, CommentsConfigPrivate))

typedef struct _CommentsConfigPrivate CommentsConfigPrivate;

struct _CommentsConfigPrivate
{
  gchar *file_types;
  gchar *start;
  gchar *end;
};

enum
{
  PROP_0,
  PROP_FILE_TYPES,
  PROP_START,
  PROP_END
};

G_DEFINE_TYPE (CommentsConfig, comments_config, G_TYPE_OBJECT)
     
static void 
comments_config_class_init (CommentsConfigClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = (GObjectFinalizeFunc) comments_config_finalize;

  gobject_class->get_property = comments_config_get_property;
  gobject_class->set_property = comments_config_set_property;

  g_type_class_add_private (klass, sizeof (CommentsConfigPrivate));

  g_object_class_install_property (gobject_class, 
                                   PROP_FILE_TYPES,
                                   g_param_spec_string ("file_types", 
                                                        "File Types",
                                                        "File Types", 
                                                        "",
                                                        G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, 
                                   PROP_START,
                                   g_param_spec_string ("start",
                                                        "Start",
                                                        "Start",
                                                        "",
                                                        G_PARAM_READWRITE));

  g_object_class_install_property (gobject_class, 
                                   PROP_END,
                                   g_param_spec_string ("end",
                                                        "End",
                                                        "End",
                                                        "",
                                                        G_PARAM_READWRITE));
}

static void
comments_config_init (CommentsConfig *config)
{
  CommentsConfigPrivate *priv;
  priv = COMMENTS_CONFIG_GET_PRIVATE (config);
  priv->file_types = NULL;
  priv->start = NULL;
  priv->end = NULL;
}

static void
comments_config_finalize (CommentsConfig *config)
{
  CommentsConfigPrivate *priv;
  priv = COMMENTS_CONFIG_GET_PRIVATE (config);
  if (priv->file_types)
    {
      g_free (priv->file_types);
      priv->file_types = NULL;
    }
  if (priv->start)
    {
      g_free (priv->start);
      priv->start = NULL;
    }
  if (priv->end)
    {
      g_free (priv->end);
      priv->end = NULL;
    }
  G_OBJECT_CLASS (comments_config_parent_class)->finalize (G_OBJECT (config));
}

static void
comments_config_get_property (GObject    *object, 
                              guint       prop_id,
                              GValue     *value, 
                              GParamSpec *pspec)
{
  CommentsConfig *config;
  CommentsConfigPrivate *priv;
  
  config = COMMENTS_CONFIG (object);
  priv = COMMENTS_CONFIG_GET_PRIVATE (config);

  switch (prop_id)
    {
    case PROP_FILE_TYPES:
      g_value_set_string (value, priv->file_types);
      break;
    case PROP_START:
      g_value_set_string (value, priv->start);
      break;
    case PROP_END:
      g_value_set_string (value, priv->end);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
comments_config_set_property (GObject      *object, 
                              guint         prop_id,
                              const GValue *value, 
                              GParamSpec   *pspec)
{
  CommentsConfig *config;
  config = COMMENTS_CONFIG (object);

  switch (prop_id)
    {
    case PROP_FILE_TYPES:
      comments_config_set_file_types (config, g_value_get_string (value));
      break;
    case PROP_START:
      comments_config_set_start (config, g_value_get_string (value));
      break;
    case PROP_END:
      comments_config_set_end (config, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

CommentsConfig*
comments_config_new (void)
{
  return COMMENTS_CONFIG (g_object_new (comments_config_get_type (), NULL));
}

const gchar*
comments_config_get_file_types (CommentsConfig *config)
{
  return COMMENTS_CONFIG_GET_PRIVATE (config)->file_types;
}

void
comments_config_set_file_types (CommentsConfig *config, 
                                const gchar    *file_types)
{
  CommentsConfigPrivate *priv;
  priv = COMMENTS_CONFIG_GET_PRIVATE (config);
  if (priv->file_types)
    {
      g_free (priv->file_types);
      priv->file_types = NULL;
    }
  priv->file_types = g_strdup (file_types);
}

const gchar*
comments_config_get_start (CommentsConfig *config)
{
  return COMMENTS_CONFIG_GET_PRIVATE (config)->start;
}

void
comments_config_set_start (CommentsConfig *config,
                           const gchar    *start)
{
  CommentsConfigPrivate *priv;
  priv = COMMENTS_CONFIG_GET_PRIVATE (config);
  if (priv->start)
    {
      g_free (priv->start);
      priv->start = NULL;
    }
  priv->start = g_strdup (start);
}

const gchar*
comments_config_get_end (CommentsConfig *config)
{
  return COMMENTS_CONFIG_GET_PRIVATE (config)->end;
}

void
comments_config_set_end (CommentsConfig *config,
                         const gchar    *end)
{
  CommentsConfigPrivate *priv;
  priv = COMMENTS_CONFIG_GET_PRIVATE (config);
  if (priv->end)
    {
      g_free (priv->end);
      priv->end = NULL;
    }
  priv->end = g_strdup (end);
}
