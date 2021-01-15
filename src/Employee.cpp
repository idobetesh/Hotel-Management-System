#include "Employee.h"

Employee::Employee(string name) : _name(name)
{
  _db = new DBConnector();
}

void Employee::checkIn(int roomNumber)
{
  _db->checkIn(roomNumber);
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

// void Employee::refreshPriceMap()
// {
//   _db->refreshPriceMap();
// }
bool Employee::bookRoom(string cls, string sDate, string eDate, Customer *c)
{
  return _db->bookRoom(cls, sDate, eDate, c);
}
