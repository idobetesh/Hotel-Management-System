#pragma once
#include "Employee.h"
#include "DBConnector.h"
class Manager : public Employee
{
public:
    Manager(string name);
    ~Manager();

    int priceUpdater(string cls, int newPrice);
    void getReport();
};
