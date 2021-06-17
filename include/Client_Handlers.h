#ifndef CLIENT_HANDLERS_H
#define CLIENT_HANDLERS_H
#include<iostream>
#include<future>
#include<bitset>
#include<mutex>
#include<memory>
#include<atomic>
#include"Client_DB.h"

#define MAX_CLIENTS_PER_THREAD 10

using namespace std;

class Client_Handlers
{
    public:
        Client_Handlers(int ID);
        void start_Handler();
        void add_Client(shared_ptr<Client_DB> client);
        vector<int> get_Released_Clients();
        void clear_Released_Clients();
        unsigned int get_Slots();
        void stop_Thread();
        Client_Handlers* return_Self();
        virtual ~Client_Handlers();

    private:
        vector<short unsigned > empty_slots;
        vector<future<int>> clients;
        bitset<MAX_CLIENTS_PER_THREAD> used_slots;
        vector<int> released_Clients;
        atomic<unsigned int> slots;
        atomic<bool> running;
        mutex es;
        int han_ID;
};

#endif // CLIENT_HANDLERS_H
