/**
 * \file ajouter_ticket.c
 * \fn ajouter_tickets(GtkWidget *widget, gpointer data)
 * \brief  Fonction qui permet d'ajouter des tickets a la base de donnée
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
#include "../headers/ajouter_ticket.h"
#include "../headers/run_query.h"
#include "../headers/on_ticket_menu_selected.h"
#include "../headers/global.h"

void ajouter_tickets(GtkWidget *widget, gpointer data)
{
    // MYSQL *con = (MYSQL *)data;

    GtkWidget *dialog, *content_area;
    char script[400];
    char script2[400];

    GtkWidget *in_id_event, *in_id_client;
    gint result;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    initialisation(con);
    /* Create the dialog */
    dialog = gtk_dialog_new_with_buttons("Ajouter un ticket",
                                         GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "OK",
                                         GTK_RESPONSE_OK,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);
    // Définir la taille de la boîte de dialogue en pixels
    gtk_window_set_default_size(GTK_WINDOW(dialog), 300, 150);
    /* Create the content area */
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* Add the entries to the content area */
    in_id_event = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(in_id_event), "ID evenement");
    gtk_box_pack_start(GTK_BOX(content_area), in_id_event, TRUE, TRUE, 0);

    in_id_client = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(in_id_client), "ID client");
    gtk_box_pack_start(GTK_BOX(content_area), in_id_client, TRUE, TRUE, 0);

    /* Show the dialog */
    gtk_widget_show_all(dialog);

    /* Run the dialog */
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    /* Get the text from the entries */
    if (result == GTK_RESPONSE_OK)
    {
        const gchar *id_even = gtk_entry_get_text(GTK_ENTRY(in_id_event));
        const gchar *id_client = gtk_entry_get_text(GTK_ENTRY(in_id_client));

        /* Store the text in variables */
        gchar *var1 = g_strdup(id_even);
        gchar *var2 = g_strdup(id_client);

        /* Do something with the variables */
        g_print("Variable 1: %s\n", var1);
        g_print("Variable 2: %s\n", var2);
        snprintf(script2, 300, "UPDATE evenement SET places = places - 1 WHERE id = %s;", var1);
        snprintf(script, 300, "INSERT INTO tickets (eventID, userID, date_creation) VALUES (%s, %s, CURDATE());", var1, var2);

        printf("%s\n", script);
        if (mysql_query(con, script2))
        {
            fprintf(stderr, "%s\n", mysql_error(con));
            mysql_close(con);
        }
        if (mysql_query(con, script))
        {
            fprintf(stderr, "%s\n", mysql_error(con));
            mysql_close(con);
        }

        /* Free the memory */
        g_free(var1);
        g_free(var2);
        on_ticket_menu_selected(NULL, GTK_WINDOW(box));
    }

    /* Destroy the dialog */
    mysql_close(con);
    gtk_widget_destroy(dialog);
}
