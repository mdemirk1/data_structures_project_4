#include <iostream>
#include <regex>
#include "Fan.h"

using namespace std;

Fan::Fan(string LastName, string FirstName, string Pnum, string Mail, string Seat, int Concessions) {
    //cout << "non default inside" << endl;
    this->FirstName = FirstName;
    this->LastName = LastName;
    this->Pnum = Pnum;    
    this->Mail = Mail;
    this->Seat = Seat; 
    this->Concessions = Concessions;
}

Fan::Fan() {
    //cout << "inside" << endl; 
    this->FirstName = "";
    this->LastName = "";
    this->Pnum = "";
    this->Mail = "";
    this->Seat = "";
    this->Concessions = -1;
}

string Fan::GetFirstName() {
    return this->FirstName;
}

string Fan::GetLastName() {
    return this->LastName;
}

string Fan::GetPnum() {
    return this->Pnum;
}

string Fan::GetMail() {
    return this->Mail;
}

void Fan::SetConces(int dollar) {
    this->Concessions = this->Concessions + dollar;
    return;
}

bool Fan::operator==(const Fan& obj) {
    if (FirstName == obj.FirstName && LastName == obj.LastName) {
        return true;
    }
    else {
        return false;
    }
}

ostream& operator<<(ostream& os, Fan f) {
    os << f.LastName << " " << f.FirstName << " " << f.Pnum << " " << f.Mail << " " << f.Seat << " " << f.Concessions << endl;
    return os;
}