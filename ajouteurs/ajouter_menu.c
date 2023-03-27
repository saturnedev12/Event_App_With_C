#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "../headers/initialisation.h"
#include "../headers/ajouter_menu.h"
#include "../headers/run_query.h"
#include "../headers/global.h"
#include "../headers/on_menu_menu_selected.h"

void ajouter_menu(GtkWidget *widget, gpointer data)
{
    // MYSQL *con = (MYSQL *)data;

    GtkWidget *dialog, *content_area;
    char script[400];
    GtkWidget *inIdEvent, *indescription, *inPrix;
    gint result;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    initialisation(con);
    /* Create the dialog */
    dialog = gtk_dialog_new_with_buttons("Ajouter un Menu",
                                         GTK_WINDOW(data),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "OK",
                                         GTK_RESPONSE_OK,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);
    // Définir la taille de la boîte de dialogue en pixels
    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 200);
    /* Create the content area */
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    /* Add the entries to the content area */
    inIdEvent = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(inIdEvent), "ID Evenement");
    gtk_box_pack_start(GTK_BOX(content_area), inIdEvent, TRUE, TRUE, 0);

    indescription = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(indescription), "Description");
    gtk_box_pack_start(GTK_BOX(content_area), indescription, TRUE, TRUE, 0);

    inPrix = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(inPrix), "Prix menu");
    gtk_box_pack_start(GTK_BOX(content_area), inPrix, TRUE, TRUE, 0);

    /* Show the dialog */
    gtk_widget_show_all(dialog);

    /* Run the dialog */
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    /* Get the text from the entries */
    if (result == GTK_RESPONSE_OK)
    {
        const gchar *idEvent = gtk_entry_get_text(GTK_ENTRY(inIdEvent));
        const gchar *description = gtk_entry_get_text(GTK_ENTRY(indescription));
        const gchar *prix = gtk_entry_get_text(GTK_ENTRY(inPrix));

        /* Store the text in variables */
        gchar *var1 = g_strdup(idEvent);
        gchar *var2 = g_strdup(description);
        gchar *var3 = g_strdup(prix);

        /* Do something with the variables */
        g_print("Variable 1: %s\n", var1);
        g_print("Variable 2: %s\n", var2);
        g_print("Variable 3: %s\n", var3);

        snprintf(script, 200, "INSERT INTO menuEvent (idEvent, descriptions, priceMenu) VALUES (%s, \"%s\",%s);", var1, var2, var3);
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
        on_menu_menu_selected(NULL, GTK_WINDOW(box));
    }

    /* Destroy the dialog */
    mysql_close(con);
    gtk_widget_destroy(dialog);
}
