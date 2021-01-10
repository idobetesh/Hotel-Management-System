#pragma once
#include "Employee.h"
#include "DBConnector.h"
class Manager : public Employee
{
private:
    DBConnector *_db;

public:
    Manager(int id, string name);
    virtual ~Manager();
    void financialReport();
    void priceUpdater(char cls, int newPrice);
};
