#pragma once
#include <iostream>
#include <string>
using namespace std;

class User
{
private:
    string _name;
    int _id;

public:
    User();
    User(string name, int id);
    virtual ~User();

    string getName() { return _name; }
    void bookRoom(int roomNumber) {}
    virtual void checkIn() = 0;
    void checkOut() {}
    string watchAvbRooms() {}
};