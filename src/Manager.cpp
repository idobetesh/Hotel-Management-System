#include "Manager.h"

Manager::Manager(int id, string name) : Employee(id, name) {}

void Manager::priceUpdater(char cls, int newPrice)
{
    _db->updatePrice(cls, newPrice);
}

void Manager::getReport()
{
    _db->generateReport();
}