//Utility functions

//Print the Scheme prompt
void prompt();

//Read the user input character by character in a STL string.
string get_input();

//START_NOTE
//"replace_substr" and "clean_input" can be replaced by a more elegant regex solution
//unfortunateley gcc does not fully support regex (at the time of this implementation)
//Visual Studio 2010 fully supports regex
//END_NOTE

//Replace substring target with substring res in string inp
void replace_substr(string &inp, string target, string res);

//Split the input string in components and store them in a STL vector of strings
vector<string> clean_input(string &str);

//START_NOTE
//This ugly hack should be replaced with a regex that can decide if we have int,double or complex numbers
//END_NOTE
//Check if the string contains a number
bool number(string inp);
