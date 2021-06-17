#include "Client_Handlers.h"


Client_Handlers::Client_Handlers(int ID)
{
    running=true;
    slots=MAX_CLIENTS_PER_THREAD;
    han_ID=ID;
    for(int i=0;i<MAX_CLIENTS_PER_THREAD;i++){
        empty_slots.push_back(i);
        clients.push_back({});
    }

}

Client_Handlers::~Client_Handlers()
{
    //dtor
}


void Client_Handlers::start_Handler(){
    //cout<<han_ID<<" handler\n";
    while(running){

        for(unsigned int i=0;i<MAX_CLIENTS_PER_THREAD;i++){
            if(used_slots[i]==1){
                if(clients[i].valid()){
                    es.lock();
                    released_Clients.push_back(clients[i].get());
                    empty_slots.push_back(i);
                    slots++;
                    es.unlock();
                }
            }
        }
    }
}

void Client_Handlers::add_Client(shared_ptr<Client_DB> client){
    cout<<han_ID<<" handler add client\n";
    es.lock();
    int index=empty_slots.back();
    empty_slots.pop_back();
    clients[index]= future<int>(async(bind(&Client_DB::connect_Handler,client)));
    used_slots[index]=1;
    slots--;
    es.unlock();
}

unsigned int Client_Handlers::get_Slots(){
    return slots;
}

void Client_Handlers::stop_Thread(){
    running=false;
}

Client_Handlers* Client_Handlers::return_Self(){
    return this;
}

vector<int> Client_Handlers::get_Released_Clients(){
    return released_Clients;
}

void Client_Handlers::clear_Released_Clients(){
    released_Clients.clear();
}
