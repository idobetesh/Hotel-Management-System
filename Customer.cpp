#include "Customer.h"

Customer::Customer(string name, string email, string phone) : _name(name), _email(email), _phone(phone) {}

string Customer::getName() { return _name; }
string Customer::getEmail() { return _email; }
string Customer::getPhone() { return _phone; }