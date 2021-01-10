#include "Employee.h"

// Employee::Employee() {}
Employee::Employee(int id, string name) : _id(id), _name(name)
{
    _db = new DBConnector();
}

// void Employee::bookRoom(int roomNumber) {}

void Employee::checkIn(int roomNumber)
{
    _db->checkIn(roomNumber);
}

void Employee::checkOut(int roomNumber)
{
    _db->checkOut(roomNumber);
}

// void Employee::checkOut() {}

void Employee::watchAvbRooms() 
{
  _db->watchAvbRooms();
}

void Employee::addCustomer(Customer *c) 
{
  _db->addCustomer(c);   
}

void Employee::isCustomerExist(Customer *c)
{
  _db->isCustomerExist(c);
}