#include "Employee.h"

Employee::Employee() {}
Employee::Employee(int id, string name) : _id(id), _name(name), _db(new DBConnector()){}

// void Employee::bookRoom(int roomNumber) {}

// void Employee::checkIn() {}

// void Employee::checkOut() {}

// string Employee::watchAvbRooms() {}

void Employee::addCustomer(Customer *c) 
{
  _db->addCustomer(c);   
}