#include "Request_Emitter.h"

Request_Emitter::Request_Emitter():QP(service),AH(service)
{

    asio::ip::tcp::endpoint epA(asio::ip::address::from_string(SOCKET_ALIVE_IP),SOCKET_ALIVE_PORT),
    epQ(asio::ip::address::from_string(SOCKET_QPAR_IP),SOCKET_QPAR_PORT);
    asio::error_code errQ,errA;

    QP.open(asio::ip::tcp::v4());
    QP.connect(epQ,errQ);
    if(errQ.value()!=0){
        cout<<"[Request Emitter > Constructor] Couldn't intialise QP socket\n";
    }

    AH.open(asio::ip::tcp::v4());
    AH.connect(epA,errA);
    if(errA.value()!=0){
        cout<<"[Request Emitter > Constructor] Couldn't intialise AH socket\n";
    }

}

Request_Emitter::~Request_Emitter()
{
    //dtor
}
