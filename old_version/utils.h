void prompt(){ cout<<"schm >>>"; }

/*Read the user input character by character in a STL string.*/
string get_input(){
    string inp;
    char tmp;
    int left=0,right=0,ll=0;
    for(;;){
        cin.get(tmp);
        //If you find ";" on a line ignore everything until the end of line (comment line)
        if(tmp==';'){
            while(tmp!='\n')cin.get(tmp);
        }
        if(tmp!='\n')inp+=tmp;
        if(tmp=='(')left++;
        else if(tmp==')')right++;
        else if(tmp=='\"')ll++;
        
        //At end of line (user has pressed Enter) check if you have un-matched parantheses or quotation marks
        if(tmp=='\n'){
            if(left==0 && right==0 && ll==0)break;
            if(left!=0 && (left==right) && (ll==0 || (ll&1)==0))break;
            if(left==0 && right==0 && (ll&1)==0)break;
            if((ll&1))inp+="\\n";
            else inp+=" ";
        }
    }
    return inp;
}

//START_NOTE
//"replace_substr" and "clean_input" can be replaced by a more elegant regex solution
//unfortunateley gcc does not fully support regex (at the time of this implementation)
//Visual Studio 2010 fully supports regex
//END_NOTE

/*Replace substring target with substring res in string inp*/
void replace_substr(string &inp,string target,string res){
    size_t ind=0;
    for(;;){
        ind=inp.find(target,ind);
        if(ind==string::npos)break;
        inp.replace(ind,1,res);
        ind+=res.length();
    }
}

/*Split the input string in components and store them in a STL vector of strings*/
vector<string> clean_input(string &str){
    replace_substr(str,"("," ( ");
    replace_substr(str,")"," ) ");
    
    stringstream ss(str);
    string aux;
    vector<string>init_pieces;
    while(ss>>aux) init_pieces.push_back(aux);
    if(str.find("\"")==string::npos)return init_pieces;
    //Treat the case of 'sentences'; for example "aaa bbb ccc" should not be broken into pieces
    vector<string>pieces;
    aux="";
    int flag=0;
    for(size_t i=0;i<init_pieces.size();i++){
        
        if(init_pieces[i].find("\"")!=string::npos){
            if(init_pieces[i][0]=='\"' && init_pieces[i][init_pieces[i].size()-1]=='\"'){
                pieces.push_back(init_pieces[i]);
                continue;
            }
            flag=1;
            if(init_pieces[i][0]=='\"')aux=init_pieces[i]+" ";
            else if(init_pieces[i][init_pieces[i].size()-1]=='\"'){
                aux+=init_pieces[i]+" ";
                pieces.push_back(aux);
                aux="";
                flag=0;
            }
            else
                aux+=init_pieces[i]+" ";
        }
        else
            if(flag==0){
                pieces.push_back(init_pieces[i]);
            }
            else
                aux+=init_pieces[i]+" ";
    }
    return pieces;
}

//START_NOTE
//This ugly hack should be replaced with a regex that can decide if we have int,double or complex numbers
//END_NOTE
/*Check if the string contains a number*/
bool number(string inp){
    char *pend;
    double tst=strtod(inp.c_str(),&pend);
    if(inp[0]!=(*pend))return true;
    else return false;
}
