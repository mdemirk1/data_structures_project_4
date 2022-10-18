#include <iostream>
#include <ctype.h>
#include <vector>
#include "Email.h"
using namespace std;


Email::Email(string mail, Fan * f) {
    this->mail = mail;
    this->f = f;
    for (int i = 0; i < mail.size(); i++) {
        if (mail[i] != '@') {
            this->name += mail[i];
        }
        else {
            break;
        }
    }
}

Email::Email() {
    this->mail = nullptr;
    //this->f = nullptr;
}

string Email::GetName() {
    return this->name;
}

string Email::GetVal() {
    return this->mail;
}

Fan* Email::GetFan() {
    return this->f;
}

void Email::setMail(string m) {
    this->mail = m;
}

ostream& operator<<(ostream& os, Email m) {
    os << m.mail;
    return os;
}

bool Email::operator>(const Email& m) {
    if (mail > m.mail) {
        return true;
    }
    else {
        return false;
    }
}

void Email::SetC(int dollars) {
    this->f->SetConces(dollars);
}

// Email& Email::operator=(const Email& obj) {
//     if (this != &obj) {
//         delete &mail;
//         delete &name;
//         delete f;
//         mail = obj.mail;
//         name = obj.name;
//         *f = *(obj.f); 
//     }
//     return *this;
// }