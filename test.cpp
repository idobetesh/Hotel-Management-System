#include <iostream>
#include <sqlite3.h>
#include <string>
using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("./DB/hotel-managment-system.db", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        const char* query = "SELECT * FROM Rooms WHERE isTaken = 0 AND class = 'A'";
        rc = sqlite3_exec(db,query,callback,0, &zErrMsg);
    }
    sqlite3_close(db);
}