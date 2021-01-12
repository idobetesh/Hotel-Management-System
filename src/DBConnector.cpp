#include "DBConnector.h"

//GLOBAL
vector<string> returnData;
vector<int> returnedRooms;
unordered_map<string, int> priceMap;

DBConnector::DBConnector() {}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        returnData.push_back(argv[i] - '0');
    }
    printf("\n");
    return 0;
}

static int callbackRooms(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        returnedRooms.push_back(stoi(argv[i]));
    }
    printf("\n");
    return 0;
}

/* void DBConnector::refreshPriceMap() 
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
        string queryString = "SELECT price FROM Prices";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }

    priceMap["A"] = stoi(returnData[0]);
    priceMap["B"] = stoi(returnData[1]);
    priceMap["C"] = stoi(returnData[2]);


    returnData.clear();
    sqlite3_close(db);
} */

void insideRefreshPriceMap() // should call before getReport() from main!
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
        string queryString = "SELECT price FROM Prices";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }

    /* update priceMap */
    priceMap["A"] = stoi(returnData[0]);
    priceMap["B"] = stoi(returnData[1]);
    priceMap["C"] = stoi(returnData[2]);

    for (auto a : priceMap)
        cout << "[" << a.first << "] => " << a.second << endl;

    returnData.clear();
    sqlite3_close(db);
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
    insideRefreshPriceMap();
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

    insideRefreshPriceMap();
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
        string queryString = "SELECT idRoom, class FROM Rooms WHERE isTaken = 1";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
    }

    /* returnData vector format => <id, class, id, class, ...> */
    memset(timeStrBuf, 0, sizeof(timeStrBuf));
    currTime = time(NULL);
    timeInfo = localtime(&currTime);
    strftime(timeStrBuf, 32, "%d-%b-%Y at %H:%M:%S", timeInfo);
    strftime(dateForTitle, 12, "%d-%b-%Y", timeInfo);

    /* generate specific title by date */
    string title = "Report_";
    string dateForTitleStr(dateForTitle);
    title += dateForTitleStr + ".txt";

    string header = "*** This Report generated on ";
    string timeStr(timeStrBuf);
    int occupiedRooms = returnData.size() / 2;
    header += timeStr + " ***\n\n* Total rooms occupied: " + to_string(occupiedRooms) + "\n\n* Details:\n";

    reportFile.open(title);
    reportFile << header;

    int profit = 0;
    string reportContent = "";
    for (int i = 0; i < returnData.size(); i++)
    {
        if (i % 2 == 0)
        {
            reportContent += "\t- Room No." + returnData[i] + " is occupied ";
        }
        else
        {
            reportContent += "| class: " + returnData[i] + "\n";
            cout << "price: " << priceMap[returnData[i]] << endl;
            profit += priceMap[returnData[i]];
            cout << "profit: " << profit << endl;
        }
    }
    reportFile << reportContent;
    reportFile << "\n\n* Profit:\n\t- Total Profit: " << profit << "₪\n\t- Average profit per room: " << double(profit / occupiedRooms) << "₪";

    reportFile.close();
    returnData.clear();
    sqlite3_close(db);
}

bool DBConnector::bookRoom(string cls, string sDate, string eDate, Customer *c)
{
    // 1. check if there are available rooms from the class between sDate and eDate.
    // 2. if true - book the room, print to the screen that the room is booked and return true
    // 3. else - print why no, and return false.

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB, &db);

    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }
    else
    {
        fprintf(stderr, "Opened database successfully\n");
        string queryString = "SELECT idRoom FROM Rooms WHERE class = '" + cls + "'";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callbackRooms, 0, &zErrMsg);
        sqlite3_close(db);

        for (int i = 0; i < returnedRooms.size(); i++)
        {
            cout << "Current room id is - " << returnedRooms[i] << endl;
            rc = sqlite3_open(DB, &db);
            queryString = "SELECT * FROM Dates WHERE idRoom = " + to_string(returnedRooms[i]) + " AND arrivalDate >= '" + sDate + "' AND depatureDate <= '" + eDate + "'";
            cout << queryString << endl;
            const char *query = queryString.c_str();
            rc = sqlite3_exec(db, query, callback, 0, &zErrMsg);
            if (rc == 0)
            {
                // book the room
                cout << "No room is taken at the wanted dates" << endl;
                returnedRooms.clear();
                return true;
            }
            else
            {
                cout << rc << endl;
                cout << "You need to fix your request" << endl;
                // print "Room is no available, try inserting other parameters"
            }
            sqlite3_close(db);
        }
        returnedRooms.clear();
        return false;
    }
    sqlite3_close(db);
}
