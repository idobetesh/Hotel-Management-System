#pragma once
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Customer.h"
using namespace std;

#define DB "../DB/hotel-management-system.db"
class DBConnector
{
public:
    DBConnector();
    ~DBConnector();

    void addCustomer(Customer *c);
    void watchAvbRooms();
    void checkIn(string name,string email);
    void checkOut(int roomNumber);
    void isCustomerExist(Customer *c);
    void generateReport();
    void refreshPriceMap();
    void notify(string cls, int priceDiff, int newPrice);
    void addNewEmployeeToDB(string name, string password, bool isManager);
    void deleteEmployeeFromDB(string name, string password);
    int updatePrice(string cls, int newPrice);
    int bookRoom(string cls,string sDate,string eDate, Customer *c);
    int authenticate(string name,string pass);
    int updateOrder(Customer *c, string sDate, string eDate);
    string getPricesString();
};