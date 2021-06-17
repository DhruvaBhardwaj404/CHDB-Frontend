#ifndef SERVER_DB_H
#define SERVER_DB_H
#include<asio.hpp>
#include<memory>
#include<thread>
#include<atomic>
#include<future>
#include<bitset>
#include<mutex>
#include"Client_DB.h"
#include"Client_Handlers.h"

#define MAX_CLIENTS 20
#define MAX_THREADS 2
#define MAX_QUEUED_CLIENTS 10
#define MAX_CLIENTS_HANDLER 2

using namespace std;

class Server_DB:public enable_shared_from_this<Server_DB>
{
    public:
        Server_DB();
        void Run();
        void add_Con();
        void wait_For_Thread();
        void thread_handler();
        virtual ~Server_DB();

    protected:

    private:
        atomic<bool> running;
        asio::io_context service;
        asio::ip::tcp::acceptor *acceptor;
        vector<thread> handler_Threads;
        vector<shared_ptr<Client_Handlers>> handlers;
        vector<shared_ptr<Client_DB>> clients;
        vector<short unsigned> avail_Handlers,avail_Clients;
        mutex ch,ah;
        unsigned int busy_Handlers;
};

#endif // SERVER_DB_H
