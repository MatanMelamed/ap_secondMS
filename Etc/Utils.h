#ifndef AP_SECONDMS_UTILS_H
#define AP_SECONDMS_UTILS_H

#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

vector<double> StringSeparatorByComma(string input);

bool UpdateCurrentFromLeftOvers(string &current_string, string &leftovers);

bool ManageStrings(const string &buffer, string &current_string,
                   string &leftovers);


#endif
