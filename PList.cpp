//Class to store and process an s-expression
//internally this is a vector of strings
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PList.h"

PList::PList() {
}

//Init a PList from a vector of strings
PList::PList(vector<string>&vv) {
    store = vv;
}

//Init a PList from a string
PList::PList(string &ss) {
    store.push_back("(");
    store.push_back(ss);
    store.push_back(")");
}

//Print the content of an s-expression
void PList::print() {
    for (size_t i = 0; i < store.size(); i++)
        cout << store[i] << " ";
    cout << endl;
}

//Convert the contents to a single string
string PList::toString() {
    string aux = "";
    for (size_t i = 0; i < store.size(); i++)aux = aux + store[i] + " ";
    return aux;
}

//Get a copy of the vector uses to store the PList
vector<string> PList::get_store() {
    return store;
}

//Clear the contents
void PList::clear() {
    store.clear();
}

//Get the number of s-expressions contained on a level
//for example: 
//(+ aa bb) will return 3
//(+ (- 2 3)) will return 2
size_t PList::size() {
    size_t nn = 0, flag = 0;
    size_t left = 0, right = 0;
    if (store.size() == 0)return nn;
    if (store.size() == 1) {
        nn = 1;
        return nn;
    }
    for (size_t i = 1; i < store.size() - 1; i++) {
        if (store[i] == "(")left++;
        if (store[i] == ")")right++;

        if (left == 0 && left == right)nn++;
        else if (left == 1 && flag == 0) {
            nn++;
            flag = 1;
        } else if (left != 0 && left == right) {
            flag = 0;
            left = 0;
            right = 0;
        }
    }
    return nn;
}

//Get the sub PList stored at pos
//e.g. (+ (- 2 3) (* 1 1)) get(0) will return "+"
PList PList::get(size_t pos) {
    PList pp;
    if (store.size() == 1) pp = *this;
    size_t nn = 0, flag = 0, flag_read = 0;
    size_t left = 0, right = 0;
    for (size_t i = 1; i < store.size() - 1; i++) {
        if (store[i] == "(")left++;
        if (store[i] == ")")right++;

        if (left == 0 && left == right) {
            nn++;
            if (pos == nn - 1) {
                pp.store.push_back(store[i]);
                break;
            }
        } else if (left == 1 && flag == 0) {
            nn++;
            flag = 1;
            if (pos == nn - 1) {
                flag_read = 1;
            }
        } else if (left != 0 && left == right) {
            flag = 0;
            left = 0;
            right = 0;
            flag_read = 0;
        } else if (flag_read == 1)pp.store.push_back(store[i]);
    }
    if (pp.store.size() == 1) return pp;
    else {
        PList cc;
        cc.store.push_back("(");
        for (size_t ii = 0; ii < pp.full_size(); ii++)cc.store.push_back(pp.store[ii]);
        cc.store.push_back(")");
        return cc;
    }
}

//Get the full size of vector used to store the PList
size_t PList::full_size() {
    return store.size();
}

//Get the elem at pos from the vector used to store the PList
string PList::elem(size_t pos) {
    string inp = store[pos];
    //Clean all trailing empty spaces
    while (inp[inp.size() - 1] == ' ')inp.erase(inp.size() - 1); //clean some empty spaces
    return inp;
}

//Add a string at the end of the current vector
void PList::puts(string ss) {
    store.push_back(ss);
}

PList::~PList() {
    store.clear();
}
