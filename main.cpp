#include"paramDefinitions.h"
#include"Listener.h"
#include<gtest/gtest.h>

#define GLOBAL_DEBUG false
#define DEBUG_MAIN true

using namespace std;

list<string> mesRE;
mutex MRE;

int main(int argc, char **argv)
{
        char banner[6][50]= {{"|==============================================|"},
                             {"|         Cloud-Hybird Database FE             |"},
                             {"|                 MEGH KOSH                    |"},
                             {"|                Created by-                   |"},
                             {"|                  Dhruva                      |"},
                             {"|==============================================|"}
                            };

        for(int a=0; a<6; a++)
        {
            cout<<"\t\t\t"<<banner[a]<<endl;
        }
    Listener Server;
    Server.run_Listener();
}


//TODO: SET up connection with BE
