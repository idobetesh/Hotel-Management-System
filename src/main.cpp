#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Customer.h"
#include "Employee.h"
#include "Manager.h"
#include <time.h>
using namespace std;

void bookRoom(Employee *e)
{
    string n, em, p, sDate, eDate, cls;
    cout << "Please enter the client details - " << endl;
    cout << "Name - ";
    fflush(stdin);
    getline(cin, n);
    cout << "Email - ";
    cin >> em;
    cout << "Phone - ";
    cin >> p;
    Customer *c = new Customer(n, em, p);
    e->isCustomerExist(c); // if not exists - creates new customer in DB else does nothing

    bool isPossible = false;
    while (!isPossible)
    {
        cout << "Start date in format yyyy-mm-dd\n> ";
        cin >> sDate;
        cout << "End date in format yyyy-mm-dd\n> ";
        cin >> eDate;
        cout << "Enter class of room - ";
        cin >> cls;
        bool isPossible = e->bookRoom(cls, sDate, eDate, c);
    }
    cout << "Booked the room! see you soon!";
    // 1 - enter customer details + order details[dates, that type of room]
    // 2 - check if customer already exist ? continue : create Customer
    // 3 - check availability of the room
    // 4 - if there is a free room ? book the room : ask for different dates/ other class of room and goto 3
}

void getReport(Manager *m)
{
    // m->refreshPriceMap();
    m->getReport();
}

void checkIn()
{
    int userInput;
    cout << "Enter room number - ";
    cin >> userInput;
    Manager *e = new Manager(1234, "ido");
    e->checkIn(userInput);
}

void checkOut()
{
    int userInput;
    cout << "Enter room number - ";
    cin >> userInput;
    Manager *e = new Manager(1234, "ido");
    e->checkOut(userInput);
}

void watchAvbRooms(Employee *e)
{
    e->watchAvbRooms();
}

void updatePrice(Manager *e)
{
    char cls;
    int amount;
    cout << "What is the room class you want the price to change?\n> ";
    cin >> cls;
    cout << "What is the new amount you want to change?\n> ";
    cin >> amount;
    e->priceUpdater(cls, amount);
}

void menu()
{
    string pass;
    int userInput;
    cout << "================ Welcome To Hotel California ================" << endl;
    cout << "if you are a manager enter password, else press *\n> ";
    cin >> pass;
    Manager *m = new Manager(1234, "ido");
    // Employee *m = new Employee(1234, "ido_Emp");

    if (pass == "123")
    {
        cout << "1 - Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room" << endl;
        cout << "4 - Watch available rooms" << endl;
        cout << "5 - Update prices" << endl;
        cout << "6 - Get report" << endl;
        cout << "0 - Exit\n> ";
    }
    else
    {
        cout << "Hello!\nWhat would you like to do? " << endl;
        cout << "1- Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room " << endl;
        cout << "4 - Watch available rooms" << endl;
        cout << "0 - Exit\n> " << endl;
    }
    cin >> userInput;
    switch (userInput)
    {
    case 1:
        bookRoom(m);
        break;
    case 2:
        checkIn();
        break;
    case 3:
        checkOut();
    case 4:
        watchAvbRooms(m);
        break;
    case 5:
        updatePrice(m);
        break;
    case 6:
        getReport(m);
        break;
    default:
        break;
    }
};

int main(void)
{

    menu();
    return 0;
}