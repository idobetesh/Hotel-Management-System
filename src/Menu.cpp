#include "Menu.h"

void Menu::start()
{
    while(true)
    {
        string name, pass;
        cout << "================ Welcome To Hotel California ================" << endl;
        cout << "Enter username: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> pass;
        int status = _db->authenticate(name, pass);
        switch (status) 
        {
            case 0: 
                cout << "Bad input! '" << name << "' was NOT found" << endl;
                break;
            case 1:
                _e = new Employee(name);
                employeeMenu(); 
                break;
            case 2:
                _m = new Manager(name);
                this->manager = 1;
                managerMenu();
                break;
        }
        if(_m || _e) {break;}
    }
}
        
void Menu::employeeMenu()
{
    int userInput = -1;
    cout << "Welcome " << _e->getName() << endl;
    while (userInput != 0)
    {
        cout << "What would you like to do? " << endl;
        cout << "1 - Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room " << endl;
        cout << "4 - Watch available rooms" << endl;
        cout << "0 - Exit\n> " << endl;

        cin >> userInput;

        switch (userInput)
        {
        case 1:
            bookRoom();
            break;
        case 2:
            checkIn();
            break;
        case 3:
            checkOut();
            break;
        case 4:
            watchAvbRooms();
            break;
        default:
            cout << "invalid input, try again" << endl;
            break;
        }
    }
}

void Menu::bookRoom()
{
    string name, email, phone, sDate, eDate, cls;
    cout << "Please enter the client details - " << endl;
    cout << "Name - ";
    fflush(stdin);
    getline(cin, name);
    cout << "Email - ";
    cin >> email;
    cout << "Phone - ";
    cin >> phone;
    Customer *c = new Customer(name, email, phone);
    if(this->manager){
        _m->isCustomerExist(c); // if not exists - creates new customer in DB else does nothing
    } else {
        _e->isCustomerExist(c); // if not exists - creates new customer in DB else does nothing
    }
    

    bool isPossible = false;
    while (!isPossible)
    {
        cout << "Start date in format yyyy-mm-dd\n> ";
        cin >> sDate;
        cout << "End date in format yyyy-mm-dd\n> ";
        cin >> eDate;
        cout << "Enter class of room - ";
        cin >> cls;
        if (this->manager){
            isPossible = _m->bookRoom(cls, sDate, eDate, c);
            cout << isPossible << endl;
        } else {
            isPossible = _e->bookRoom(cls, sDate, eDate, c);
            cout << isPossible << endl;
        }
    }
    cout << "Room is booked! see you soon!";
    // 1 - enter customer details + order details[dates, that type of room]
    // 2 - check if customer already exist ? continue : create Customer
    // 3 - check availability of the room
    // 4 - if there is a free room ? book the room : ask for different dates/ other class of room and goto 3
}

void Menu::getReport()
{
    // m->refreshPriceMap();
    this->_m->getReport();
}

void Menu::checkIn()
{
    int userInput;
    cout << "Enter room number - ";
    cin >> userInput;
    if(this->manager){
        this->_m->checkIn(userInput);
    } else {
        this->_e->checkIn(userInput);
    }
    
}

void Menu::checkOut()
{
    int userInput;
    cout << "Enter room number - ";
    cin >> userInput;
    if(this->manager){
        this->_m->checkOut(userInput);
    } else {
        this->_e->checkOut(userInput);
    }
}

void Menu::watchAvbRooms()
{
    if(this->manager){
        this->_m->watchAvbRooms();
    } else {
        this->_e->watchAvbRooms();
    }
    
}

void Menu::updatePrice()
{
    char cls;
    int amount;
    cout << "What is the room class you want the price to change?\n> ";
    cin >> cls;
    cout << "What is the new amount you want to change?\n> ";
    cin >> amount;
    _m->priceUpdater(cls, amount);
}

void Menu::managerMenu()
{
    int userInput = -1;
    while (userInput != 0)
    {            
        cout << "Welcome " << _m->getName() << endl;
        cout << "1 - Book a room" << endl;
        cout << "2 - Check-in room" << endl;
        cout << "3 - Check-out room" << endl;
        cout << "4 - Watch available rooms" << endl;
        cout << "5 - Update prices" << endl;
        cout << "6 - Get report" << endl;
        cout << "0 - Exit\n> ";
        cin >> userInput;
        switch (userInput)
        {
        case 1:
            this->bookRoom();
            break;
        case 2:
            this->checkIn();
            break;
        case 3:
            this->checkOut();
            break;
        case 4:
            this->watchAvbRooms();
            break;
        case 5:
            this->updatePrice();
            break;
        case 6:
            this->getReport();
            break;
        default:
            cout << "invalid input '" << userInput << "', try again" << endl;
            break;
        }
    }
}