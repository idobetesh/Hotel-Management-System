#include <iostream>
#include <sqlite3.h>
#include <string>
#include "Customer.h"
#include "Employee.h"
#include "Manager.h"
using namespace std;

void menu()
{
    string pass;
    int userInput;
    cout << "================ Welcome To Hotel California ================" << endl;
    cout << "if you are a manager enter password, else press *> ";
    cin >> pass;
    if (pass == "123")
    {
        Customer *c = new Customer("dor oved", "ddsi19@gmail.com", "012445328");
        Manager *m = new Manager(1234, "ido");

        m->checkIn(1);
        m->checkOut(1);
        m->watchAvbRooms();

        cout << "1 - Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room" << endl;
        cout << "4 - Watch available rooms" << endl;
        cout << "5 - Get financial report" << endl;
        cout << "6 - Update prices" << endl;
    }
    else
    {
        cout << "Hello!\nWhat would you like to do? " << endl;
        cout << "1- Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room " << endl;
        cout << "4 - Watch available rooms" << endl;
    }
    //swich case
};

int main(void)
{
    menu();
    // Room *r = new Room();
    return 0;
}