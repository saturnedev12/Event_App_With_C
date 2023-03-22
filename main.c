#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>
#include "headers/initialisation.h"
#include "headers/ajouter_even.h"
#include "headers/create_menu.h"
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    // Création de la fenêtre principale
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Menu avec GTK+");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // Création du conteneur principal
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    create_menu(box);
    // Affichage de la fenêtre
    gtk_widget_show_all(window);

    // Boucle principale de GTK+
    gtk_main();
    perror("UNE ERROR: ");
    return 0;
}
