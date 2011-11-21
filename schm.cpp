//Simple Scheme interpreter

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "utils.h"
#include "PList.h"
#include "Procedure.h"
#include "Object.h"
#include "Procedures.h"
#include "Cell.h"

typedef map<string, Object> Environment;

string apply_proc(Procedure &proc, PList &args, Environment env);
Cell eval(PList &pp, Environment &env);
string apply_proc(Procedure &proc, PList &args, Environment env);
void REPL(Environment &env);

bool show_err1_flag = true;
bool show_err2_flag = true;

//START_NOTE
//It will be nice to implement some history for the commands, this way a user won't be forced to retype again a command.
//No plan for implementing this now.
//If you want to use syntax highlighting, paranthese matching etc... you can use schm from Emacs!
//END_NOTE

Cell eval(PList &pp, Environment &env) {
    int N = pp.size();
    if (N == 1) { //Check for symbol, constant literal, procedure with no argument
        if (pp.elem(0) == "(" && pp.elem(pp.full_size() - 1) == ")") {
            PList aux = pp.get(0);
            string inp = aux.elem(0);
            for (int i = 1; i < pp.full_size() - 2; i++)inp = inp + pp.elem(i);
            //Check for procedure with no argument, e.g. (quit)
            if (env.find(inp) != env.end()) {
                if (env[inp].get_kind() == "procedure" && env[inp].check_native_procedure() == true) return env[inp].apply();
                else return env[inp].get_value();
            } else {
                return (("Error! Unbound variable: " + inp));
            }
        } else {
            string inp = pp.elem(0);
            //Check if character
            if (inp[0] == '#' && inp[1] == '\\')return Cell("character type not yet implemented");
            //Check if string
            if (inp[0] == '\"' && inp[inp.size() - 1] == '\"')return inp;
            //Check if number
            if (number(inp))return inp;
            //Check if variable or procedure
            if (env.find(inp) != env.end()) {
                if (env[inp].get_kind() == "variable")return env[inp].get_value();
                else {
                    if (show_err1_flag)cout << env[inp].get_kind() << " ";
                    show_err1_flag = true;
                    return inp;
                }
            } else {
                string res;
                if (show_err2_flag)res = "Error! Unbound variable: " + inp;
                show_err2_flag = true;
                return res;
            }
        }
    } else {
        show_err1_flag = false;
        show_err2_flag = false;
        string proc;
        PList aux = pp.get(0);
        if (aux.size() == 1) proc = aux.elem(0);
        else {
            PList aux2 = aux.get(0);
            string tst = aux2.elem(0);
            if (tst == "lambda") {
                Procedure anonymous = Procedure(aux);
                //Collect the arguments of the lambda expression:
                PList args;
                args.puts("(");
                for (int i = 1; i < N; i++) {
                    PList piece = pp.get(i);
                    string res = (eval(piece, env)).get_str();
                    args.puts(res);
                }
                args.puts(")");
                return apply_proc(anonymous, args, env);
            } else {
                proc = (eval(aux, env)).get_str();
            }
        }
        if (proc == "define") {
            if (pp.size() != 3)return Cell("Ill-formed special form: define");
            else {
                string name = (pp.get(1)).elem(0);
                PList value = pp.get(2);
                Cell res = eval(value, env);
                if (res.get_str() == "") {
                    Procedure prr = res.get_proc();
                    env[name] = prr;
                } else {
                    string stt = res.get_str();
                    env[name] = stt;
                }
                return Cell("");
            }
        } else if (proc == "set!") {
            if (pp.size() != 3)return Cell("Ill-formed special form: set!");
            else {
                string name = (pp.get(1)).elem(0);
                if (env.find(name) == env.end()) {
                    return Cell("Error! Unbound variable: " + name);
                }
                PList value = pp.get(2);
                string res = (eval(value, env)).get_str();
                env[name] = res;
                return Cell("");
            }
        } else if (proc == "quote") {
            if (pp.size() != 2)return Cell("Ill-formed special form: quote");
            else {
                PList value = pp.get(1);
                return value.toString();
            }
        } else if (proc == "if") {
            if (pp.size() == 3) {
                PList cond = pp.get(1);
                PList if_true = pp.get(2);
                string aux = (eval(cond, env)).get_str();
                //If cond is a number evaluate the TRUE branch, if cond is a boolean evaluate accordingly
                if (number(aux))return eval(if_true, env);
                if (aux == "#t")return eval(if_true, env);
                else return Cell("");
            }
            if (pp.size() == 4) {
                PList cond = pp.get(1);
                PList if_true = pp.get(2);
                PList if_false = pp.get(3);
                string aux = (eval(cond, env)).get_str();
                //If cond is a number evaluate the TRUE branch, if cond is a boolean evaluate accordingly
                if (number(aux))return eval(if_true, env);
                if (aux == "#t")return eval(if_true, env);
                else return eval(if_false, env);
            } else {
                return Cell("Ill-formed special form: if");
            }
        } else if (proc == "lambda") {
            Procedure pr = Procedure(pp);
            return pr;
        } else if (proc == "begin") {
            if (pp.size() < 2)return Cell("Ill-formed special form: begin");
            string res;
            for (int i = 1; i < pp.size(); i++) {
                PList aux = pp.get(i);
                res = (eval(aux, env)).get_str();
            }
            return res;
        } else {
            PList exps;
            exps.puts("(");
            for (int i = 0; i < N; i++) {
                PList piece = pp.get(i);
                string aux = (eval(piece, env)).get_str();
                if (aux == "")aux = (piece.get(0)).elem(0);
                exps.puts(aux);
            }
            exps.puts(")");
            string pr = (exps.get(0)).elem(0);
            vector<string>args;
            for (int i = 1; i < exps.size(); i++)args.push_back((exps.get(i)).elem(0));
            if (env.find(pr) != env.end()) {
                if (env[pr].check_native_procedure()) {
                    return env[pr].apply(args);
                } else {
                    Procedure prt = env[pr].get_proc();
                    PList argss;
                    argss.puts("(");
                    for (int i = 1; i < N; i++) {
                        PList piece = pp.get(i);
                        string res = (eval(piece, env)).get_str();
                        argss.puts(res);
                    }
                    argss.puts(")");
                    return apply_proc(prt, argss, env);
                }

            } else {
                return Cell("Error! Unbound variable: " + pr);
            }
        }
    }
}

