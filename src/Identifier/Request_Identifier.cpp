#include "Request_Identifier.h"

Request_Identifier::Request_Identifier():AH(service),CH(service)
{
    asio::ip::tcp::endpoint epA(asio::ip::address::from_string(SOCKET_ALIVE_IP),SOCKET_ALIVE_PORT),
    epC(asio::ip::address::from_string(SOCKET_CONHAN_IP),SOCKET_CONHAN_PORT);
    asio::error_code errC,errA;

    CH.open(asio::ip::tcp::v4());
    CH.connect(epC,errC);
    while(errC.value()){
        CH.connect(epC,errC);
    }

    AH.open(asio::ip::tcp::v4());
    AH.connect(epA,errA);
    while(errA.value()){
        AH.connect(epA,errA);
    }

    if(DEBUG_RI){
        cout<<"[Request Identifier > Constructor] Connected\n";
    }
}

Request_Identifier::~Request_Identifier()
{
    //dtor
}


void Request_Identifier::send_AH(const string &head,const string &mess){
    memcpy(buffAH,(head+mess).c_str(),head.size()+mess.size()-2);
    AH.send(asio::buffer(buffAH,MAX_PAC_SIZE));

}
void Request_Identifier::send_CH(const string &head,const string &mess){
    memcpy(buffAH,(head+mess).c_str(),head.size()+mess.size()-2);
    CH.send(asio::buffer(buffAH,MAX_PAC_SIZE));
}
