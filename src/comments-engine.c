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

#include <codeslayer/codeslayer-utils.h>
#include "comments-engine.h"
#include "comments-dialog.h"
#include "comments-configuration.h"

typedef gchar* (*BlockCommentFunc) (gchar        *selection, 
                                    const gchar  *start,
                                    const gchar  *end);

typedef gchar* (*LineCommentFunc)  (gchar        *selection, 
                                    const gchar  *start);

static void comments_engine_class_init           (CommentsEngineClass  *klass);
static void comments_engine_init                 (CommentsEngine       *engine);
static void comments_engine_finalize             (CommentsEngine       *engine);

static void action_callback                      (CommentsEngine       *engine, 
                                                  BlockCommentFunc      blockCommentFunc, 
                                                  LineCommentFunc       lineCommentFunc);

static void comment_action                       (CommentsEngine       *engine);
static void uncomment_action                     (CommentsEngine       *engine);

static CommentsConfiguration* get_configuration  (CommentsEngine       *engine);

static gchar* get_configuration_file_path        (CommentsEngine       *engine);

static gchar* insert_line_comment                (gchar                *selection, 
                                                  const gchar          *start);
static gchar* remove_line_comment                (gchar                *selection,
                                                  const gchar          *start);

static gboolean match_block_comment              (const gchar          *start,
                                                  const gchar          *end);
static gchar* insert_block_comment               (gchar                *selection,
                                                  const gchar          *start,
                                                  const gchar          *end);
static gchar* remove_block_comment               (gchar                *selection, 
                                                  const gchar          *start,
                                                  const gchar          *end);
static GList* get_configurations_deep_copy       (CommentsEngine       *engine);

#define COMMENTS_ENGINE_GET_PRIVATE(obj) \
  (G_TYPE_INSTANCE_GET_PRIVATE ((obj), COMMENTS_ENGINE_TYPE, CommentsEnginePrivate))

typedef struct _CommentsEnginePrivate CommentsEnginePrivate;

struct _CommentsEnginePrivate
{
  CodeSlayer *codeslayer;
  GtkWidget  *menu;
  GList      *configurations;
};

G_DEFINE_TYPE (CommentsEngine, comments_engine, G_TYPE_OBJECT)

static void
comments_engine_class_init (CommentsEngineClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = (GObjectFinalizeFunc) comments_engine_finalize;
  g_type_class_add_private (klass, sizeof (CommentsEnginePrivate));
}

static void
comments_engine_init (CommentsEngine *engine) 
{
  CommentsEnginePrivate *priv;
  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);
  priv->configurations = NULL;
}

static void
comments_engine_finalize (CommentsEngine *engine)
{
  CommentsEnginePrivate *priv;
  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);
  if (priv->configurations != NULL)
    {
      g_list_foreach (priv->configurations, (GFunc) g_object_unref, NULL);
      g_list_free (priv->configurations);
      priv->configurations = NULL;    
    }

  G_OBJECT_CLASS (comments_engine_parent_class)->finalize (G_OBJECT(engine));
}

CommentsEngine*
comments_engine_new (CodeSlayer *codeslayer,
                    GtkWidget  *menu)
{
  CommentsEnginePrivate *priv;
  CommentsEngine *engine;

  engine = COMMENTS_ENGINE (g_object_new (comments_engine_get_type (), NULL));
  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);

  priv->codeslayer = codeslayer;
  priv->menu = menu;
  
  g_signal_connect_swapped (G_OBJECT (menu), "comment",
                            G_CALLBACK (comment_action), engine);
  
  g_signal_connect_swapped (G_OBJECT (menu), "uncomment",
                            G_CALLBACK (uncomment_action), engine);
  
  return engine;
}

void
comments_engine_load_configurations (CommentsEngine *engine)
{
  CommentsEnginePrivate *priv;
  GList *configurations;
  gchar *file_path;

  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);
  
  file_path = get_configuration_file_path (engine);
  configurations = codeslayer_utils_get_gobjects (COMMENTS_CONFIGURATION_TYPE,
                                                  FALSE,
                                                  file_path, 
                                                  "comment",
                                                  "file_types", G_TYPE_STRING, 
                                                  "start", G_TYPE_STRING, 
                                                  "end", G_TYPE_STRING, 
                                                  NULL);
  priv->configurations = configurations;
  g_free (file_path);
}

