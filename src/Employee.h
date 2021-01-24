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
    string getPrices();
    void addCustomer(Customer *c);
    void checkIn(string name,string email);
    void checkOut(int roomNumber);
    void watchAvbRooms();
    void isCustomerExist(Customer *c);
    int bookRoom(string cls,string sDate,string eDate, Customer *c);
    int updateOrder(Customer *c, string sDate, string eDate);
};