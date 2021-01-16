#include "Menu.h"

void Menu::start()
{
    string name, pass;
    while (true)
    {
        cout << "================ Welcome To Hotel California ================" << endl;
        cout << "Enter username: ";
        cin >> name;
        cout << "Enter password: ";
        cin >> pass;
        int status = _db->authenticate(name, pass);
        switch (status)
        {
        case 0:
            cout << "Username or password is incorrect, try again"<< endl;
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

        if (_m || _e)
        {
            break;
        }
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
        cout << "0 - Exit\n> ";

        cin >> userInput;

        switch (userInput)
        {
        case 0:
            cout << _e->getName() << ", have a great day!";
            break;
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

bool isValidClass(string cls) { return (cls == "A" || cls == "B" || cls == "C"); }

void Menu::bookRoom()
{
    // 1 - enter customer details + order details[dates, that type of room]
    // 2 - check if customer already exist ? continue : create Customer
    // 3 - check availability of the room
    // 4 - if there is a free room ? book the room : ask for different dates/ other class of room and goto 3

    string name, email, phone, sDate, eDate, cls;
    cout << "Please enter customer details - " << endl;
    cout << "Name - ";
    fflush(stdin);
    getline(cin, name);
    cout << "Email - ";
    cin >> email;
    cout << "Phone - ";
    cin >> phone;
    Customer *c = new Customer(name, email, phone);
    if (this->manager)
    {
        _m->isCustomerExist(c); // if not exists - creates new customer in DB else does nothing
    }
    else
    {
        _e->isCustomerExist(c); // if not exists - creates new customer in DB else does nothing
    }

    int bookedRoom = 0;
    while (bookedRoom == 0)
    {
        cout << "Start date in format yyyy-mm-dd\n> ";
        cin >> sDate;
        cout << "End date in format yyyy-mm-dd\n> ";
        cin >> eDate;

        bool validCls = false;
        while (!validCls)
        {
            cout << "Enter room class - ";
            cin >> cls;
            validCls = isValidClass(cls);
            if (!validCls)
                cout << "Class '" << cls << "' was NOT found, try again\n> ";
        }

        if (this->manager)
        {
            bookedRoom = _m->bookRoom(cls, sDate, eDate, c); // should return room number when possible else 0
        }
        else
        {
            bookedRoom = _e->bookRoom(cls, sDate, eDate, c);
        }
    }
    cout << "Room No." << to_string(bookedRoom) << " from class " << cls << " is booked from " << sDate << " to " << eDate << endl;
}

void Menu::getReport()
{
    this->_m->getReport();
}

void Menu::priceList()
{
    string pricesString = "============ Room Prices ============";
    pricesString += this->_m->getPrices();
    cout << pricesString;
}

void Menu::checkIn()
{
    int userInput;
    cout << "Enter room number - ";
    cin >> userInput;
    if (this->manager)
    {
        this->_m->checkIn(userInput);
    }
    else
    {
        this->_e->checkIn(userInput);
    }
}

void Menu::checkOut()
{
    int userInput;
    cout << "Enter room number - ";
    cin >> userInput;
    if (this->manager)
    {
        this->_m->checkOut(userInput);
    }
    else
    {
        this->_e->checkOut(userInput);
    }
}

void Menu::watchAvbRooms()
{
    if (this->manager)
    {
        this->_m->watchAvbRooms();
    }
    else
    {
        this->_e->watchAvbRooms();
    }
}

void Menu::updatePrice() // manager enter price -> new price lower than the current one ? mail customers : none
{
    string cls;
    int newPrice;
    bool validCls = false;
    int isLowerPrice = 0;

    cout << "For which class would you like to change the price?\n> ";
    while (!validCls)
    {
        cin >> cls;
        validCls = isValidClass(cls);
        if (!validCls)
            cout << "Class '" << cls << "' was NOT found, try again\n> ";
    }

    cout << "Enter new price - ";
    cin >> newPrice;
    if (newPrice < 200) // 'last price!'
        newPrice = 200;

    isLowerPrice = _m->priceUpdater(cls, newPrice); // returns currPrice - newPrice
    cout << "The diff is " << isLowerPrice << endl;
    if (isLowerPrice > 0) // newPrice is LOWER than currPrice!
    {
        cout << "Your are about to get in the notify func! " << endl;
        // notify all customers about the new *lower* price
        _db->notify(cls, isLowerPrice, newPrice); // currPrice = isLowerPrice + newPrice
    }
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
        cout << "7 - Price List" << endl;
        cout << "0 - Exit\n> ";
        cin >> userInput;
        switch (userInput)
        {
        case 0:
            cout << _m->getName() << ", have a great day!";
            break;
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
        case 7:
            this->priceList();
            break;
        default:
            cout << "invalid input '" << userInput << "', try again" << endl;
            break;
        }
    }
}