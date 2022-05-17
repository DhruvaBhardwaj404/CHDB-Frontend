#include <iostream>
#include<asio.hpp>
#include"Server_DB.h"
#include<boost/interprocess/managed_shared_memory.hpp>
#include<sys/types.h>
#include"Listener.h"

#define DEBUG_MAIN true

using namespace std;

pid_t QH,AH,CH;
boost::interprocess::managed_shared_memory memQH,memAH,memCH;

void init_SharedMem(){
}

int main()
{
    Listener Server;
    while(true){
        ;
    }

}


//TODO: SET up connection with BE
