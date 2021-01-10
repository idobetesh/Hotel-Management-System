#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Customer.h"
#include "Employee.h"
#include "Manager.h"
using namespace std;

void bookRoom(Employee *e)
{
    // int userID;
    // string n, e, p;
    // cout << "Please enter the client details - \n" << "id - " << endl;
    // cin >> userID;
    // cout << "Name - ";
    // cin >> n;
    // cout << "Email - ";
    // cin >> e;
    // cout << "Phone - ";
    // cin >> p;
    // e->
    // Customer *c = new Customer(n,e,p);

    // 1 - enter customer details + order details[dates, that type of room]
    // 2 - check if customer already exist ? continue : create Customer 
    // 3 - check availability of the room
    // 4 - if there is a free room ? book the room : ask for different dates/ other class of room and goto 3
}

void checkIn()
{
    int userInput;
    cout << "Please enter the room number -";
    cin >> userInput;
    Manager *e = new Manager(1234, "ido");
    e->checkIn(userInput);
}

void checkOut()
{
    int userInput;
    cout << "Please enter the room number -";
    cin >> userInput;
    Manager *e = new Manager(1234, "ido");
    e->checkOut(userInput);
}

void menu()
{
    string pass;
    int userInput;
    cout << "================ Welcome To Hotel California ================" << endl;
    cout << "if you are a manager enter password, else press *> ";
    cin >> pass;
    if (pass == "123")
    {
        Manager *e = new Manager(1234, "ido");

        //e->checkIn(1);
        //e->checkOut(1);
        e->watchAvbRooms();

        cout << "1 - Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room" << endl;
        cout << "4 - Watch available rooms" << endl;
        cout << "5 - Get financial report" << endl;
        cout << "6 - Update prices" << endl;
        cout << "0 - Exit" << endl;
    }
    else
    {
        cout << "Hello!\nWhat would you like to do? " << endl;
        cout << "1- Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room " << endl;
        cout << "4 - Watch available rooms" << endl;
        cout << "0 - Exit" << endl;
    }
    cin >> userInput;
    switch (userInput)
    {
    case 1:
        //bookRoom(e);
        break;
    case 2:
        checkIn();
        break;
    case 3:
        checkOut();
        break;    
    default:
        break;
    }
    //swich case

};

int main(void)
{
    menu();
    // Room *r = new Room();
    return 0;
}