#pragma once
#include "User.h"

class Manager : public User 
{
    public:
        Manager(int id, string name) : User(name, id) {}
        void financialReport();
        void priceUpdater();
};