void
comments_engine_open_dialog (CommentsEngine *engine)
{
  CommentsEnginePrivate *priv;
  GList *copies;
  GtkWidget *dialog;
  gint response;

  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);

  copies = get_configurations_deep_copy (engine);
  dialog = comments_dialog_new (priv->codeslayer, &copies);
    
  response = gtk_dialog_run (GTK_DIALOG (dialog));
    
  if (response == GTK_RESPONSE_OK)
    {
      gchar *file_path;
      
      g_list_foreach (priv->configurations, (GFunc) g_object_unref, NULL);
      g_list_free (priv->configurations);      
      priv->configurations = copies;
      
      file_path = get_configuration_file_path (engine);
      
      g_print ("file_path %s \n", file_path);
      
      codeslayer_utils_save_gobjects (copies,
                                      file_path, 
                                      "comment",
                                      "file_types", G_TYPE_STRING, 
                                      "start", G_TYPE_STRING, 
                                      "end", G_TYPE_STRING, 
                                      NULL);
      g_free (file_path);
    }
  else
    {
      g_list_foreach (copies, (GFunc) g_object_unref, NULL);
      g_list_free (copies);
    }
  
  gtk_widget_destroy (dialog);
}

static gchar*
get_configuration_file_path (CommentsEngine *engine)
{
  CommentsEnginePrivate *priv;
  gchar *folder_path;
  gchar *file_path;
  
  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);

  folder_path = codeslayer_get_configuration_folder_path (priv->codeslayer);  
  file_path = g_build_filename (folder_path, "comments.xml", NULL);
  g_free (folder_path);
  
  return file_path;
}

static GList*
get_configurations_deep_copy (CommentsEngine *engine)
{
  CommentsEnginePrivate *priv;
  GList *results = NULL;
  GList *list;

  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);
  
  list = priv->configurations;

  while (list != NULL)
    {
      CommentsConfiguration *configuration = list->data;
      CommentsConfiguration *copy;
      const gchar *file_types;
      const gchar *start;
      const gchar *end;

      file_types = comments_configuration_get_file_types (configuration);
      start = comments_configuration_get_start (configuration);
      end = comments_configuration_get_end (configuration);
      
      copy = comments_configuration_new ();
      comments_configuration_set_file_types (copy, file_types);
      comments_configuration_set_start (copy, start);
      comments_configuration_set_end (copy, end);
      results = g_list_prepend (results, copy);
      
      list = g_list_next (list);
    }
    
  return results;    
}

static void 
comment_action (CommentsEngine *engine)
{
  action_callback (engine, insert_block_comment, insert_line_comment);
}

static void 
uncomment_action (CommentsEngine *engine)
{
  action_callback (engine, remove_block_comment, remove_line_comment);
}

static void 
action_callback (CommentsEngine    *engine, 
                 BlockCommentFunc  blockCommentFunc, 
                 LineCommentFunc   lineCommentFunc)
{
  CommentsEnginePrivate *priv;
  CodeSlayerEditor *editor;
  GtkTextBuffer *buffer;
  GtkTextMark *insert_mark;
  GtkTextMark *selection_mark;
  GtkTextIter selection_start, selection_end;
  gchar *selection;
  
  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);

  editor = codeslayer_get_active_editor (priv->codeslayer);
  
  if (editor == NULL)
    return;

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (editor));

  insert_mark = gtk_text_buffer_get_insert (buffer);
  selection_mark = gtk_text_buffer_get_selection_bound (buffer);

  gtk_text_buffer_get_iter_at_mark (buffer, &selection_start, insert_mark);
  gtk_text_buffer_get_iter_at_mark (buffer, &selection_end, selection_mark);

  selection = gtk_text_buffer_get_text (buffer, &selection_start, 
                                        &selection_end, FALSE);

  if (codeslayer_utils_has_text (selection))
    {
      CommentsConfiguration *configuration;
      configuration = get_configuration (engine);
      if (configuration != NULL)
        {
          gchar *replace = NULL;
          const gchar *start;
          const gchar *end;
          
          start = comments_configuration_get_start (configuration);
          end = comments_configuration_get_end (configuration);

          if (match_block_comment (start, end))
            {
              g_strchomp (selection);
              replace = blockCommentFunc (selection, start, end);
            }
          else
            {
              replace = lineCommentFunc (selection, start);
            }

          if (replace != NULL)
            {
              gtk_text_buffer_begin_user_action (buffer);
              gtk_text_buffer_delete (buffer, &selection_start, &selection_end);
              gtk_text_buffer_insert (buffer, &selection_start, replace, -1);
              gtk_text_buffer_end_user_action (buffer);
              g_free (replace);
            }    
        }
    }

  if (selection != NULL)
    g_free (selection);
}

