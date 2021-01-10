#include "Manager.h"

Manager::Manager(int id, string name) : Employee(name, id)
{
    _db = new DBConnector();
}

void Manager::financialReport()
{
    // TO DO
}

void Manager::priceUpdater(char cls, int newPrice)
{
    _db->updatePrice(cls, newPrice);
}