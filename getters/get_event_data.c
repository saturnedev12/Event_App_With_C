#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "../headers/get_even_data.h"
typedef struct
{
    /* data */
    int id;
    char *titre;
    char *descriptions;
    int places;
    int priceTicket;
    char *dataTime;

} Evenement;

// Fonction pour récupérer les données de la base de données et les ranger dans un tableau de données GTK
void get_event_data(MYSQL *conn, GtkListStore *store)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Requête SQL pour récupérer les données de la base de données
    mysql_query(conn, "SELECT * FROM evenement");

    res = mysql_use_result(conn);

    // Boucle pour parcourir les résultats de la requête et les stocker dans le tableau de données GTK
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        Evenement event;
        event.id = atoi(row[0]);
        event.titre = row[1];
        event.descriptions = row[2];
        event.places = atoi(row[3]);
        event.priceTicket = atoi(row[4]);
        event.dataTime = row[5];

        GtkTreeIter iter;
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, 0, event.id, 1, event.titre, 2, event.descriptions, 3, event.places, 4, event.priceTicket, 5, event.dataTime, -1);
    }

    mysql_free_result(res);
    mysql_close(conn);
}
