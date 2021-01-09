// #include "Manager.h"
// #include "Room.h"
#include <iostream>
#include <sqlite3.h>
#include <string>
using namespace std;

/* void menu()
{
    string pass;
    cout << "Welcome To Hotel California" << endl;
    cout << "if you are a manager enter password, else press *> ";
    cin >> pass;
    if (pass == "123")
    {
        //Manager *m = new Manager("yali", 123);
        cout << "Hello Manager!\nWhat would you like to do?" << endl;
        cout << "1 - Get financial report" << endl;
        cout << "2 - Update prices" << endl;
        cout << "3 - Book a room" << endl;
        cout << "4 - Check-in room" << endl;
        cout << "5 - Check-out room " << endl;
        cout << "6 - Book a room" << endl;
        cout << "6 - Watch available rooms" << endl;
    }
    else
    {
        cout << "Hello!\nWhat would you like to do?" << endl;
        cout << "1- Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room " << endl;
        cout << "4 - Book a room" << endl;
        cout << "5 - Watch available rooms" << endl;
    }
    //swich case
};

int main()
{
    //menu();
    // Room *r = new Room();
    return 0;
} */

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

    rc = sqlite3_open("hotel-managment-system.db", &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        char* query = "SELECT * FROM Orders";
        rc = sqlite3_exec(db,query,callback,0, &zErrMsg);
        cout << rc << endl;

    }
    sqlite3_close(db);
}