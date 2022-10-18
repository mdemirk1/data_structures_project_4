#ifndef FAN_H
#define FAN_H

#include <string>
//#include "Phone.h"
//#include "Email.h"

using namespace std;

class Fan
{
private:
    string FirstName; //must start with a capital letter and may include only letters. 
    string LastName;  //same with FirstName
    string Pnum; //implement a phone class
    string Mail; //implement a email class
    string Seat; 
    int Concessions;

public:
    Fan(string LastName, string FirstName, string Pnum, string Mail, string Seat, int Concessions);
    Fan();
    string GetFirstName();
    string GetLastName();
    string GetPnum();
    string GetMail();
    bool operator==(const Fan& obj);
    friend ostream& operator<<(ostream& os, Fan f);
    void SetConces(int dollar);
};



#endif