/*
Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gstdio.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

#include <libintl.h>

/* Columns in tree store */

#define PIAG_FILE           0
#define PIAG_NAME           1
#define PIAG_TEXT           2
#define PIAG_STATUS         3
#define PIAG_ENABLED        4

/* Test status */

typedef enum {
     STATUS_NOTRUN,
     STATUS_RUNNING,
     STATUS_PASS,
     STATUS_FAIL
} TEST_STATUS_T;

/* Controls */

static GtkWidget *piag_wd, *piag_nb, *piag_tv, *btn_run, *btn_cancel;

GtkListStore *tests;

static void parse_test_file (gchar *path)
{
    FILE *fp;
    char *line = NULL, *name = NULL, *desc = NULL, *mutext;
    size_t len = 0;
    GtkTreeIter entry;

    fp = fopen (path, "rb");
    if (fp)
    {
        name = NULL;
        desc = NULL;
        while (getline (&line, &len, fp) != -1)
        {
            if (!strncmp (line, "#NAME=", 6)) name = g_strdup (line + 6);
            if (!strncmp (line, "#DESC=", 6)) desc = g_strdup (line + 6);
        }
        if (name && desc)
        {
            mutext = g_strdup_printf (_("<b>%s</b>\n%s"), name, desc);
            gtk_list_store_append (tests, &entry);
            gtk_list_store_set (tests, &entry,
                PIAG_FILE, path,
                PIAG_NAME, name,
                PIAG_TEXT, mutext,
                PIAG_STATUS, STATUS_NOTRUN,
                PIAG_ENABLED, TRUE,
                -1);
            free (mutext);
        }
        if (name) free (name);
        if (desc) free (desc);
        name = NULL;
        desc = NULL;

        free (line);
        fclose (fp);
    }
}

static int find_tests (void)
{
    GDir *data_dir;
    GError *err;
    const gchar *name;
    gchar *path;

    data_dir = g_dir_open (PACKAGE_DATA_DIR, 0, &err);
    if (data_dir)
    {
        while ((name = g_dir_read_name (data_dir)) != NULL)
        {
            if (!g_strcmp0 (name + strlen (name) - 3, ".sh"))
            {
                path = g_strdup_printf ("%s/%s", PACKAGE_DATA_DIR, name);
                parse_test_file (path);
                g_free (path);
            }
        }
        g_dir_close (data_dir);
    }
}

static void run_toggled (GtkCellRendererToggle *cell, gchar *path, gpointer user_data)
{
    GtkTreeIter iter;
    gboolean val;

    gtk_tree_model_get_iter_from_string (GTK_TREE_MODEL (tests), &iter, path);
    gtk_tree_model_get (GTK_TREE_MODEL (tests), &iter, PIAG_ENABLED, &val, -1);
    gtk_list_store_set (tests, &iter, PIAG_ENABLED, 1 - val, -1);
}

static void end_program (GtkWidget *wid, gpointer ptr)
{
    gtk_main_quit ();
}

/* The dialog... */

int main (int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkCellRenderer *crt, *crb;

#ifdef ENABLE_NLS
    setlocale (LC_ALL, "");
    bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);
#endif

    // GTK setup
    gtk_init (&argc, &argv);
    gtk_icon_theme_prepend_search_path (gtk_icon_theme_get_default(), PACKAGE_DATA_DIR);

    // find test files in data directory
    tests = gtk_list_store_new (5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_BOOLEAN);
    find_tests ();

    // build the UI
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, PACKAGE_DATA_DIR "/piagnostics.ui", NULL);

    piag_wd = (GtkWidget *) gtk_builder_get_object (builder, "piag_wd");
    piag_nb = (GtkWidget *) gtk_builder_get_object (builder, "piag_nb");
    piag_tv = (GtkWidget *) gtk_builder_get_object (builder, "piag_tv");
    btn_run = (GtkWidget *) gtk_builder_get_object (builder, "btn_run");
    btn_cancel = (GtkWidget *) gtk_builder_get_object (builder, "btn_cancel");

    gtk_window_set_default_size (GTK_WINDOW (piag_wd), 500, 350);

    // set up tree view
    gtk_tree_view_set_model (GTK_TREE_VIEW (piag_tv), GTK_TREE_MODEL (tests));

    crt = gtk_cell_renderer_text_new ();
    g_object_set (G_OBJECT (crt), "wrap-width", 350, "wrap-mode", PANGO_WRAP_WORD_CHAR, NULL);
    crb = gtk_cell_renderer_toggle_new ();
    g_object_set (G_OBJECT (crb), "activatable", TRUE, NULL);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (piag_tv), 0, _("Test"), crt, "markup", PIAG_TEXT, NULL);
    gtk_tree_view_column_set_expand (gtk_tree_view_get_column (GTK_TREE_VIEW (piag_tv), 0), TRUE);

    gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (piag_tv), 1, _("Run Test?"), crb, "active", PIAG_ENABLED, NULL);
    gtk_tree_view_column_set_expand (gtk_tree_view_get_column (GTK_TREE_VIEW (piag_tv), 1), FALSE);

    // connect button handlers
    g_signal_connect (crb, "toggled", G_CALLBACK (run_toggled), NULL);
    g_signal_connect (piag_wd, "delete-event", G_CALLBACK (end_program), NULL);
    g_signal_connect (btn_cancel, "clicked", G_CALLBACK (end_program), NULL);

    gtk_widget_show (piag_wd);
    g_object_unref (builder);

    // main loop
    gtk_main ();

    return 0;
}
