//Simple class to store a string or a procedure
class Cell {
    string st;
    Procedure proc;

public:
    Cell();

    //Init the Cell with a string
    Cell(string aa);

    //Init the Cell with a procedure
    Cell(Procedure &procedure);
    
    //Get the values stored in a Cell (string or procedure)
    string get_str();
    Procedure get_proc();
};
