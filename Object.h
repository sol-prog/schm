//Class to store a native defined procedures (C++), Scheme defined procedures and strings

class Object {
    string(*pp)(vector<string>&);
    Procedure proc;
    string value;
    string kind;
    bool native_proc;

public:
    Object();

    //Store a string
    Object(string &ss);

    //Store a pointer to a C++ function (this can be accessed from Scheme)
    Object(string(*p_)(vector<string>&));

    //Store a Scheme defined procedure
    Object(Procedure &procedure);

    //Get the type of data stored - variable or procedure
    string get_kind();

    //Get the value stored
    string get_value();

    //Return true if the procedure is native (C++) and false if it was defined in Scheme
    bool check_native_procedure();

    //Run the current procedure with the arguments V
    string apply(vector<string>&V);

    //Run the current procedure with no arguments
    string apply();

    //Get the list of arguments of the current procedure 
    PList get_arg_list();

    //Get the body of the current procedure
    PList get_body();

    //Get the Scheme procedure
    Procedure get_proc();
};
