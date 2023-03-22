#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "headers/run_query.h"
void run_query(MYSQL *con, char *script)
{
    if (mysql_query(con, script))
    {
        fprintf(stderr, "%s\n", mysql_error(con));
        mysql_close(con);
        exit(1);
    }
}