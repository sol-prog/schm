class PList{
    vector<string>store;
    
    public:
    PList(){}
    PList(vector<string>vv){store=vv;}
    void print(){for(size_t i=0;i<store.size();i++)cout<<store[i]<<" ";cout<<endl;}
    string get_store(){string aux=""; for(size_t i=0;i<store.size();i++)aux=aux+store[i]+" ";return aux;}
    void clear(){store.clear();}
    
    size_t size(){        
        size_t nn=0,flag=0;
        size_t left=0,right=0;
        if(store.size()==0)return nn;
        if(store.size()==1){nn=1; return nn;}
        for(size_t i=1;i<store.size()-1;i++){
            if(store[i]=="(")left++;
            if(store[i]==")")right++;
            
            if(left==0 && left==right)nn++;
            else if(left==1 && flag==0){nn++; flag=1;}
            else if(left!=0 && left==right){flag=0;left=0;right=0;}
        }
        return nn;
    }
        
    PList get(size_t pos){
        PList pp;
        if(store.size()==1){pp=*this;}
        size_t nn=0,flag=0,flag_read=0;
        size_t left=0,right=0;
        for(size_t i=1;i<store.size()-1;i++){
            if(store[i]=="(")left++;
            if(store[i]==")")right++;
            
            if(left==0 && left==right){
                nn++;
                if(pos==nn-1){
                    pp.store.push_back(store[i]);
                    break;
                }
            }
            else if(left==1 && flag==0){
                nn++; flag=1;
                if(pos==nn-1){
                    flag_read=1;
                }
            }
            else if(left!=0 && left==right){flag=0;left=0;right=0;flag_read=0;}
            else if(flag_read==1)pp.store.push_back(store[i]);
        }
        if(pp.store.size()==1)  return pp;
        else{
            PList cc;
            cc.store.push_back("(");
            for(size_t ii=0;ii<pp.full_size();ii++)cc.store.push_back(pp.store[ii]);
            cc.store.push_back(")");
            return cc;
        }
    }
            
    size_t full_size(){
        return store.size();
    }
    
    string elem(size_t pos){
        string inp=store[pos];
        //Clean all trailing empty spaces
        while(inp[inp.size()-1]==' ')inp.erase(inp.size()-1); //clean some empty spaces
        return inp;
    }
    
    void puts(string ss){store.push_back(ss);}
    
   ~PList(){store.clear();}
};
