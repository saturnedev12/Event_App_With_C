/**
 * \file initialisation.c
 * \fn void initialisation(MYSQL *con)
 * \brief Fonction de création de la base de donnée et des tables si elles n'existent pas encore.
 *
 * \param con Objet MySQL passé en paramettre.
 * \return retourne rien.
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include "headers/run_query.h"
#include "headers/initialisation.h"

void initialisation(MYSQL *con)
{

    if (mysql_real_connect(con, "localhost", "root", "saturne12",
                           "EVENEMENT_DB", 0, NULL, 0) == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }

    run_query(con, "CREATE DATABASE IF NOT EXISTS EVENEMENT_DB ");

    run_query(con, "CREATE TABLE IF NOT EXISTS menuEvent("
                   "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                   "eventID INT NOT NULL,"
                   "menuID INT NOT NULL,"
                   "FOREIGN KEY(eventID) REFERENCES evenement(id),"
                   "FOREIGN KEY(menuID) REFERENCES menu(id)"
                   ")");
    run_query(con, "CREATE TABLE IF NOT EXISTS tickets("
                   "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                   "eventID INT NOT NULL,"
                   "userID INT NOT NULL,"
                   "FOREIGN KEY(eventID) REFERENCES evenement(id),"
                   "FOREIGN KEY(userID) REFERENCES users(id),"
                   "date_creation DATE"
                   ")");
    run_query(con, "CREATE TABLE IF NOT EXISTS menu("
                   "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                   "titre VARCHAR(50),"
                   "descriptions VARCHAR(300)"
                   ")");
    run_query(con, "CREATE TABLE IF NOT EXISTS evenement("
                   "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                   "titre VARCHAR(50),"
                   "descriptions VARCHAR(50),"
                   "places INT,"
                   "priceTicket INT,"
                   "dataTime DATE"
                   ")");
    run_query(con, "CREATE TABLE IF NOT EXISTS users("
                   "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,"
                   "noms VARCHAR(50),"
                   "age SMALLINT"
                   ")");
    // printf("MySQL client version: %s\n", mysql_get_client_info());
}