//Use this for named Scheme procedures, e.g. (define square (lambda (x) (* x x)))

string apply_proc(Procedure &proc, PList &args, Environment env) {
    PList arg_list = proc.get_arg_list();
    PList body = proc.get_body();
    for (int i = 0; i < args.size(); i++) {
        string aux = (arg_list.get(i)).elem(0);
        PList piece = args.get(i);
        string stt = (eval(piece, env)).get_str();
        env[aux] = stt;
    }
    string res = (eval(body, env)).get_str();
    return res;
}


//Simple REPL (read - evaluate - print).

void REPL(Environment &env) {
    prompt();
    for (;;) {
        show_err1_flag = true;
        show_err2_flag = true;
        string inp = get_input();
        if (inp == "")continue; //if the input buffer is empty go to the start of the for loop
        vector<string>out = clean_input(inp);
        //Evaluate an expression and print the result
        PList pp = PList(out);
        string res = (eval(pp, env)).get_str();
        if (res == "") {
            prompt();
            continue;
        }
        cout << res << endl;
        prompt();
    }
}

//Start the interpreter and load the predefined procedures

int main() {
    Environment env;
    env["+"] = add;
    env["-"] = diff;
    env["*"] = prod;
    env["/"] = divv;
    env["exit"] = scheme_quit;
    env["quit"] = scheme_quit;
    env["="] = equall;
    env["!="] = not_equal;
    env["<"] = less_than;
    env["<="] = less_or_equal;
    env[">"] = great_than;
    env[">="] = great_or_equal;
    env["print"] = print;

    string ss = "Ill formed special form: lambda.";
    env["lambda"] = ss;
    ss = "Ill formed special form: quote.";
    env["quote"] = ss;
    ss = "Ill formed special form: begin.";
    env["begin"] = ss;
    ss = "Ill formed special form: set!.";
    env["set!"] = ss;
    ss = "Ill formed special form: define.";
    env["define"] = ss;
    ss = "Ill formed special form: if.";
    env["if"] = ss;

    REPL(env);
    return (0);
}
