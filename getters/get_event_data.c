/**
 * \fn get_event_data(MYSQL *conn, GtkListStore *store)
 * \brief Fonction qui permet de recuperer tout les  evenements a la base de donnée
 *
 * \param conn Objet MySQL
 * \param store Gtk List Store reprensente les ligne du tableau.
 * \return retourne rien.
 */
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "../headers/get_even_data.h"
/**
 * \file get_even_data.c
 * \fn get_event_data(MYSQL *conn, GtkListStore *store)
 * \struct Evenement
 * \brief Objet representant l'entité evenement.
 *
 * Evenement est une structure dans laquel sera
 * modelisé les differentes lignes de la base de donnee
 * de sort a être facilement ajouté aux ligne du tableau
 */
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

void get_event_data(MYSQL *conn, GtkListStore *store)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(conn, "SELECT * FROM evenement");

    res = mysql_use_result(conn);

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
