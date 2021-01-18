#include "Manager.h"

/* All of these functions are connected to the DB so that the main job is done within the DBConnector class */

Manager::Manager(string name) : Employee(name) {}

int Manager::priceUpdater(string cls, int newPrice)
{
    return _db->updatePrice(cls, newPrice);
}

void Manager::getReport()
{
    _db->generateReport();
}