#pragma once
#include <iostream>
#include <string>
using namespace std;

class Customer
{
private:
    string _name;
    string _email;
    string _phone;

public:
    Customer(string name, string email, string phone);
    ~Customer() {}
    
    string getName();
    string getEmail();
    string getPhone();
};