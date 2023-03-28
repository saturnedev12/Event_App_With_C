/**
 * \file ajouter_user.c
 * \fn ajouter_user(GtkWidget *widget, gpointer data)
 * \brief  Fonction qui permet d'ajouter des utilisateur a la base de donnée
 *
 * \param widget Widget parent qui appelle la fonction
 * \param data gpointer pointant vers l'objet passé en paramettre.
 * \return retourne rien.
 */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "../headers/initialisation.h"
#include "../headers/ajouter_user.h"
#include "../headers/run_query.h"
#include "../headers/on_users_menu_selected.h"
#include "../headers/global.h"
// TODO ajouter telephone
void ajouter_user(GtkWidget *widget, gpointer data)
{
    // MYSQL *con = (MYSQL *)data;

    GtkWidget *dialog, *content_area;
    char script[400];
    GtkWidget *innoms, *inage;
    gint result;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    initialisation(con);
    /* Create the dialog */
    dialog = gtk_dialog_new_with_buttons("Ajouter un Utilisateur",
                                         GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "OK",
                                         GTK_RESPONSE_OK,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);
    // Définir la taille de la boîte de dialogue en pixels
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 100);
    /* Create the content area */
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* Add the entries to the content area */
    innoms = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(innoms), "Noms");
    gtk_box_pack_start(GTK_BOX(content_area), innoms, TRUE, TRUE, 0);

    inage = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(inage), "Age");
    gtk_box_pack_start(GTK_BOX(content_area), inage, TRUE, TRUE, 0);

    /* Show the dialog */
    gtk_widget_show_all(dialog);

    /* Run the dialog */
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    /* Get the text from the entries */
    if (result == GTK_RESPONSE_OK)
    {
        const gchar *noms = gtk_entry_get_text(GTK_ENTRY(innoms));
        const gchar *age = gtk_entry_get_text(GTK_ENTRY(inage));

        /* Store the text in variables */
        gchar *var1 = g_strdup(noms);
        gchar *var2 = g_strdup(age);

        /* Do something with the variables */
        g_print("Variable 1: %s\n", var1);
        g_print("Variable 2: %s\n", var2);

        snprintf(script, 200, "INSERT INTO users (noms, age) VALUES (\"%s\", \"%s\");", var1, var2);
        printf("%s\n", script);
        if (mysql_query(con, script))
        {
            fprintf(stderr, "%s\n", mysql_error(con));
            mysql_close(con);
        }

        /* Free the memory */
        g_free(var1);
        g_free(var2);
        on_users_menu_selected(NULL, GTK_WINDOW(box));
    }

    /* Destroy the dialog */
    /* Destroy the dialog */
    mysql_close(con);
    gtk_widget_destroy(dialog);
}
