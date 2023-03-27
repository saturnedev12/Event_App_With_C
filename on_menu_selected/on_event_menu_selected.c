#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <mysql/mysql.h>
#include <gtk/gtk.h>

#include "../headers/get_even_data.h"
#include "../headers/on_event_menu_selected.h"
#include "../headers/ajouter_even.h"
#include "../headers/initialisation.h"
typedef struct
{
    /* data */
    char *date;
    int nb;
} Statis;
void run_r_script()
{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }
    initialisation(con);
    // SELECT dataTime, COUNT(id) FROM evenement GROUP BY dataTime;
    FILE *fp;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Requête SQL pour récupérer les données de la base de données
    mysql_query(con, "SELECT dataTime, COUNT(id) FROM evenement GROUP BY dataTime;");

    res = mysql_use_result(con);
    fp = fopen("toto.txt", "w");

    // Vérifier si le fichier est ouvert avec succès
    if (fp == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier\n");
        exit(1);
    }

    // Boucle pour parcourir les résultats de la requête et les stocker dans le tableau de données GTK
    while ((row = mysql_fetch_row(res)) != NULL)
    {

        printf("%s\n", row[0]);
        fprintf(fp, "%s,%s\n", row[0], row[1]);
        // Statis statis;
        // statis.date = row[0];
        // statis.nb = atoi(row[1]);
        // printf("%s,%s\n", stat.date, stat.nb);
        // fprintf(fp, "%s,%s\n", stat.date, stat.nb);
    }

    mysql_free_result(res);
    mysql_close(con);

    // for (int i = 0; i < 10; i++)
    // {
    //     fprintf(fp, "%d\n", i);
    //     /* code */
    // }
    fclose(fp);

    // sprintf(cmd, "Rscript %s", script_file);
    system("python3 stat_1.py");
}

void on_event_menu_selected(GtkMenuItem *item, gpointer user_data)
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
    store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

    // Appel de la fonction pour récupérer les données de la base de données et les ranger dans le tableau de données GTK
    get_event_data(con, store);

    // Création d'un widget de type TreeView pour afficher le tableau de données
    treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    /* Add the button to the box */
    headerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    // Création d'un renderer pour afficher les données dans les colonnes du TreeView
    renderer = gtk_cell_renderer_text_new();

    // Ajout des colonnes au TreeView
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "ID", renderer, "text", 0, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "TITRE", renderer, "text", 1, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "DESCRIPTION", renderer, "text", 2, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "PLACE", renderer, "text", 3, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "PRIX PLACE", renderer, "text", 4, NULL);
    gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "DATE", renderer, "text", 5, NULL);

    // Création de la boîte à outils
    toolbar = gtk_toolbar_new();
    gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
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

    g_signal_connect(G_OBJECT(new_tb), "clicked", G_CALLBACK(ajouter_even), NULL);
    g_signal_connect(G_OBJECT(open_tb), "clicked", G_CALLBACK(run_r_script), NULL);

    // BOX
    // Ajouter le bouton à la boîte
    gtk_box_pack_start(GTK_BOX(headerBox), toolbar, TRUE, TRUE, 0);
    // gtk_box_pack_start(GTK_BOX(headerBox), button, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(headerBox), treeview, TRUE, TRUE, 0);

    // GtkWidget *label = gtk_label_new("Bienvenue sur la page d'accueil !");
    gtk_widget_show_all(headerBox);
    gtk_container_add(GTK_CONTAINER(user_data), headerBox);
}