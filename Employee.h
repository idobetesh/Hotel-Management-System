#pragma once
#include <iostream>
#include <string>
#include "DBConnector.h"
#include "Customer.h"
using namespace std;
class Employee
{
private:
    int _id;
    string _name;
    DBConnector *_db;

public:
    Employee();
    Employee(int id, string name);
    virtual ~Employee();

    string getName() { return _name; }
    void addCustomer(Customer *c);
    // void bookRoom(int roomNumber) {}
    // void checkIn();
    // void checkOut() {}
    // string watchAvbRooms() {}
};