#include "Request_Emitter.h"

Request_Emitter::Request_Emitter():QP(service),
                                    AH(service),
                                    CH(service)
{

    asio::ip::tcp::endpoint epA(asio::ip::address::from_string(SOCKET_ALIVE_IP),SOCKET_ALIVE_PORT),
                            epQ(asio::ip::address::from_string(SOCKET_QPAR_IP),SOCKET_QPAR_PORT),
                            epC(asio::ip::address::from_string(SOCKET_CONHAN_IP),SOCKET_CONHAN_PORT);
    asio::error_code errQ,errA,errC;



    AH.open(asio::ip::tcp::v4());
    AH.connect(epA,errA);

    while(errA.value()){
        AH.connect(epA,errA);
    }

    CH.open(asio::ip::tcp::v4());
    CH.connect(epC,errC);
    while(errC.value()){
        CH.connect(epC,errC);
    }

    QP.open(asio::ip::tcp::v4());
    QP.connect(epQ,errQ);
    while(errQ.value()){
        QP.connect(epQ,errQ);
    }
    if(DEBUG_RE){
        cout<<"[Request Emitter > Constructor] Connected \n";
    }
}

Request_Emitter::~Request_Emitter()
{
    //dtor
}

void Request_Emitter::run_RE(){
    if(DEBUG_RE){
        cout<<"[Request Emitter > run RE] Ping\n";
    }

    future<void> QP_hand    =   async(std::launch::async,bind(&Request_Emitter::fetch_QP,this)),
                 AH_hand    =   async(std::launch::async,bind(&Request_Emitter::fetch_AH,this)),
                 CH_hand    =   async(std::launch::async,bind(&Request_Emitter::fetch_AH,this));

}


void Request_Emitter::fetch_QP(){
    while(true){
        QP.read_some(asio::buffer(buffQP,MAX_PAC_SIZE));
        MQP.lock();
        mesQP.push_back(buffQP);
        MQP.unlock();
    }
}

void Request_Emitter::fetch_AH(){
    while(true){
        AH.read_some(asio::buffer(buffQP,MAX_PAC_SIZE));
        MAH.lock();
        mesAH.push_back(buffQP);
        MAH.unlock();
    }

}

void Request_Emitter::fetch_CH(){
    while(true){
        CH.read_some(asio::buffer(buffQP,MAX_PAC_SIZE));
        MCH.lock();
        mesCH.push_back(buffQP);
        MCH.unlock();
    }
}

void Request_Emitter::mesRE_Handler(){
    while(running){
        string temp;
        if(!mesQP.empty()){
            MQP.lock();
                temp=mesQP.front();
                mesQP.pop_front();
            MQP.unlock();
            MRE.lock();
                mesRE.push_back(temp);
            MRE.unlock();
        }

        if(!mesAH.empty()){
            MAH.lock();
                temp=mesAH.front();
                mesAH.pop_front();
            MAH.unlock();
            MRE.lock();
                mesRE.push_back(temp);
            MRE.unlock();
        }

        if(!mesCH.empty()){
            MCH.lock();
                temp=mesCH.front();
                mesCH.pop_front();
            MCH.unlock();
            MRE.lock();
                mesRE.push_back(temp);
            MRE.unlock();
        }
    }
}
