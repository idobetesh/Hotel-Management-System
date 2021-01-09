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
    void checkIn();
    void checkOut() {}
    // string watchAvbRooms() {}
};