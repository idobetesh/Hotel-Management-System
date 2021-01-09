// #include "Manager.h"
// #include "Room.h"
#include <iostream>
#include <sqlite3.h>
#include <string>
#include "DB_Connector.h"
#include "Customer.h"
using namespace std;

void menu()
{

    string pass;
    cout << "================ Welcome To Hotel California ================" << endl;
    cout << "if you are a manager enter password, else press *> ";
    cin >> pass;
    if (pass == "123")
    {
        DBConnector *db = new DBConnector();
        Customer *c = new Customer("mori shalom", "mor123@gmail.com", "1122345324");
        db->addCustomer(c);
        //Manager *m = new Manager("yali", 123);
        // cout << "Hello Manager!\nWhat would you like to do?" << endl;
        // cout << "1 - Get financial report" << endl;
        // cout << "2 - Update prices" << endl;
        // cout << "3 - Book a room" << endl;
        // cout << "4 - Check-in room" << endl;
        // cout << "5 - Check-out room " << endl;
        // cout << "6 - Book a room" << endl;
        // cout << "6 - Watch available rooms" << endl;
    }
    else
    {
        cout << "Hello!\nWhat would you like to do?" << endl;
        cout << "1- Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room " << endl;
        cout << "4 - Book a room" << endl;
        cout << "5 - Watch available rooms" << endl;
    }
    //swich case
};

int main(void)
{
    menu();
    // Room *r = new Room();
    return 0;
}