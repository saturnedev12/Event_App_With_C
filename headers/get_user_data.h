#if !defined(GET_USER_DATA_H)
#define GET_USER_DATA_H
#include <mysql/mysql.h>
#include <gtk/gtk.h>
void get_user_data(MYSQL *conn, GtkListStore *store);
#endif // GET_EVEN_DATA_H
