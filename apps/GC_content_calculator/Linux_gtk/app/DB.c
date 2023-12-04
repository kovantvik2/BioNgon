#include <unistd.h>
#include "sqlite3.h"


void create_db()
{   //

    const char *path_to_db = "../DB/DB.db";
    sqlite3 *db;
    int result  = sqlite3_open(path_to_db, &db);
    sqlite3_close(db);
}






