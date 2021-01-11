#include "DBConnector.h"
#include <vector>
#include <fstream>
#include <time.h>

//GLOBAL
vector<string> returnData;

DBConnector::DBConnector() {}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        returnData.push_back(argv[i]);
    }
    printf("\n");
    return 0;
}

// int findPriceWithClass(string cls)
// {
//     sqlite3 *db;
//     char *zErrMsg = 0;
//     int rc;

//     rc = sqlite3_open(DB, &db);

//     if (rc)
//     {
//         fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
//         return 0;
//     }
//     else
//     {
//         fprintf(stderr, "Opened database successfully\n");
//         string queryString = "SELECT price FROM Prices WHERE class = '" + cls + "'";
//         cout << queryString << endl;
//         const char *query = queryString.c_str();
//         rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
//     }
//     string priceStr;
//     priceStr = returnData[0];
//     cout << "sdssdsdsdsdsdssdsdsdsd" << returnData[0] << endl;
//     returnData.clear();
//     sqlite3_close(db);
//     return stoi(priceStr);
// }

void DBConnector::addCustomer(Customer *c)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB, &db);

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
    returnData.clear();
    sqlite3_close(db);
}

void DBConnector::updatePrice(char cls, int newPrice)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    string cls_str = string(1, cls);

    rc = sqlite3_open(DB, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        string queryString = "UPDATE Prices SET class = '" + cls_str + "', price = " + to_string(newPrice) + " WHERE class = '" + cls_str + "'";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }
    returnData.clear();
    sqlite3_close(db);
}

void DBConnector::watchAvbRooms()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        string queryString = "SELECT * FROM Rooms WHERE isTaken = 0";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }
    returnData.clear();
    sqlite3_close(db);
}

void DBConnector::checkIn(int roomNumber)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        string queryString = "UPDATE Rooms SET isTaken = 1 WHERE idRoom = " + to_string(roomNumber);
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }
    returnData.clear();
    sqlite3_close(db);
}

void DBConnector::checkOut(int roomNumber)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        string queryString = "UPDATE Rooms SET isTaken = 0 WHERE idRoom = " + to_string(roomNumber);
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }
    returnData.clear();
    sqlite3_close(db);
}

void DBConnector::isCustomerExist(Customer *c)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    string n = c->getName();
    string e = c->getEmail();
    rc = sqlite3_open(DB, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        string queryString = "SELECT * FROM Customers WHERE email = '" + e + "'AND name = '" + n + "'";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, nullptr, 0, &zErrMsg);
        if (rc == 0)
            addCustomer(c);
    }
    returnData.clear();
    sqlite3_close(db);
}

void DBConnector::generateReport()
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///TO DO - logics for a financial report, calculate profits, also decide what to display on such a report.///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    sqlite3 *db;
    time_t currTime;
    ofstream reportFile;
    struct tm *timeInfo;
    char *zErrMsg = 0;
    int rc = sqlite3_open(DB, &db);
    char timeStrBuf[32];   // DD-MMM-YYYY at HH-MM-SS
    char dateForTitle[12]; // DD/MM/YYYY

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        string queryString = "SELECT * FROM Rooms WHERE isTaken = 1";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }
    cout << "return Data: " << endl;
    for (auto a : returnData) // => <id, isTaken, class, ...>
        cout << a << endl;

    memset(timeStrBuf, 0, sizeof(timeStrBuf));
    currTime = time(NULL);
    timeInfo = localtime(&currTime);
    strftime(timeStrBuf, 32, "%d-%b-%Y at %H:%M:%S", timeInfo);
    strftime(dateForTitle, 12, "%d-%b-%Y", timeInfo);

    /* generate specific title by date */
    string title = "Report_";
    string dateForTitleStr(dateForTitle);
    title += dateForTitleStr + ".txt";

    string header = "### This Report generated on ";
    string timeStr(timeStrBuf);
    header += timeStr + " ###\n\nTotal rooms occupied: " + to_string(returnData.size() / 3) + "\nDetails:\n";
    cout << header << endl;

    reportFile.open(title);
    reportFile << header;
    for (auto a : returnData) // => <id, isTaken, class, ...>
        reportFile << "writing some data to report [" << a << "] .\n";

    reportFile.close();
    returnData.clear();
    sqlite3_close(db);
}

/*void DBConnector::bookRoom(char cls,string sDate,string eDate)
{
}
*/