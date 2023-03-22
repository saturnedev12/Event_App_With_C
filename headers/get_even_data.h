#if !defined(GET_EVEN_DATA_H)
#define GET_EVEN_DATA_H
#include <mysql/mysql.h>
#include <gtk/gtk.h>
void get_event_data(MYSQL *conn, GtkListStore *store);
#endif // GET_EVEN_DATA_H
