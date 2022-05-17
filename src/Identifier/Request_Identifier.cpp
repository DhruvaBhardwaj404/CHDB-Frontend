#include "Request_Identifier.h"

Request_Identifier::Request_Identifier():AH(service),CH(service)
{
    asio::ip::tcp::endpoint epA(asio::ip::address::from_string(SOCKET_ALIVE_IP),SOCKET_ALIVE_PORT),
    epC(asio::ip::address::from_string(SOCKET_CONHAN_IP),SOCKET_CONHAN_PORT);
    asio::error_code errC,errA;

    CH.open(asio::ip::tcp::v4());
    CH.connect(epC,errC);
    if(errC.value()!=0){
        cout<<"[Request Identifier > Constructor] Couldn't intialise CH socket\n";
    }

    AH.open(asio::ip::tcp::v4());
    AH.connect(epA,errA);
    if(errA.value()!=0){
        cout<<"[Request Identifier > Constructor] Couldn't intialise AH socket\n";
    }
}

Request_Identifier::~Request_Identifier()
{
    //dtor
}
