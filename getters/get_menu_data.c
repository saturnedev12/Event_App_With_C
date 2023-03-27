//  SELECT * FROM tickets;
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "../headers/get_ticket_data.h"
typedef struct
{
    /* data */
    int id;
    int idEvent;
    char *description;
    int price;

} Evenement;

// Fonction pour récupérer les données de la base de données et les ranger dans un tableau de données GTK
void get_menu_data(MYSQL *conn, GtkListStore *store)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Requête SQL pour récupérer les données de la base de données
    mysql_query(conn, "SELECT * FROM menuEvent");

    res = mysql_use_result(conn);

    // Boucle pour parcourir les résultats de la requête et les stocker dans le tableau de données GTK
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        Evenement event;
        event.id = atoi(row[0]);
        event.idEvent = atoi(row[1]);
        event.description = row[2];
        event.price = atoi(row[3]);

        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, event.id, 1, event.idEvent, 2, event.description, 3, event.price, -1);
    }

    mysql_free_result(res);
    mysql_close(conn);
}
