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
    string getName();
    string getEmail();
    string getPhone();
    ~Customer() {}
};