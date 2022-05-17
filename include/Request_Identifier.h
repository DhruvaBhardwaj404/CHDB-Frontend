#ifndef REQUEST_IDENTIFIER_H
#define REQUEST_IDENTIFIER_H


#include<asio.hpp>
#include<iostream>
#include"paramDefinitions.h"

using namespace std;

class Request_Identifier
{
    public:
        Request_Identifier();
        virtual ~Request_Identifier();

    private:
        asio::io_context service;
        asio::ip::tcp::socket AH,CH;
};

#endif // REQUEST_IDENTIFIER_H
