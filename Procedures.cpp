//Basic procedures:
//Each procedure receives as input a vector of strings and returns a string

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

#include "Procedures.h"

//Print one or more variables; e.g. (print aa), (print aa bb cc)
string print(vector<string>&vv) {
    for (int i = 0; i < vv.size(); i++) {
        cout << vv[i] << " ";
    }
    cout << endl;
    return ("");
}

//Add one or more variables; e.g. (+ aa), (+ aa bb cc)
string add(vector<string>&vv) {
    if (vv.size() == 0)return "Wrong number of arguments for procedure +";
    stringstream ss;
    double sum = strtod(vv[0].c_str(), NULL);
    for (size_t i = 1; i < vv.size(); i++)sum += strtod(vv[i].c_str(), NULL);
    ss << sum;
    return ss.str();
}

//Diff, e.g.: (- aa bb)
string diff(vector<string>&vv) {
    if (vv.size() == 0)return "Wrong number of arguments for procedure -";
    stringstream ss;
    double sum = strtod(vv[0].c_str(), NULL);
    for (size_t i = 1; i < vv.size(); i++)sum -= strtod(vv[i].c_str(), NULL);
    ss << sum;
    return ss.str();
}

//Division, e.g. (/ aa bb cc ...)
string divv(vector<string>&vv) {
    if (vv.size() == 0)return "Wrong number of arguments for procedure /";
    stringstream ss;
    double sum = strtod(vv[0].c_str(), NULL);
    for (size_t i = 1; i < vv.size(); i++)sum /= strtod(vv[i].c_str(), NULL);
    ss << sum;
    return ss.str();
}

//Product, e.g. (* aa bb cc ...)
string prod(vector<string>&vv) {
    if (vv.size() == 0)return "Wrong number of arguments for procedure *";
    stringstream ss;
    double sum = strtod(vv[0].c_str(), NULL);
    for (size_t i = 1; i < vv.size(); i++)sum *= strtod(vv[i].c_str(), NULL);
    ss << sum;
    return ss.str();
}

//Quit the interpreter, e.q. (quit) or (exit)
string scheme_quit(vector<string>&vv) {
    exit(1);
    return "ok";
}

//Logical operators: <, <=, >, >=, =, !=

string less_than(vector<string>&vv) {
    if (vv.size() == 1)return "#t";
    for (size_t i = 0; i < vv.size() - 1; i++) {
        if (!(strtod(vv[i].c_str(), NULL) < strtod(vv[i + 1].c_str(), NULL))) return "#f";
    }
    return "#t";
}

string less_or_equal(vector<string>&vv) {
    if (vv.size() == 1)return "#t";
    for (size_t i = 0; i < vv.size() - 1; i++)if (!(strtod(vv[i].c_str(), NULL) <= strtod(vv[i + 1].c_str(), NULL))) return "#f";
    return "#t";
}

string great_than(vector<string>&vv) {
    if (vv.size() == 1)return "#t";
    for (size_t i = 0; i < vv.size() - 1; i++)if (!(strtod(vv[i].c_str(), NULL) > strtod(vv[i + 1].c_str(), NULL))) return "#f";
    return "#t";
}

string great_or_equal(vector<string>&vv) {
    if (vv.size() == 1)return "#t";
    for (size_t i = 0; i < vv.size() - 1; i++)if (!(strtod(vv[i].c_str(), NULL) >= strtod(vv[i + 1].c_str(), NULL))) return "#f";
    return "#t";
}

string equall(vector<string>&vv) {
    if (vv.size() == 1)return "#t";
    for (size_t i = 0; i < vv.size() - 1; i++)if (!(strtod(vv[i].c_str(), NULL) == strtod(vv[i + 1].c_str(), NULL))) return "#f";
    return "#t";
}

string not_equal(vector<string>&vv) {
    if (vv.size() == 1)return "#t";
    for (size_t i = 0; i < vv.size() - 1; i++)if (!(strtod(vv[i].c_str(), NULL) != strtod(vv[i + 1].c_str(), NULL))) return "#f";
    return "#t";
}
