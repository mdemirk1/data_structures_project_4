#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <regex>
#include "LinkedList.h"
#include "Fan.h"
#include "Phone.h"
#include "Email.h"
#include "Parser.h"
#include "BinarySearchTree.cpp"

using namespace std;

bool Is_valid_email(string arg) {
    for (int i = 0; i < arg.size(); i++) {
        if (arg[i] == '@') {
            return true;
        }
    }
    return false;
}

bool Is_valid_phone(string arg){
    if(!(arg.length()==13)) return false;
    if(!(arg[0] == '(')) return false;
    if(!(arg[4] == ')')) return false;
    if(!(arg[8] == '-')) return false;
    for(int i=0; i < arg.length();i++){
        if(i==0 || i==4 || i==8) continue;
        if(!(isdigit(arg[i]))) return false;
    }
    return true;
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void proc(string filename,BinaryTree<Phone*> * Phones, BinaryTree<Email*> * Emails, LinkedList * LL, string OutFile) {
    
    fstream f;
    f.open(filename, ios::in);
    if (f.is_open()) {
        string cp;
        while (getline(f, cp)) {
            Parser cm(cp);
            if (cm.getArg1() == "Quit") {
                if (cm.numArgs() > 1) {
                    cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                    continue;
                }
                cout << endl;
                fstream o;
                o.open(OutFile, ios::out);
                if (o.is_open()) {
                    for (int i = 0; i < LL->size; i++) {
                        o << *LL->GetFan();
                        LL->iterate();
                    }
                }   
                o.close();
                exit(1);
            }

            if (cm.getArg1() == "Load") {
                if (cm.numArgs() < 2) {
                    cout << std::endl << MISSING_ARGS << endl;
                    continue;
                }
                if (cm.numArgs() > 2) {
                    cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                    continue;
                }
                string LoadFileName = cm.getArg2();
                fstream read;
                read.open(LoadFileName, ios::in);
                if(read.is_open()) {
                    string l;
                    int p;
                    regex integer_expr2("(\\+|-)?[[:digit:]]+");
                    while (getline(read, l)) {
                        Parser com(l);
                        if (regex_match(com.getArg6(), integer_expr2)) {
                            p = stoi(com.getArg6());
                        }else {
                            cerr << "ERROR: incorrect concession argument" << endl;
                            continue;
                        }
                        if (!(isupper(com.getArg1()[0]))) {
                            cout << "ERROR: incorrect firstname argument" << endl;
                            continue;;
                        }
                        if (!(isupper(com.getArg2()[0]))) {
                            cout << "ERROR: incorrect lastname argument" << endl;
                            continue;
                        }
                        if (!(Is_valid_phone(com.getArg3()))) {
                            cout << "ERROR: incorrect phone number argument" << endl;
                            continue;
                        }
                        if (!(Is_valid_email(com.getArg4()))) {
                            cout << "ERROR: incorrect email argument" << endl;
                            continue;
                        }
                        if (!(is_number(com.getArg5()))) {
                            cout << "ERROR: incorrect seat argument" << endl;
                            continue;
                        }
                        Fan *fan = new Fan(com.getArg1(),com.getArg2(),com.getArg3(),com.getArg4(),com.getArg5(),p);
                        if (LL->Search(*fan)) {
                            cout << "duplicate fan object rejected" << endl;
                            continue;
                        }
                        LL->add(fan);
                        Phone *p = new Phone(fan->GetPnum(), LL->GetT());
                        Email *m = new Email(fan->GetMail(), LL->GetT());
                        Emails->add(m);
                        Phones->add(p);
                    }
                read.close();
                }
                else {
                    cerr << "ERROR: Problem opening file" << endl;
                    exit(1);
                }
            }

            if (cm.getArg1() == "Show") {
                if (cm.numArgs() < 2) {
                    cout << std::endl << MISSING_ARGS << endl;
                    continue;
                }
                if (cm.numArgs() > 2) {
                    cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                    continue;
                }
                string fanid = cm.getArg2();

                if (fanid[0] == '(') {
                    if ((Phones->search(fanid)) != NULL) {
                        cout << *(Phones->search(fanid)) << endl;
                    }else {
                        cout << "fan-number cannot found" << endl;
                    } 
                }
                else {
                    if (Emails->search(fanid) != NULL) {
                        cout << *(Emails->search(fanid)) << endl;
                    }
                    else {
                        cout << "fan-email cannot found" << endl;
                    }
                }
            }
            if (cm.getArg1() == "Spend") {
                
                int dollars;
                string fanid = cm.getArg2();
                if (cm.numArgs() < 3) {
                    cout << std::endl << MISSING_ARGS << endl;
                    continue;
                }
                if (is_number(cm.getArg3())) {
                    dollars = stoi(cm.getArg3());
                }else {
                    cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                    cout << "spending must be an integer value." << endl;
                    continue; 
                }
                if (cm.numArgs() > 3) {
                    cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                    continue;
                }

                if (fanid[0] == '(') {
                    if ((Phones->search(fanid)) != NULL) {
                        Phones->search(fanid)->SetConces(dollars);
                        
                    }else {
                       cout << "fan-number cannot found" << endl; 
                    }
                }else {
                    if (Emails->search(fanid) != NULL) {
                        Emails->search(fanid)->SetConces(dollars);
                    

                    }else {
                        cout << "fan-email cannot found" << endl;
                    }
                }
            }
            if (cm.getArg1() == "Remove") {
                if (cm.numArgs() < 2) {
                    cout << std::endl << MISSING_ARGS << endl;
                    continue;
                }
                if (cm.numArgs() > 2) {
                    cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                    continue;
                }
                string fanid = cm.getArg2();
                Fan* fanid2;
                if ((Phones->search(fanid)) != NULL || Emails->search(fanid) != NULL) {

                    if (fanid[0] == '(') {
                        fanid2 = Phones->search(fanid);
                        LL->remove(fanid2);
                        Phones->Remove(Phones, fanid);
                        Emails->Remove(Emails, fanid2->GetMail());
                    }
                    else {
                        fanid2 = Emails->search(fanid);
                        LL->remove(fanid2);
                        Emails->Remove(Emails, fanid);
                        Phones->Remove(Phones, fanid2->GetPnum());
                    }
                }
                else {
                    cout << "fan-id cannot found" << endl;
                }
                
            }
            // recursively calling proc func above.
            if (cm.getArg1() == "Process") {
                if (cm.numArgs() < 2) {
                cout << std::endl << MISSING_ARGS << endl;
                continue;
                }

                if (cm.numArgs() > 2) {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                continue;
                }
            string ProcFile = cm.getArg2();
            proc(ProcFile, Phones, Emails, LL, OutFile);
            }
            

        }
    f.close();
    }
    else {
        cerr << "ERROR: Problem opening file" << endl;
        exit(1);
    }
}

int main(int argc, char *argv[]) {

    BinaryTree<Phone*> * Phones = new BinaryTree<Phone*>();
    BinaryTree<Email*> * Emails = new BinaryTree<Email*>();
    LinkedList * LL = new LinkedList();
    cout << endl;
    string line; // menu ops
    
    int FanCounter;
    int opt;
    int flags = 0;  // true when -o option is present ---> 
    string nsecs;  //set to the value of -i parameter, ---> input file
    int tfnd = 0;
    
    while ((opt = getopt(argc, argv, "oi:")) != -1) {
        switch (opt) {
        case 'o':
            flags = 1;
            break;
        case 'i':
            nsecs = optarg;
            tfnd = 1;
            break;
        default:
            cerr << "ERROR: incorrect input usage" << endl;
            exit(1);
        }
    }
    string OutFile;
    if (optind >= argc) {
        argv[optind] = "fans.out.txt";
        OutFile = argv[optind];
    }
    else {
        OutFile = argv[optind];
    }

    // cout << "name argument = " << argv[optind] << endl;   //---> output filename

    if (nsecs == "") {
        nsecs = "fans.in.txt";
    }
    string filename = nsecs;
    fstream r;
    r.open(filename, ios::in);
    if(r.is_open()) {
        string line;
        int param;
        regex integer_expr("(\\+|-)?[[:digit:]]+");
        while (getline(r, line)) {
            Parser command(line);
            if (regex_match(command.getArg6(), integer_expr)) {
                param = stoi(command.getArg6());
            }else {
                cout << "ERROR: incorrect concession argument" << endl;
                continue;;
            }
            if (!(isupper(command.getArg1()[0]))) {
                cout << "ERROR: incorrect firstname argument" << endl;
                continue;;
            }
            if (!(isupper(command.getArg2()[0]))) {
                cout << "ERROR: incorrect lastname argument" << endl;
                continue;
            }
            if (!(Is_valid_phone(command.getArg3()))) {
                cout << "ERROR: incorrect phone number argument" << endl;
                continue;
            }
            if (!(Is_valid_email(command.getArg4()))) {
                cout << "ERROR: incorrect email argument" << endl;
                continue;
            }
            if (!(is_number(command.getArg5()))) {
                cout << "ERROR: incorrect seat argument" << endl;
                continue;
            }
            
            Fan *fan = new Fan(command.getArg1(),command.getArg2(),command.getArg3(),command.getArg4(),command.getArg5(),param);
            if ((LL->Search(*fan))) {
                cout << "duplicate fan object rejected" << endl;
                continue;
            }
            LL->add(fan);
            Phone *p = new Phone(fan->GetPnum(), LL->GetT());
            Email *m = new Email(fan->GetMail(), LL->GetT());
            Emails->add(m);
            Phones->add(p);
        }
        r.close();
    }
    else {
        cerr << "ERROR: Problem opening file" << endl;
        exit(1);
    }
    while(true) {
        cout << endl << "Enter a command:" << endl;
        cout<<"Choose from"<<endl;
        cout << 
	      "   Load <input-filename>" << std::endl << 
	      "   Show <fan-id>" << std::endl << 
	      "   Spend <fan-id> <dollars>" << std::endl << 
          "   Remove <fan-id>" <<std::endl<<
          "   Process <commands-filename>" <<std::endl<<
	      "   Quit";
        cout << endl;
        cout << ": ";

        getline(cin, line);
        Parser command(line);
        
        if (command.getArg1().empty()){
            if (std::cin.fail()) {  
                break;
            }
            continue;
        }
    
        if (command.getArg1() == "Quit") {
            if (command.numArgs() > 1) {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                continue;
            }
            cout << endl;
            fstream o;
            o.open(OutFile, ios::out);
            if (o.is_open()) {
                for (int i = 0; i < LL->size; i++) {
                    o << *LL->GetFan();
                    LL->iterate();
                }
            }
            o.close();
            break;
        }
        
        if (command.getArg1() == "Load") {
            if (command.numArgs() < 2) {
                cout << std::endl << MISSING_ARGS << endl;
                continue;
            }
            if (command.numArgs() > 2) {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                continue;
            }
            string LoadFileName = command.getArg2();
            fstream read;
            read.open(LoadFileName, ios::in);
            if(read.is_open()) {
            string l;
            int p;
            regex integer_expr2("(\\+|-)?[[:digit:]]+");
            while (getline(read, l)) {
                Parser com(l);
                if (regex_match(com.getArg6(), integer_expr2)) {
                    p = stoi(com.getArg6());
                }else {
                    cout << "ERROR: incorrect concession argument" << endl;
                    continue;
                }
                if (!(isupper(com.getArg1()[0]))) {
                    cout << "ERROR: incorrect firstname argument" << endl;
                    continue;;
                }
                if (!(isupper(com.getArg2()[0]))) {
                    cout << "ERROR: incorrect lastname argument" << endl;
                    continue;
                }
                if (!(Is_valid_phone(com.getArg3()))) {
                    cout << "ERROR: incorrect phone number argument" << endl;
                    continue;
                }
                if (!(Is_valid_email(com.getArg4()))) {
                    cout << "ERROR: incorrect email argument" << endl;
                    continue;
                }
                if (!(is_number(com.getArg5()))) {
                    cout << "ERROR: incorrect seat argument" << endl;
                    continue;
                }
                Fan *fan = new Fan(com.getArg1(),com.getArg2(),com.getArg3(),com.getArg4(),com.getArg5(),p);
                if ((LL->Search(*fan))) {
                    cout << "duplicate fan object rejected" << endl;
                    continue;
                }
                LL->add(fan);
                Phone *p = new Phone(fan->GetPnum(), LL->GetT());
                Email *m = new Email(fan->GetMail(), LL->GetT());
                Emails->add(m);
                Phones->add(p);
            }
            read.close();
            }
        else {
            cerr << "ERROR: Problem opening file" << endl;
            exit(1);
            }
        }

        if (command.getArg1() == "Show") {
            if (command.numArgs() < 2) {
                cout << std::endl << MISSING_ARGS << endl;
                continue;
            }
            if (command.numArgs() > 2) {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                continue;
            }
            string fanid = command.getArg2();

            if (fanid[0] == '(') {
                if ((Phones->search(fanid)) != NULL) {
                    cout << *(Phones->search(fanid)) << endl;

                }else {
                    cout << "fan-number cannot found" << endl;
                } 
            }
            else {
                if (Emails->search(fanid) != NULL) {
                    cout << *(Emails->search(fanid)) << endl;
                }
                else {
                    cout << "fan-email cannot found" << endl;
                }
            }
        }

        if (command.getArg1() == "Spend") {
            
            int dollars;
            string fanid = command.getArg2();
            if (command.numArgs() < 3) {
                cout << std::endl << MISSING_ARGS << endl;
                continue;
            }
            if ((is_number(command.getArg3()))) {
                dollars = stoi(command.getArg3());
            }else {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                cout << "spending must be an integer value." << endl;
                continue;
            }
            if (command.numArgs() > 3) {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                continue;
            }
            
            if (fanid[0] == '(') {
                if ((Phones->search(fanid)) != NULL) {
                    Phones->search(fanid)->SetConces(dollars);
                    
                }else {
                    cout << "fan-number cannot found" << endl;
                }
            }else {
                if (Emails->search(fanid) != NULL) {
                    Emails->search(fanid)->SetConces(dollars);
                    
                    
                }else {
                    cout << "fan-email cannot found" << endl;
                }
            }
        }
        if (command.getArg1() == "Remove") {
            if (command.numArgs() < 2) {
                cout << std::endl << MISSING_ARGS << endl;
                continue;
            }
            if (command.numArgs() > 2) {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                continue;
            }
            string fanid = command.getArg2();
            Fan* fanid2;
            if ((Phones->search(fanid)) != NULL || Emails->search(fanid) != NULL) {
                
                if (fanid[0] == '(') {
                    fanid2 = Phones->search(fanid);
                    LL->remove(fanid2);
                    Phones->Remove(Phones, fanid);
                    Emails->Remove(Emails, fanid2->GetMail());
                }
                else {
                    fanid2 = Emails->search(fanid);
                    LL->remove(fanid2);
                    Emails->Remove(Emails, fanid);
                    Phones->Remove(Phones, fanid2->GetPnum());
                }
            }
            else {
                cout << "fan-id cannot found" << endl;
            }
        }

        if (command.getArg1() == "Process") {
            if (command.numArgs() < 2) {
                cout << std::endl << MISSING_ARGS << endl;
                continue;
            }
            if (command.numArgs() > 2) {
                cout << std::endl << "Ignoring " << UNEXPECTED_ARGS << endl;
                continue;
            }
            string ProcFile = command.getArg2();
            proc(ProcFile, Phones, Emails, LL, OutFile); // recursively calls proc func above.
        }
    }
    delete Phones;
    delete Emails;
    delete LL;
    
    return 0;
}
