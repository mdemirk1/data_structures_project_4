#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

static const char *WHITESPACE = " \t\n\r";
static const char *UNEXPECTED_ARGS = "unexpected arguments";
static const char *MISSING_ARGS = "missing arguments";

class Parser {
   public:
      Parser(string line) : arg1(""), arg2(""), arg3(""), arg4(""), arg5(""), arg6(""), arg7("") {
	   num_args = 0;
      stringstream is;	       
      trim_whitespace(line);
      is.str(line);
	   if ((is >> arg1) && (++num_args))
            if ((is >> arg2) && (++num_args))
                if ((is >> arg3) && (++num_args))
                     if ((is >> arg4) && (++num_args))
                        if((is >> arg5) && (++num_args))
                           if ((is >> arg6) && (++num_args)) {
                              getline(is, arg7);
                              arg7.erase(0, arg7.find_first_not_of(WHITESPACE));
		                        if (!arg7.empty()) ++num_args;
                           }
      }
      unsigned numArgs() const {return num_args;};
      string getArg1() const {return arg1;};
      string getArg2() const {return arg2;};
      string getArg3() const {return arg3;};
      string getArg4() const {return arg4;};
      string getArg5() const {return arg5;};
      string getArg6() const {return arg6;};
      string getArg7() const {return arg7;};

      static string splitFirst(string &s) {
         s.erase(0, s.find_first_not_of(WHITESPACE));
         string first;
         stringstream is(s);
         is >> first;
         s.erase(0, s.find_first_of(WHITESPACE));
	      return first; 
      }

      static void trim_whitespace(string &s) {
         s.erase(0, s.find_first_not_of(WHITESPACE));
         s.erase(s.find_last_not_of(WHITESPACE) + 1);
      }

      static bool isInteger(const string &str) {
         for (const char &c : str)
            if (!isdigit(c)) 
	       return false;
         return true;
      }

   private:
      unsigned num_args;
      string arg1; 
      string arg2; 
      string arg3; 
      string arg4; 
      string arg5; 
      string arg6; 
      string arg7;
};

#endif