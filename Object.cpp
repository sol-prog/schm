//Class to store a native defined procedures (C++), Scheme defined procedures and strings

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "PList.h"
#include "Procedure.h"
#include "Object.h"

Object::Object() {
}

//Store a string
Object::Object(string &ss) {
    value = ss;
    kind = "variable";
    pp = NULL;
    native_proc = false;
}

//Store a pointer to a C++ function (this can be accessed from Scheme)
Object::Object(string(*p_)(vector<string>&)) {
    pp = p_;
    kind = "procedure";
    value = "";
    native_proc = true;
}

//Store a Scheme defined procedure
Object::Object(Procedure &procedure) {
    proc = procedure;
    kind = "procedure";
    value = "";
    native_proc = false;
}

//Get the type of data stored - variable or procedure
string Object::get_kind() {
    return kind;
}

//Get the value stored
string Object::get_value() {
    return value;
}

//Return true if the procedure is native (C++) and false if it was defined in Scheme
bool Object::check_native_procedure() {
    return native_proc;
}

//Run the current procedure with the arguments V
string Object::apply(vector<string>&V) {
    return pp(V);
}

//Run the current procedure with no arguments
string Object::apply() {
    vector<string>V;
    return pp(V);
}

//Get the list of arguments of the current procedure 
PList Object::get_arg_list() {
    return proc.get_arg_list();
}

//Get the body of the current procedure
PList Object::get_body() {
    return proc.get_body();
}

//Get the Scheme procedure
Procedure Object::get_proc() {
    return proc;
}
