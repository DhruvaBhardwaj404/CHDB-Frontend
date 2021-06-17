#ifndef CLIENT_DB_H
#define CLIENT_DB_H
#include<asio.hpp>
#include<memory>
#include<iostream>
#include<future>
#include<cstring>
#include"functions_Server.h"


using namespace functions_Server;
using namespace std::placeholders;
using namespace std;

class Client_DB:public enable_shared_from_this<Client_DB>
{
    public:
        Client_DB(asio::io_context &service,int index);
        int connect_Handler();
        void read_Request();
        void send_Data();
        void ping();
        void disconnect_Handler();
        asio::ip::tcp::socket& get_Socket();
        virtual ~Client_DB();

    private:
        int Id;
        atomic<bool> con;
        asio::ip::tcp::socket socket;
        char readBuff[1024],writeBuff[1024];
};

#endif // CLIENT_DB_H
