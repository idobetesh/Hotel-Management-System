#include "Manager.h"

Manager::Manager(string name) : Employee(name) {}

int Manager::priceUpdater(string cls, int newPrice)
{
    return _db->updatePrice(cls, newPrice);
}

void Manager::getReport()
{
    _db->generateReport();
}