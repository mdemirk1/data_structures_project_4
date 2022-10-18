#ifndef PHONE_H
#define PHONE_H

#include <iostream>
#include <ctype.h>
#include "Fan.h"
using namespace std;

class Phone
{
private:
    string Number;
    string AreaCode;

public:
    Fan * f;
    Phone(string Number, Fan * f);
    Phone();
    void SetC(int dollars);
    string GetAreaCode();
    string GetVal();
    Fan* GetFan();
    void SetNum(string num);
    bool operator>(const Phone& p);
    friend ostream& operator<<(ostream& os, Phone p);
    // Phone& operator=(const Phone& obj);

    
};

#endif