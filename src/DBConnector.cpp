#include "DBConnector.h"

//GLOBAL
vector<string> returnData;
vector<int> returnedRooms;
int customerID = 0;
int orderID = 0;
unordered_map<string, int> priceMap;

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

static int tmpcallback(void *NotUsed, int argc, char **argv, char **azColName)
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

static int callbackCustomerID(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        customerID = stoi(argv[i]);
    }
    return 0;
}

static int callbackOrderID(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        orderID = stoi(argv[i]);
    }
    return 0;
}

int datesDiff(string date_s, string date_e)
{
    //  YYYY-MM-DD
    int year_e = stoi(date_s.substr(0, 4));
    int year_s = stoi(date_e.substr(0, 4));
    int month_s = stoi(date_s.substr(5, 2));
    int month_e = stoi(date_e.substr(5, 2));
    int day_s = stoi(date_s.substr(8, 2));
    int day_e = stoi(date_e.substr(8, 2));

    // cout << "test: " << year_e << "-" << month_e << "-" << day_e << endl;
    time_t timeA, timeB;
    struct tm tA, tB, *tptr;

    time(&timeA);
    time(&timeB);
    tptr = localtime(&timeA);
    tA = *tptr;
    tptr = localtime(&timeB);
    tB = *tptr;

    tA.tm_mday = day_s;
    tA.tm_mon = month_s;
    tA.tm_year = year_s;

    tB.tm_mday = day_e;
    tB.tm_mon = month_e;
    tB.tm_year = year_e;

    timeA = mktime(&tA);
    timeB = mktime(&tB);

    int difference = abs(difftime(timeB, timeA) / 86400);

    return difference;
}

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
    cout << "Checking what is in returned data - " << returnData[0] << endl;
    cout << "Checking what is in returned data - " << returnData[1] << endl;
    cout << "Checking what is in returned data - " << returnData[2] << endl;
    priceMap["A"] = stoi(returnData[0]);
    priceMap["B"] = stoi(returnData[1]);
    priceMap["C"] = stoi(returnData[2]);

    //returnData.clear();
    sqlite3_close(db);
}

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
        customerID = -1;
        string queryString = "SELECT idCustomer FROM Customers WHERE email = '" + e + "' AND name = '" + n + "'";
        cout << queryString << endl;
        const char *query = queryString.c_str();
        rc = sqlite3_exec(db, query, callbackCustomerID, 0, &zErrMsg);
        if (customerID == -1){
            cout << "I've added the customer sir!" << endl;
            addCustomer(c);
        }
    }
    returnData.clear();
    sqlite3_close(db);
}

void DBConnector::generateReport()
{
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

    /* generate unique title by date */
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
            queryString = "SELECT * FROM Dates WHERE '" + sDate + "' >= arrivalDate AND '" + sDate + "' <= departureDate AND idRoom = " + to_string(returnedRooms[i]);
            cout << queryString << endl;
            query = queryString.c_str();
            rc = sqlite3_exec(db, query, tmpcallback, 0, &zErrMsg);
            if (returnData.size() == 0)
            {
                returnedRooms.clear();
                sqlite3_close(db);

                rc = sqlite3_open(DB, &db);
                int diffInDays = datesDiff(sDate, eDate);
                returnData.clear();
                insideRefreshPriceMap();
                cout << priceMap[cls] << ", " << diffInDays<< endl;
                int totalPrice = priceMap[cls] * (diffInDays - 1);
                queryString = "SELECT idCustomer FROM Customers WHERE name = '" + c->getName() + "' AND email = '" + c->getEmail() + "'";
                query = queryString.c_str();
                rc = sqlite3_exec(db, query, callbackCustomerID, 0, &zErrMsg);
                sqlite3_close(db);

                rc = sqlite3_open(DB, &db);
                queryString = "INSERT INTO Orders (totalPrice, idRoom, idCustomer) values(" + to_string(totalPrice) + ", " + to_string(returnedRooms[i]) + ", " + to_string(customerID) + ")";
                query = queryString.c_str();
                rc = sqlite3_exec(db, query, callbackOrderID, 0, &zErrMsg);
                sqlite3_close(db);

                rc = sqlite3_open(DB, &db);
                queryString = "SELECT idOrder FROM Orders WHERE totalPrice = " + to_string(totalPrice) + " AND idCustomer = " + to_string(customerID);
                query = queryString.c_str();
                rc = sqlite3_exec(db, query, callbackOrderID, 0, &zErrMsg);
                sqlite3_close(db);

                rc = sqlite3_open(DB, &db);
                queryString = "INSERT INTO Dates (idRoom, arrivalDate, departureDate, idOrder) values(" + to_string(returnedRooms[i]) + ", '" + sDate + "', '" + eDate + "', " + to_string(orderID) + ")";
                query = queryString.c_str();
                rc = sqlite3_exec(db, query, callbackOrderID, 0, &zErrMsg);
                sqlite3_close(db);
                cout << "Order was booked! \nEnjoy your future stay with us!" << endl;
                return true;
            }
            returnData.clear();
            sqlite3_close(db);
        }
        cout << "There are no available rooms in these dates :(,\nplease try different dates or other room class, Good luck!" << endl;
        returnedRooms.clear();
        return false;
    }
    sqlite3_close(db);
}
