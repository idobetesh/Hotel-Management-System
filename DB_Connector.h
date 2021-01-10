#pragma once
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Customer.h"
using namespace std;

class DBConnector
{
public:
    // void getConnection();
    // DBConnector(){};
    static int callback(void *NotUsed, int argc, char **argv, char **azColName)
    {
        int i;
        for (i = 0; i < argc; i++)
        {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
        printf("\n");
        return 0;
    }

    void addCustomer(Customer *c)
    {
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;

        rc = sqlite3_open("./DB/hotel-managment-system.db", &db);

        if (rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }
        else
        {
            string n = c->getName();
            string e = c->getEmail();
            string p = c->getPhone();

            fprintf(stderr, "Opened database successfully\n");
            string queryString = "INSERT INTO Customers(name, email, phone) values('" + n + "', '" + e + "', '" + p + "')";
            cout << queryString << endl;
            const char *query = queryString.c_str();
            rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
        }
        sqlite3_close(db);
    }

    void updatePrice(char cls, int newPrice)
    {
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;

        string cls_str = string(1,cls);

        rc = sqlite3_open("./DB/hotel-managment-system.db", &db);

        if (rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return;
        }
        else
        {
            fprintf(stderr, "Opened database successfully\n");
            string queryString = "UPDATE Prices SET class = '" + cls_str + "', price = " + to_string(newPrice) + "WHERE class = '" + cls_str + "'";
            cout << queryString << endl;
            const char *query = queryString.c_str();
            rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
        }
        sqlite3_close(db);
    }
};