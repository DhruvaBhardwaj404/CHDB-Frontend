#ifndef REQUEST_IDENTIFIER_H
#define REQUEST_IDENTIFIER_H

#include"paramDefinitions.h"
#define DEBUG_RI true
using namespace std;

class Request_Identifier
{
    public:
        Request_Identifier();
        ~Request_Identifier();
        void send_AH(const string &head,const string &mess);
        void send_CH(const string &head,const string &mess);

    private:
        char buffAH[MAX_PAC_SIZE],buffCH[MAX_PAC_SIZE];
        asio::io_context service;
        asio::ip::tcp::socket AH,CH;
};

#endif // REQUEST_IDENTIFIER_H
