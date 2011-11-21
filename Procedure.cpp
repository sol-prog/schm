//Class used to store a Scheme defined procedure
//the procedure is stored in two PLists: arguments and body

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "PList.h"
#include "Procedure.h"

Procedure::Procedure() {
}

//Init a procedure from a PList
Procedure::Procedure(PList &pp) {
    arg_list = pp.get(1);
    vector<string>aux;
    aux.push_back("(");
    aux.push_back("begin");
    for (int i = 2; i < pp.size(); i++) {
        addPList(aux, pp.get(i));
    }
    aux.push_back(")");
    body = PList(aux);
}

//Add a PList to the end of the vector V
void Procedure::addPList(vector<string>&V, PList a) {
    vector<string>aux = a.get_store();
    for (int i = 0; i < aux.size(); i++) {
        V.push_back(aux[i]);
    }
}

//Get the list of arguments of the current procedure 
PList Procedure::get_arg_list() {
    return arg_list;
}

//Get the body of the current procedure
PList Procedure::get_body() {
    return body;
}
