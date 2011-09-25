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

#include "comments-configuration.h"

static void comments_configuration_class_init    (CommentsConfigurationClass *klass);
static void comments_configuration_init          (CommentsConfiguration      *configuration);
static void comments_configuration_finalize      (CommentsConfiguration      *configuration);
static void comments_configuration_get_property  (GObject                    *object, 
                                                  guint                       prop_id,
                                                  GValue                     *value,
                                                  GParamSpec                 *pspec);
static void comments_configuration_set_property  (GObject                    *object, 
                                                  guint                       prop_id,
                                                  const GValue               *value,
                                                  GParamSpec                 *pspec);

#define COMMENTS_CONFIGURATION_GET_PRIVATE(obj) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), COMMENTS_CONFIGURATION_TYPE, CommentsConfigurationPrivate))

typedef struct _CommentsConfigurationPrivate CommentsConfigurationPrivate;

struct _CommentsConfigurationPrivate
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

G_DEFINE_TYPE (CommentsConfiguration, comments_configuration, G_TYPE_OBJECT)
     
static void 
comments_configuration_class_init (CommentsConfigurationClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

  gobject_class->finalize = (GObjectFinalizeFunc) comments_configuration_finalize;

  gobject_class->get_property = comments_configuration_get_property;
  gobject_class->set_property = comments_configuration_set_property;

  g_type_class_add_private (klass, sizeof (CommentsConfigurationPrivate));

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
comments_configuration_init (CommentsConfiguration *configuration)
{
  CommentsConfigurationPrivate *priv;
  priv = COMMENTS_CONFIGURATION_GET_PRIVATE (configuration);
  priv->file_types = NULL;
  priv->start = NULL;
  priv->end = NULL;
}

static void
comments_configuration_finalize (CommentsConfiguration *configuration)
{
  CommentsConfigurationPrivate *priv;
  priv = COMMENTS_CONFIGURATION_GET_PRIVATE (configuration);
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
  G_OBJECT_CLASS (comments_configuration_parent_class)->finalize (G_OBJECT (configuration));
}

static void
comments_configuration_get_property (GObject    *object, 
                                     guint       prop_id,
                                     GValue     *value, 
                                     GParamSpec *pspec)
{
  CommentsConfiguration *configuration;
  CommentsConfigurationPrivate *priv;
  
  configuration = COMMENTS_CONFIGURATION (object);
  priv = COMMENTS_CONFIGURATION_GET_PRIVATE (configuration);

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
comments_configuration_set_property (GObject      *object, 
                                     guint         prop_id,
                                     const GValue *value, 
                                     GParamSpec   *pspec)
{
  CommentsConfiguration *configuration;
  configuration = COMMENTS_CONFIGURATION (object);

  switch (prop_id)
    {
    case PROP_FILE_TYPES:
      comments_configuration_set_file_types (configuration, g_value_get_string (value));
      break;
    case PROP_START:
      comments_configuration_set_start (configuration, g_value_get_string (value));
      break;
    case PROP_END:
      comments_configuration_set_end (configuration, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

CommentsConfiguration*
comments_configuration_new (void)
{
  return COMMENTS_CONFIGURATION (g_object_new (comments_configuration_get_type (), NULL));
}

const gchar*
comments_configuration_get_file_types (CommentsConfiguration *configuration)
{
  return COMMENTS_CONFIGURATION_GET_PRIVATE (configuration)->file_types;
}

void
comments_configuration_set_file_types (CommentsConfiguration *configuration, 
                                       const gchar           *file_types)
{
  CommentsConfigurationPrivate *priv;
  priv = COMMENTS_CONFIGURATION_GET_PRIVATE (configuration);
  if (priv->file_types)
    {
      g_free (priv->file_types);
      priv->file_types = NULL;
    }
  priv->file_types = g_strdup (file_types);
}

const gchar*
comments_configuration_get_start (CommentsConfiguration *configuration)
{
  return COMMENTS_CONFIGURATION_GET_PRIVATE (configuration)->start;
}

void
comments_configuration_set_start (CommentsConfiguration *configuration,
                                  const gchar           *start)
{
  CommentsConfigurationPrivate *priv;
  priv = COMMENTS_CONFIGURATION_GET_PRIVATE (configuration);
  if (priv->start)
    {
      g_free (priv->start);
      priv->start = NULL;
    }
  priv->start = g_strdup (start);
}

const gchar*
comments_configuration_get_end (CommentsConfiguration *configuration)
{
  return COMMENTS_CONFIGURATION_GET_PRIVATE (configuration)->end;
}

void
comments_configuration_set_end (CommentsConfiguration *configuration,
                                const gchar           *end)
{
  CommentsConfigurationPrivate *priv;
  priv = COMMENTS_CONFIGURATION_GET_PRIVATE (configuration);
  if (priv->end)
    {
      g_free (priv->end);
      priv->end = NULL;
    }
  priv->end = g_strdup (end);
}
