
string add(vector<string>&vv){
    if(vv.size()==0)return "Wrong number of arguments for procedure +";
    stringstream ss;
    double sum=strtod(vv[0].c_str(),NULL);
    for(size_t i=1;i<vv.size();i++)sum+=strtod(vv[i].c_str(),NULL);
    ss<<sum;
    return ss.str();
}

string diff(vector<string>&vv){
    if(vv.size()==0)return "Wrong number of arguments for procedure -";
    stringstream ss;
    double sum=strtod(vv[0].c_str(),NULL);
    for(size_t i=1;i<vv.size();i++)sum-=strtod(vv[i].c_str(),NULL);
    ss<<sum;
    return ss.str();
}

string div(vector<string>&vv){
    if(vv.size()==0)return "Wrong number of arguments for procedure /";
    stringstream ss;
    double sum=strtod(vv[0].c_str(),NULL);
    for(size_t i=1;i<vv.size();i++)sum/=strtod(vv[i].c_str(),NULL);
    ss<<sum;
    return ss.str();
}

string prod(vector<string>&vv){
    if(vv.size()==0)return "Wrong number of arguments for procedure *";
    stringstream ss;
    double sum=strtod(vv[0].c_str(),NULL);
    for(size_t i=1;i<vv.size();i++)sum*=strtod(vv[i].c_str(),NULL);
    ss<<sum;
    return ss.str();
}

string scheme_quit(vector<string>&vv){
    exit(1);
    return "ok";
}

string less_than(vector<string>&vv){
    if(vv.size()==1)return "#t";
    for(size_t i=0;i<vv.size()-1;i++){
        if(!(strtod(vv[i].c_str(),NULL)<strtod(vv[i+1].c_str(),NULL))) return "#f";
    }
    return "#t";
}

string less_or_equal(vector<string>&vv){
    if(vv.size()==1)return "#t";
    for(size_t i=0;i<vv.size()-1;i++)if(!(strtod(vv[i].c_str(),NULL)<=strtod(vv[i+1].c_str(),NULL))) return "#f";
    return "#t";
}

string great_than(vector<string>&vv){
    if(vv.size()==1)return "#t";
    for(size_t i=0;i<vv.size()-1;i++)if(!(strtod(vv[i].c_str(),NULL)>strtod(vv[i+1].c_str(),NULL))) return "#f";
    return "#t";
}

string great_or_equal(vector<string>&vv){
    if(vv.size()==1)return "#t";
    for(size_t i=0;i<vv.size()-1;i++)if(!(strtod(vv[i].c_str(),NULL)>=strtod(vv[i+1].c_str(),NULL))) return "#f";
    return "#t";
}


string equal(vector<string>&vv){
    if(vv.size()==1)return "#t";
    for(size_t i=0;i<vv.size()-1;i++)if(!(strtod(vv[i].c_str(),NULL)==strtod(vv[i+1].c_str(),NULL))) return "#f";
    return "#t";
}

string not_equal(vector<string>&vv){
    if(vv.size()==1)return "#t";
    for(size_t i=0;i<vv.size()-1;i++)if(!(strtod(vv[i].c_str(),NULL)!=strtod(vv[i+1].c_str(),NULL))) return "#f";
    return "#t";
}
