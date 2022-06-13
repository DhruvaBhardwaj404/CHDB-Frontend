#ifndef REQUEST_EMITTER_H
#define REQUEST_EMITTER_H

#include"paramDefinitions.h"

using namespace std;

extern mutex MRE;
extern list<string> mesRE;

class Request_Emitter
{
    public:
        Request_Emitter();
        ~Request_Emitter();
        void run_RE();
        void fetch_QP();
        void fetch_AH();
        void fetch_CH();
        void mesRE_Handler();
    private:
        char buffQP[MAX_PAC_SIZE],buffAH[MAX_PAC_SIZE],buffCH[MAX_PAC_SIZE];
        list<string> mesQP,mesAH,mesCH;
        asio::io_context service;
        asio::ip::tcp::socket QP,AH,CH;
        atomic<bool> running;
        mutex MQP,MAH,MCH;

};

#endif // REQUEST_EMITTER_H
