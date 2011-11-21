//Simple class to store a string or a procedure

#include <string>
#include <vector>

using namespace std;

#include "PList.h"
#include "Procedure.h"
#include "Cell.h"

Cell::Cell() {
}

//Init the Cell with a string
Cell::Cell(string aa) {
    st = aa;
}

//Init the Cell with a procedure
Cell::Cell(Procedure &procedure) {
    proc = procedure;
    st = "";
}

//Get the values stored in a Cell (string or procedure)

string Cell::get_str() {
    return st;
}

Procedure Cell::get_proc() {
    return proc;
}
