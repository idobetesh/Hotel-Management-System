#pragma once
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "DBConnector.h"
#include "Manager.h"
using namespace std;
class Menu
{
private:
    DBConnector *_db;
    Employee *_e;
    Manager *_m;
    bool manager;

public:
    Menu(){ manager = false; };
    ~Menu();
    void start();
    void bookRoom();
    void getReport();
    void checkIn();
    void checkOut();
    void watchAvbRooms();
    void updatePrice();
    void employeeMenu();
    void managerMenu();
    void priceList();
    void updateOrder();
    void addNewEmployee();
    void deleteEmployee();
};