#ifndef REQUEST_EMITTER_H
#define REQUEST_EMITTER_H

#include<asio.hpp>
#include<iostream>
#include"paramDefinitions.h"

using namespace std;

class Request_Emitter
{
    public:
        Request_Emitter();
        virtual ~Request_Emitter();

    private:
        asio::io_context service;
        asio::ip::tcp::socket QP,AH;

};

#endif // REQUEST_EMITTER_H
