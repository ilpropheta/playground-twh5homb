#include "Exercises/MicroUrl.h"

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

void Message(string channel, string msg) {
    stringstream ss(msg);
    string line;
    while (getline(ss, line, '\n')) {
        cout << "TECHIO> message --channel \"" << channel << "\" \"" << line << "\"" << endl;
    }
}

void Success(bool success) {
    cout << "TECHIO> success " << (success ? "true" : "false") << endl;
}

// check if a string exists in a text file
bool ExistsInFile(string str, string filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        if (line.find(str) != string::npos ) {
            return true;
        }
    }
    
    return false;
}

void AssertEquals(int expected, int found, string message) {
    if(expected != found) {
        ostringstream error;
        error << message << " Expected: " << expected << ", Found: " << found  << endl;
        throw logic_error(error.str());
    }
}

int main() 
{

      MicroUrl service;

      if (service.Shorten("http://google.com") == "https://micro.url")
      {
        Message("Great 🌟", "Well done");
        Success(true);
      }
      else
      {
        Message("Oops! 🐞", "Not correct");
        Message("Hint 💡", "Encode properly");
        Success(false);  
      }
}
