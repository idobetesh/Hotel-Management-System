#include "Manager.h"

Manager::Manager(int id, string name) : Employee(id, name) {}

void Manager::financialReport()
{
    cout << "hi";
}

void Manager::priceUpdater(char cls, int newPrice)
{
    _db->updatePrice(cls, newPrice);
}