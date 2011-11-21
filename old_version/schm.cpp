#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdlib>

using namespace std;

#include "utils.h"
#include "PList.h"
#include "Environment.h"
#include "Procedures.h"

bool show_err1_flag=true;
bool show_err2_flag=true;

//START_NOTE
//It will be nice to implement some history for the commands, this way a user won't be forced to retype again a command.
//No plan for implementing this now.
//END_NOTE

string eval(PList &pp,Environment &env){
    int N=pp.size();
    if(N==1){ //Check for symbol, constant literal, procedure with no argument
        if(pp.elem(0)=="(" &&  pp.elem(pp.full_size()-1)==")"){
            PList aux=pp.get(0); string inp=aux.elem(0);
            //Check for procedure with no argument, e.g. (quit)
            if(env.find(inp)!=env.end()){
                return env[inp].apply();
            }
            else{
                return(("Error! Unbound variable: "+inp));
            }
        }
        else{
            string inp=pp.elem(0);
            //Check if character
            if(inp[0]=='#' && inp[1]=='\\')return "character type not yet implemented";
            //Check if string
            if(inp[0]=='\"' && inp[inp.size()-1]=='\"')return inp;
            //Check if number
            if(number(inp))return inp;
            //Check if variable or procedure
            if(env.find(inp)!=env.end()){
                if(env[inp].get_kind()=="variable")return env[inp].get_value();
                else{
                    if(show_err1_flag)cout<<env[inp].get_kind()<<" ";
                    show_err1_flag=true;
                    return inp;
                }
            }
            else{
                string res;
                if(show_err2_flag)res="Error! Unbound variable: "+inp;
                show_err2_flag=true;
                return res;
            }
        }
    }
    else{
        PList aux=pp.get(0); string proc=aux.elem(0);
        show_err1_flag=false;
        show_err2_flag=false;
        if     (proc=="quote"){return ((proc+" - not yet implemented!"));}
        else if(proc=="if"){return ((proc+" - not yet implemented!"));}
        else if(proc=="define"){return ((proc+" - not yet implemented!"));}
        else if(proc=="set!"){return ((proc+" - not yet implemented!"));}
        else if(proc=="if"){return ((proc+" - not yet implemented!"));}
        else if(proc=="lambda"){return ((proc+" - not yet implemented!"));}
        else if(proc=="begin"){return ((proc+" - not yet implemented!"));}
        else{
            PList exps; exps.puts("(");
            for(int i=0;i<N;i++){
                PList piece=pp.get(i);
                string aux=eval(piece,env);
                if(aux=="")aux=(piece.get(0)).elem(0);
                exps.puts(aux);
            }
            exps.puts(")");
            string pr=(exps.get(0)).elem(0);
            vector<string>args;
            for(int i=1;i<exps.size();i++)args.push_back((exps.get(i)).elem(0));
            if(env.find(pr)!=env.end())  return env[pr].apply(args);
            else{
                return(("Error! Unbound variable: "+pr));
            }
        }
    }
}


/*Simple REPL (read - evaluate - print).*/
void REPL(Environment &env){
    prompt();
    for(;;){
        show_err1_flag=true;
        show_err2_flag=true;
        string inp=get_input();
        if(inp=="")continue; //if the input buffer is empty go to the start of the for loop
        vector<string>out=clean_input(inp);
        //Evaluate an expression and print the result
        PList pp = PList(out);
        cout<<eval(pp,env)<<endl;
        prompt();
    }
}

/*Start the interpreter and load the predefined procedures*/
int main(){
    Environment env;
    env["+"]=add;
    env["-"]=diff;
    env["*"]=prod;
    env["/"]=div;
    env["exit"]=scheme_quit;
    env["quit"]=scheme_quit;
    env["="]=equal;
    env["!="]=not_equal;
    env["<"]=less_than;
    env["<="]=less_or_equal;
    env[">"]=great_than;
    env[">="]=great_or_equal;

    REPL(env);
    return(0);
}
