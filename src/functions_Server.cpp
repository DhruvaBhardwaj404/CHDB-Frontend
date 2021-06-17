#include "functions_Server.h"

bool functions_Server::read_Completion(asio::error_code err, string buffer,unsigned size){
    cout<<buffer<<" "<<size<<"\n";
    if(err){
        return 0;
    }
    if(size>=1024){
        return 0;
    }

    bool found=  (find(buffer.begin(),buffer.begin()+size,'}')!=buffer.end())?true:false;
    if(found)
        return 0;
    else
        return 1;
}


