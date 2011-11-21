class Object{
	string(*pp)(vector<string>&);
	string(*rr)();
	string value;
	string kind;
	
	public:
		Object(){};
		Object(string ss){value=ss;kind="variable";pp=NULL;};
        Object(string(*p_)(vector<string>&)){pp=p_;kind="procedure";value="";};
		string get_kind(){
			return kind;
		}
        string get_value(){
            return value;
        }
        string apply(vector<string>&V){
            return pp(V);
        }
        string apply(){
        	vector<string>V;
            return pp(V);
        }        
};

typedef map<string,Object> Environment;
