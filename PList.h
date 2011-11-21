//Class to store and process an s-expression
//internally this is a vector of strings
class PList {
    vector<string>store;

public:
    PList();

    //Init a PList from a vector of strings
    PList(vector<string>&vv);

    //Init a PList from a string
    PList(string &ss);

    //Print the content of an s-expression
    void print();

    //Convert the contents to a single string
    string toString();

    //Get a copy of the vector uses to store the PList
    vector<string> get_store();

    //Clear the contents
    void clear();

    //Get the number of s-expressions contained on a level
    //for example: 
    //(+ aa bb) will return 3
    //(+ (- 2 3)) will return 2
    size_t size();

    //Get the sub PList stored at pos
    //e.g. (+ (- 2 3) (* 1 1)) get(0) will return "+"
    PList get(size_t pos);

    //Get the full size of vector used to store the PList
    size_t full_size();

    //Get the elem at pos from the vector used to store the PList
    string elem(size_t pos);

    //Add a string at the end of the current vector
    void puts(string ss);
    ~PList();
};
