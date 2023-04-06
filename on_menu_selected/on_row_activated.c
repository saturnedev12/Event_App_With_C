/**
 * \file on_row_activated.c
 * \fn on_row_activated(GtkMenuItem *item, gpointer user_data)
 * \brief Fonction qui affiche l'evenement, le client, et le prix des paces lié a un ticket
 *
 * \param item Objet GtkMenuItem representant l'Item sur lequel l'on a cliqué.
 * \param user_data Objet gpointer pointant sur l'objet passé en paramettre qui est ici le GtkBox princoipal.
 * \return retourne rien.
 */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "../headers/ajouter_ticket.h"
#include "../headers/initialisation.h"
#include "../headers/on_row_activated.h"
void on_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *col, gpointer userdata)
{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    initialisation(con);
    GtkTreeIter iter;
    GtkTreeModel *model;
    char *script[500];
    char *response[500];
    MYSQL_RES *res;
    MYSQL_ROW row;
    gint result;

    GtkWidget *dialog, *content_area, *label;

    // Récupérer le modèle et l'itérateur pour la ligne activée
    model = gtk_tree_view_get_model(treeview);
    gtk_tree_model_get_iter(model, &iter, path);

    // Récupérer les données de la ligne
    gint col1, col2, col3;
    gchar *col4;
    gtk_tree_model_get(model, &iter, 0, &col1, 1, &col2, 2, &col3, 3, &col4, -1);

    // Afficher les données récupérées
    printf("Colonne 1 : %d\nColonne 2 : %d\nColonne 3 : %d\nColonne 4 : %s\n", col1, col2, col3, col4);
    snprintf(script, 400, "SELECT evenement.descriptions, users.noms, tickets.date_creation, evenement.priceTicket"
                          "  FROM evenement"
                          " JOIN tickets ON evenement.id = tickets.eventID"
                          " JOIN users ON tickets.userID = users.id"
                          " WHERE tickets.id = %d;",
             (int)col1);
    printf("%s\n", script);
    mysql_query(con, script);
    res = mysql_use_result(con);
    // Boucle pour parcourir les résultats de la requête et les stocker dans le tableau de données GTK
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        // descriptions              | noms        | date_creation | prix
        printf("Description : %s\nClient : %s\nDate de creation : %s\nPrix Ticket :%sF\n", row[0], row[1], row[2], row[3]);
        snprintf(response, 400, "Description : %s\nClient : %s\nDate de creation : %s\nPrix Ticket :%sF\n", row[0], row[1], row[2], row[3]);
    }

    dialog = gtk_dialog_new_with_buttons("Information du Ticket",
                                         GTK_WINDOW(userdata),
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "OK",
                                         GTK_RESPONSE_OK,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         NULL);
    // Définir la taille de la boîte de dialogue en pixels
    gtk_window_set_default_size(GTK_WINDOW(dialog), 200, 150);
    label = gtk_label_new(response);
    /* Create the content area */
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    gtk_container_add(GTK_CONTAINER(content_area), label);
    /* Show the dialog */
    gtk_widget_show_all(dialog);
    result = gtk_dialog_run(GTK_DIALOG(dialog));

    if (result == GTK_RESPONSE_OK || result == GTK_RESPONSE_CANCEL)
    {
        /* code */
        gtk_widget_destroy(dialog);
    }

    mysql_free_result(res);
    mysql_close(con);
    // Libérer la mémoire allouée pour les chaînes de caractères
    g_free(col4);
}
