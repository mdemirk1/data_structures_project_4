#ifndef EMAIL_H
#define EMAIL_H

#include <iostream>
#include <vector>
#include "Fan.h"
using namespace std;

class Email
{
private:
    string mail;
    string name;
    Fan * f;

public:
    void SetC(int dollars);
    Email(string mail, Fan * f);
    Email();
    string GetName();
    string GetVal();
    Fan* GetFan();
    void setMail(string m);
    bool operator>(const Email& m);
    friend ostream& operator<<(ostream& os, Email m);
    // Email& operator=(const Email& obj);
};

#endif