#pragma once
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Customer.h"
using namespace std;

#define DB "./DB/hotel-managment-system.db"

class DBConnector
{
public:
    DBConnector();
    void addCustomer(Customer *c);
    void updatePrice(char cls, int newPrice);
    void watchAvbRooms();
    void checkIn(int roomNumber);
    void checkOut(int roomNumber);
    void isCustomerExist(Customer *c);
};