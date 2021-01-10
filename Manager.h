#pragma once
#include "Employee.h"
#include "DB_Connector.h"
class Manager : public Employee
{
private:
    DBConnector *_db;

public:
    Manager(int id, string name);
    void financialReport();
    void priceUpdater(char cls, int newPrice);
};
