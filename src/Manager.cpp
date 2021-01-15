#include "Manager.h"

Manager::Manager(string name) : Employee(name) {}

void Manager::priceUpdater(char cls, int newPrice)
{
    _db->updatePrice(cls, newPrice);
}

void Manager::getReport()
{
    _db->generateReport();
}