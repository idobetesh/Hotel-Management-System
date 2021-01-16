#pragma once
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <time.h>
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Customer.h"

#define DB "../DB/hotel-management-system.db"
class DBConnector
{
public:
    DBConnector();
    void addCustomer(Customer *c);
    int updatePrice(string cls, int newPrice);
    void watchAvbRooms();
    void checkIn(int roomNumber);
    void checkOut(int roomNumber);
    void isCustomerExist(Customer *c);
    void generateReport();
    void refreshPriceMap();
    int bookRoom(string cls,string sDate,string eDate, Customer *c);
    int authenticate(string name,string pass);
    string getPricesString();
    void notify(string cls, int priceDiff, int newPrice);
};