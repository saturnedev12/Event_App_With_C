// #include <string.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <mysql/mysql.h>
// #include <gtk/gtk.h>
// #include "get_even_data.h"
// #include "on_event_menu_selected.h"
// #include "ajouter_even.h"
// #include "initialisation.h"
// void run_r_script()
// {
//     char *script_file = "Rscript -e \" curve(sin(x), xlim = c(0, 2 * pi), main = 'Ma courbe', xlab = 'Variable X', ylab = 'Variable Y')\"";
//     char cmd[3000];
//     sprintf(cmd, "Rscript %s", script_file);
//     system(cmd);
// }

// void on_tickets_menu_selected(GtkMenuItem *item, gpointer user_data)
// {

//     // Nettoyer la zone centrale
//     GtkContainer *container = GTK_CONTAINER(user_data);
//     GList *children, *iters;

//     children = gtk_container_get_children(container);
//     for (iters = children; iters != NULL; iters = g_list_next(iters))
//     {
//         if (GTK_IS_MENU_BAR(iters->data))
//             continue;
//         gtk_widget_destroy(GTK_WIDGET(iters->data));
//     }
//     g_list_free(children);
//     // ______________________________________________________

//     MYSQL *con = mysql_init(NULL);
//     if (con == NULL)
//     {
//         fprintf(stderr, "%s\n", mysql_error(con));
//         exit(1);
//     }
//     initialisation(con);
//     GtkListStore *store;
//     GtkTreeIter iter;
//     GtkCellRenderer *renderer;
//     GtkWidget *headerBox, *toolbar, *treeview;
//     // Création d'un tableau de données GTK avec trois colonnes : id, name, age
//     store = gtk_list_store_new(6, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING);

//     // Appel de la fonction pour récupérer les données de la base de données et les ranger dans le tableau de données GTK
//     get_event_data(con, store);

//     // Création d'un widget de type TreeView pour afficher le tableau de données
//     treeview = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
//     g_object_unref(store);
//     /* Add the button to the box */
//     headerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

//     // Création d'un renderer pour afficher les données dans les colonnes du TreeView
//     renderer = gtk_cell_renderer_text_new();

//     // Ajout des colonnes au TreeView
//     gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "ID", renderer, "text", 0, NULL);
//     gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "TITRE", renderer, "text", 1, NULL);
//     gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "DESCRIPTION", renderer, "text", 2, NULL);
//     gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "PLACE", renderer, "text", 3, NULL);
//     gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "PRIX PLACE", renderer, "text", 4, NULL);
//     gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, "DATE", renderer, "text", 5, NULL);

//     // Création de la boîte à outils
//     toolbar = gtk_toolbar_new();
//     gtk_toolbar_set_style(GTK_TOOLBAR(toolbar), GTK_TOOLBAR_ICONS);
//     gtk_container_set_border_width(GTK_CONTAINER(toolbar), 5);
//     gtk_toolbar_set_icon_size(GTK_TOOLBAR(toolbar), GTK_ICON_SIZE_SMALL_TOOLBAR);

//     // Ajout des stocks de boutons à la boîte à outils
//     GtkToolItem *new_tb = gtk_tool_button_new_from_stock(GTK_STOCK_NEW);
//     gtk_toolbar_insert(GTK_TOOLBAR(toolbar), new_tb, -1);

//     GtkToolItem *open_tb = gtk_tool_button_new_from_stock(GTK_STOCK_OPEN);
//     gtk_toolbar_insert(GTK_TOOLBAR(toolbar), open_tb, -1);

//     GtkToolItem *save_tb = gtk_tool_button_new_from_stock(GTK_STOCK_SAVE);
//     gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save_tb, -1);

//     GtkToolItem *sep = gtk_separator_tool_item_new();
//     gtk_toolbar_insert(GTK_TOOLBAR(toolbar), sep, -1);

//     GtkToolItem *cut_tb = gtk_tool_button_new_from_stock(GTK_STOCK_CUT);
//     gtk_toolbar_insert(GTK_TOOLBAR(toolbar), cut_tb, -1);

//     GtkToolItem *copy_tb = gtk_tool_button_new_from_stock(GTK_STOCK_COPY);
//     gtk_toolbar_insert(GTK_TOOLBAR(toolbar), copy_tb, -1);

//     GtkToolItem *paste_tb = gtk_tool_button_new_from_stock(GTK_STOCK_PASTE);
//     gtk_toolbar_insert(GTK_TOOLBAR(toolbar), paste_tb, -1);

//     // Ajout d'un label pour chaque bouton
//     gtk_tool_item_set_tooltip_text(new_tb, "Nouveau");
//     gtk_tool_item_set_tooltip_text(open_tb, "Ouvrir");
//     gtk_tool_item_set_tooltip_text(save_tb, "Enregistrer");
//     gtk_tool_item_set_tooltip_text(cut_tb, "Couper");
//     gtk_tool_item_set_tooltip_text(copy_tb, "Copier");
//     gtk_tool_item_set_tooltip_text(paste_tb, "Coller");
//     g_signal_connect(G_OBJECT(new_tb), "clicked", G_CALLBACK(ajouter_even), NULL);
//     g_signal_connect(G_OBJECT(open_tb), "clicked", G_CALLBACK(run_r_script), NULL);

//     // BOX
//     // Ajouter le bouton à la boîte
//     gtk_box_pack_start(GTK_BOX(headerBox), toolbar, TRUE, TRUE, 0);
//     // gtk_box_pack_start(GTK_BOX(headerBox), button, TRUE, TRUE, 0);
//     gtk_box_pack_start(GTK_BOX(headerBox), treeview, TRUE, TRUE, 0);

//     // GtkWidget *label = gtk_label_new("Bienvenue sur la page d'accueil !");
//     gtk_widget_show_all(headerBox);
//     gtk_container_add(GTK_CONTAINER(user_data), headerBox);
// }