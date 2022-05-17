#ifndef LISTENER_H
#define LISTENER_H

#include<asio.hpp>
#include"Request_Emitter.h"
#include"Request_Identifier.h"

class Listener
{
    public:
        Listener();
        virtual ~Listener();

    private:
        Request_Emitter RE;
        Request_Identifier RI;

};

#endif // LISTENER_H
