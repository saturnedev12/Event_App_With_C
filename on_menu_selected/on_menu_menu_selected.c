/**
 * \file on_menu_menu_selected.c
 * \fn on_ticket_menu_selected(GtkMenuItem *item, gpointer user_data)
 * \brief Fonction qui change l'etat de l'application quand on clique sur un item du menu
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
#include "../headers/ajouter_menu.h"
#include "../headers/initialisation.h"
#include "../headers/on_menu_menu_selected.h"
#include "../headers/get_menu_data.h"

void on_menu_menu_selected(GtkMenuItem *item, gpointer user_data)
{

    // Nettoyer la zone centrale
    GtkContainer *container = GTK_CONTAINER(user_data);
    GList *children, *iters;

    children = gtk_container_get_children(container);
    for (iters = children; iters != NULL; iters = g_list_next(iters))
    {
        if (GTK_IS_MENU_BAR(iters->data))
            continue;
        gtk_widget_destroy(GTK_WIDGET(iters->data));
    }
    g_list_free(children);
    // ______________________________________________________

    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    initialisation(con);
    GtkListStore *store;
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkWidget *headerBox, *toolbar, *treeview;
    // Création d'un tableau de données GTK avec trois colonnes : id, name, age
    store = gtk_list_store_new(4, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT);

    // Appel de la fonction pour récupérer les données de la base de données et les ranger dans le tableau de données GTK
    get_menu_data(con, store);

    // Création d'un widget de type TreeView pour afficher le tableau de données
    treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    /* Add the button to the box */
    headerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Création d'un renderer pour afficher les données dans les colonnes du TreeView
    renderer = gtk_cell_renderer_text_new();

    // Ajout des colonnes au TreeView
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "ID", renderer, "text", 0, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "ID EVENT", renderer, "text", 1, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "DESCRIPTION", renderer, "text", 2, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "PRIX", renderer, "text", 3, NULL);

    // Création de la boîte à outils
    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
    gtk_container_set_border_width(GTK_CONTAINER(toolbar), 1);
    gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolbar), GTK_ICON_SIZE_SMALL_TOOLBAR);

    // Ajout des stocks de boutons à la boîte à outils
    GtkToolItem *new_tb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_tb, -1);

    GtkToolItem *del_tb = gtk_tool_button_new_from_stock(GTK_STOCK_DELETE);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), del_tb, -1);

    GtkToolItem *open_tb = gtk_tool_button_new_from_stock(GTK_STOCK_FIND);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open_tb, -1);

    // Ajout d'un label pour chaque bouton
    gtk_tool_item_set_tooltip_text(new_tb, "Creer");
    gtk_tool_item_set_tooltip_text(del_tb, "Supprimer");
    gtk_tool_item_set_tooltip_text(open_tb, "Statistique");
    g_signal_connect(G_OBJECT(new_tb), "clicked", G_CALLBACK(ajouter_menu), NULL);

    // BOX
    // Ajouter le bouton à la boîte
    gtk_box_pack_start(GTK_BOX(headerBox), toolbar, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(headerBox), button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(headerBox), treeview, TRUE, TRUE, 0);

    // GtkWidget *label = gtk_label_new("Bienvenue sur la page d'accueil !");
    gtk_widget_show_all(headerBox);
    gtk_container_add(GTK_CONTAINER(user_data), headerBox);
}