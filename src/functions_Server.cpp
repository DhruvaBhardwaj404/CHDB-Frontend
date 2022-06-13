#include "functions_Server.h"

pair<tuple<unsigned long long,bool,string>,string> functions_Server::separate_header(string data){
    pair<tuple<unsigned long long,bool,string>,string> res;
    string IP,temp;
    unsigned long long num;
    bool mode;
    int i;
    if(data[0]=='<' && data[1]=='<' && data[1]=='<' && data[2]=='!'){
        bool NRQ=false;
        for(i=3;i<data.size();i++){
            if(data[i]==':'){
                if(temp=="NRQ"){
                    NRQ=true;
                }
            }
            else if(data[i]==','){
                if(NRQ==true){
                    num= stoull(temp);
                }
                temp.clear();
                NRQ=false;
            }
            else if(data[i]=='>'){
                IP=temp;
                i++;
                break;
            }
            else{
                if(NRQ==true){
                    if(data[i]=='A'){
                        mode=false;
                    }
                    else if(data[i]=='U'){
                        mode=true;
                    }
                    else{
                        temp+=data[i];
                    }
                }
                temp+=data[i];
            }
        }
    }
    else
        throw "FORMAT INCORRECT";

    res={{num,mode,IP},string(data.begin()+i,data.end())};
    return res;
}


