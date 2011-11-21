//Class used to store a Scheme defined procedure
//the procedure is stored in two PLists: arguments and body
class Procedure {
    PList arg_list;
    PList body;

    //Add a PList to the end of the vector V
    void addPList(vector<string>&V, PList a);

public:
    Procedure();

    //Init a procedure from a PList
    Procedure(PList &pp);

    //Get the list of arguments of the current procedure 
    PList get_arg_list();

    //Get the body of the current procedure
    PList get_body();
};
