#pragma once
#include <iostream>
#include <string>
using namespace std;

class Customer
{
private:
    // int _id;
    string _name;
    string _email;
    string _phone;

public:
    Customer(string name, string email, string phone);
    ~Customer() {}
    string getName() { return _name; }
    string getEmail() { return _email; }
    string getPhone() { return _phone; }
};