static CommentsConfiguration*
get_configuration (CommentsEngine *engine)
{
  CommentsEnginePrivate *priv;
  CodeSlayerDocument *document;
  const gchar *file_path;
  GList *list;

  priv = COMMENTS_ENGINE_GET_PRIVATE (engine);
  
  document = codeslayer_get_active_editor_document (priv->codeslayer);
  file_path = codeslayer_document_get_file_path (document);
  
  list = priv->configurations;
  while (list != NULL)
    {
      CommentsConfiguration *configuration = list->data;
      const gchar *file_types;
      GList *elements;
      
      file_types = comments_configuration_get_file_types (configuration);
      
      elements = codeslayer_utils_string_to_list (file_types);
      
      if (codeslayer_utils_contains_element_with_suffix (elements, file_path))
        {
          g_list_foreach (elements, (GFunc) g_free, NULL);
          g_list_free (elements);
          return configuration;
        }

      g_list_foreach (elements, (GFunc) g_free, NULL);
      g_list_free (elements);
      
      list = g_list_next (list);
    }

    return NULL;
}

static gchar*
insert_line_comment (gchar       *selection, 
                     const gchar *start)
{
  gchar *result;
  GRegex *regex;
  gchar *replacement;

  regex = g_regex_new ("(.*?)([\r\n])", 0, 0, NULL);
  
  replacement = g_strconcat (start, "\\1\\2\\3", NULL);
  
  result = g_regex_replace (regex, selection, -1, 0, replacement, 0, NULL);
  
  g_regex_unref (regex);
  g_free (replacement);

  return result;
}

static gchar*
remove_line_comment (gchar       *selection, 
                     const gchar *start)
{
  gchar *result;
  GRegex *regex;
  gchar *pattern;
  gchar *escape_start;
  
  escape_start = g_regex_escape_string (start, -1);  

  pattern = g_strconcat ("(", escape_start, ")(.*?)([\\r\\n])", NULL);

  regex = g_regex_new (pattern, 0, 0, NULL);

  result = g_regex_replace (regex, selection, -1, 0, "\\2\\3", 0, NULL);
  
  g_regex_unref (regex);
  g_free (pattern);
  g_free (escape_start);

  return result;
}

static gboolean
match_block_comment (const gchar *start,
                     const gchar *end)
{
  if (codeslayer_utils_has_text (start) && 
      codeslayer_utils_has_text (end))
    return TRUE;

  return FALSE;
}

static gchar*
insert_block_comment (gchar       *selection, 
                      const gchar *start,
                      const gchar *end)
{
  gchar *result;
  GRegex *regex;
  gchar *replacement;

  regex = g_regex_new ("^(\\s*)(.{1})((.|[\r\n])*)", 0, 0, NULL);
  
  replacement = g_strconcat ("\\1", start, "\\2\\3", end, "\n", NULL);
  
  result = g_regex_replace (regex, selection, -1, 0, replacement, 0, NULL);
  
  g_regex_unref (regex);
  g_free (replacement);

  return result;
}

static gchar*
remove_block_comment (gchar       *selection, 
                      const gchar *start,
                      const gchar *end)
{
  gchar *result;
  GRegex *regex;
  gchar *pattern;
  gchar *escape_start;
  gchar *escape_end;
  
  escape_start = g_regex_escape_string (start, -1);  
  escape_end = g_regex_escape_string (end, -1);  
    
  pattern = g_strconcat ("^(\\s*)(", escape_start, ")((.|[\\r\\n])*)(", escape_end, ")", NULL);

  regex = g_regex_new (pattern, 0, 0, NULL);
  
  result = g_regex_replace (regex, selection, -1, 0, "\\1\\3\n", 0, NULL);
  
  g_regex_unref (regex);
  g_free (pattern);
  g_free (escape_start);
  g_free (escape_end);

  return result;
}
