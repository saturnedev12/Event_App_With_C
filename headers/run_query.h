#if !defined(RUN_QUERY_H)
#define RUN_QUERY_H
#include <mysql/mysql.h>
#include <string.h>
void run_query(MYSQL *con, char *script);

#endif // RUN_QUERY_H
