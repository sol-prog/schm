//Basic procedures:
//Each procedure receives as input a vector of strings and returns a string

//Print one or more variables; e.g. (print aa), (print aa bb cc)
string print(vector<string>&vv);

//Add one or more variables; e.g. (+ aa), (+ aa bb cc)
string add(vector<string>&vv);

//Diff, e.g.: (- aa bb)
string diff(vector<string>&vv);

//Division, e.g. (/ aa bb cc ...)
string divv(vector<string>&vv);

//Product, e.g. (* aa bb cc ...)
string prod(vector<string>&vv);

//Quit the interpreter, e.q. (quit) or (exit)
string scheme_quit(vector<string>&vv);

//Logical operators: <, <=, >, >=, =, !=
 
string less_than(vector<string>&vv);

string less_or_equal(vector<string>&vv);

string great_than(vector<string>&vv);

string great_or_equal(vector<string>&vv);

string equall(vector<string>&vv);

string not_equal(vector<string>&vv);
