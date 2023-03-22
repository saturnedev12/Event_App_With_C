#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "../headers/initialisation.h"
#include "../headers/ajouter_even.h"
#include "../headers/run_query.h"

void ajouter_even(GtkWidget *widget, gpointer data)
{
    // MYSQL *con = (MYSQL *)data;

    GtkWidget *dialog, *content_area;
    char script[400];
    GtkWidget *intitre, *indescription, *inplaces, *inpriceTicket, *indataTime;
    gint result;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    initialisation(con);
    /* Create the dialog */
    dialog = gtk_dialog_new_with_buttons("Ajouter un evenement",
                                         GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "OK",
                                         GTK_RESPONSE_OK,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);
    // Définir la taille de la boîte de dialogue en pixels
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 250);
    /* Create the content area */
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* Add the entries to the content area */
    intitre = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(intitre), "Titre");
    gtk_box_pack_start(GTK_BOX(content_area), intitre, TRUE, TRUE, 0);

    indescription = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(indescription), "Description");
    gtk_box_pack_start(GTK_BOX(content_area), indescription, TRUE, TRUE, 0);

    inplaces = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(inplaces), "Nombre places");
    gtk_box_pack_start(GTK_BOX(content_area), inplaces, TRUE, TRUE, 0);

    inpriceTicket = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(inpriceTicket), "Prix tickets");
    gtk_box_pack_start(GTK_BOX(content_area), inpriceTicket, TRUE, TRUE, 0);

    indataTime = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(indataTime), "Date annee-mois-jours");
    gtk_box_pack_start(GTK_BOX(content_area), indataTime, TRUE, TRUE, 0);

    /* Show the dialog */
    gtk_widget_show_all(dialog);

    /* Run the dialog */
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    /* Get the text from the entries */
    if (result == GTK_RESPONSE_OK)
    {
        const gchar *titre = gtk_entry_get_text(GTK_ENTRY(intitre));
        const gchar *description = gtk_entry_get_text(GTK_ENTRY(indescription));
        const gchar *places = gtk_entry_get_text(GTK_ENTRY(inplaces));
        const gchar *priceTicket = gtk_entry_get_text(GTK_ENTRY(inpriceTicket));
        const gchar *dataTime = gtk_entry_get_text(GTK_ENTRY(indataTime));

        /* Store the text in variables */
        gchar *var1 = g_strdup(titre);
        gchar *var2 = g_strdup(description);
        gchar *var3 = g_strdup(places);
        gchar *var4 = g_strdup(priceTicket);
        gchar *var5 = g_strdup(dataTime);

        /* Do something with the variables */
        g_print("Variable 1: %s\n", var1);
        g_print("Variable 2: %s\n", var2);
        g_print("Variable 3: %s\n", var3);
        g_print("Variable 4: %s\n", var4);
        g_print("Variable 5: %s\n", var5);
        snprintf(script, 200, "INSERT INTO evenement (titre, descriptions, places, priceTicket, dataTime) VALUES ('%s', '%s', %s, %s,'%s');", var1, var2, var3, var4, var5);
        printf("%s\n", script);
        if (mysql_query(con, script))
        {
            fprintf(stderr, "%s\n", mysql_error(con));
            mysql_close(con);
        }

        /* Free the memory */
        g_free(var1);
        g_free(var2);
        g_free(var3);
        g_free(var4);
        g_free(var5);
    }

    /* Destroy the dialog */
    mysql_close(con);
    gtk_widget_destroy(dialog);
}
