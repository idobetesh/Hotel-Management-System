#include "Employee.h"

/* All of these functions are connected to the DB so that the main job is done within the DBConnector class */

Employee::Employee(string name) : _name(name)
{
  _db = new DBConnector();
}

void Employee::checkIn(string name, string email)
{
  _db->checkIn(name, email);
}

void Employee::checkOut(int roomNumber)
{
  _db->checkOut(roomNumber);
}

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

int Employee::bookRoom(string cls, string sDate, string eDate, Customer *c)
{
  return _db->bookRoom(cls, sDate, eDate, c);
}

string Employee::getPrices()
{
    return _db->getPricesString();
}

int Employee::updateOrder(Customer *c, string sDate, string eDate)
{
    return _db->updateOrder(c, sDate, eDate);
}
