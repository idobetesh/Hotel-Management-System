#pragma once
#include <iostream>
#include <string>
#include "DBConnector.h"
#include "Customer.h"
using namespace std;
class Employee
{
private:
    string _name;

protected:
    DBConnector *_db;

public:
    Employee(string name);
    ~Employee();

    string getName() { return _name; }
    void addCustomer(Customer *c);
    void checkIn(int roomNumber);
    void checkOut(int roomNumber);
    void watchAvbRooms();
    void isCustomerExist(Customer *c);
    // void refreshPriceMap();
    bool bookRoom(string cls,string sDate,string eDate, Customer *c);
};