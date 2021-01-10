#pragma once
#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
    string _name;
    int _id;

public:
    Employee();
    Employee(string name, int id);
    virtual ~Employee();

    string getName() { return _name; }
    // void bookRoom(int roomNumber) {}
    // void checkIn();
    // void checkOut() {}
    // string watchAvbRooms() {}
};