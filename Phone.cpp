#include <iostream>
#include <ctype.h>
#include "Phone.h"

using namespace std;

Phone::Phone(string Number, Fan * f) {
    this->f = f;
    this->Number = Number;
    for (int i = 0; i < Number.size(); i++) {
        if (Number[i] == '(') {
            continue;
        }

        if (Number[i] != ')') {
            this->AreaCode += Number[i];
        }
        else {
            break;
        }
    }
}

Phone::Phone() {
    // Fan * fan;
    this->Number = "-1";
    this->AreaCode = "-1";
    this->f = NULL;
}

string Phone::GetAreaCode() {
    return this->AreaCode;
}

void Phone::SetNum(string Num) {
    this->Number = Num;
}

bool Phone::operator>(const Phone& p) {
    if (stoi(AreaCode) > stoi(p.AreaCode)) {
        return true;
    }
    else {
        return false;
    }
}

ostream& operator<<(ostream& os, Phone p){
    os << p.Number;
    return os;
}

// Phone& Phone::operator=(const Phone& obj) {
//     if (this != &obj) {
//         delete &Number;
//         delete &AreaCode;
//         delete f;
//         Number = obj.Number;
//         AreaCode = obj.AreaCode;
//         *f = *(obj.f);
//     }
//     return *this;
// }

string Phone::GetVal() {
    return this->Number;
}

Fan* Phone::GetFan() {
    return this->f;
}

void Phone::SetC(int dollars) {
    this->f->SetConces(dollars);
}