#include <gtk/gtk.h>
#include <string.h>
#include "headers/on_event_menu_selected.h"
#include "headers/on_users_menu_selected.h"
#include "headers/on_ticket_menu_selected.h"
#include "headers/on_menu_menu_selected.h"

#include "headers/create_menu.h"
void create_menu(GtkWidget *box)
{
    // Création du menu
    GtkWidget *menu_bar = gtk_menu_bar_new();
    gtk_box_pack_start(GTK_BOX(box), menu_bar, FALSE, FALSE, 0);
    // Création de l'élément "Home"
    GtkWidget *menu_item_home = gtk_menu_item_new_with_label("Evenement");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item_home);
    g_signal_connect(menu_item_home, "activate", G_CALLBACK(on_event_menu_selected), box);
    //  Création de l'élément "About"
    GtkWidget *menu_item_users = gtk_menu_item_new_with_label("Users");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item_users);
    g_signal_connect(menu_item_users, "activate", G_CALLBACK(on_users_menu_selected), box);
    //  Création de l'élément "About"
    GtkWidget *menu_item_menus = gtk_menu_item_new_with_label("Menus");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item_menus);
    g_signal_connect(menu_item_menus, "activate", G_CALLBACK(on_menu_menu_selected), box);
    //  Création de l'élément "About"
    GtkWidget *menu_item_tickets = gtk_menu_item_new_with_label("Tickets");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item_tickets);
    g_signal_connect(menu_item_tickets, "activate", G_CALLBACK(on_ticket_menu_selected), box);
    gtk_widget_show_all(menu_bar);
}