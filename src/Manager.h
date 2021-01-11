#pragma once
#include "Employee.h"
#include "DBConnector.h"
class Manager : public Employee
{
public:
    Manager(int id, string name);
    ~Manager();

    void priceUpdater(char cls, int newPrice);
    void getReport();
};
