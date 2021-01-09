#pragma once
#include <iostream>
#include <unordered_map>
using namespace std;

class Room
{
private:
    int _id;
    bool _state;
    char _class;
    unordered_map<char,int> prices;
public:
    Room();
    ~Room();
    void edit();
    bool getState() { return _state; }
    void setState(bool state) { _state = state; }

};