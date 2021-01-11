#pragma once
#include "Employee.h"
#include "DBConnector.h"
class Manager : public Employee
{
// private:
    // DBConnector *_db;

public:
    Manager(int id, string name);
    ~Manager();

    void priceUpdater(char cls, int newPrice);
    void getFinancialReport();
};
