#include "Server_DB.h"

Server_DB::Server_DB()
{
    running=true;
    busy_Handlers=0;
    for(unsigned int i=0;i<MAX_CLIENTS_HANDLER;i++){
        handlers.push_back({});
        avail_Handlers.push_back(MAX_CLIENTS_PER_THREAD);
    }
    for(unsigned int i=0;i<MAX_CLIENTS_HANDLER*MAX_CLIENTS_PER_THREAD;i++){
        avail_Clients.push_back(i);
        clients.push_back({});
    }
}

Server_DB::~Server_DB()
{
    //dtor
}

void Server_DB::Run()
{
    acceptor = new asio::ip::tcp::acceptor(service,asio::ip::tcp::endpoint(asio::ip::tcp::v4(),8069));
    cout<<"Server running on port:8069\n";

    for(unsigned int i=0;i<MAX_CLIENTS_HANDLER;i++){
        handlers[i]=shared_ptr<Client_Handlers>(new Client_Handlers(i));
        handler_Threads.push_back(thread(&Client_Handlers::start_Handler,handlers[i]->return_Self()));
    }
    thread get_Con(&Server_DB::add_Con,this);
    future<void> thandler = async(launch::async,&Server_DB::thread_handler,this);
    get_Con.join();
}

void Server_DB::add_Con()
{
    int index,c=0;
    cout<<"here";
    while(running)
    {

        if(avail_Clients.size()>0)
        {
            ch.lock();
            index=avail_Clients.back();
            avail_Clients.pop_back();
            clients[index]= (shared_ptr<Client_DB>(new Client_DB(service,index)));
            ch.unlock();
            acceptor->accept(clients[index]->get_Socket());
            cout<<"accepted\n";
            if(busy_Handlers<MAX_CLIENTS_HANDLER)
            {
                while(true){
                    if(avail_Handlers[c]==0){
                        c++;
                        if(c==MAX_CLIENTS_HANDLER)
                            c==0;
                    }
                    else{
                        handlers[c]->add_Client(clients[index]);
                        c=c==MAX_CLIENTS_HANDLER-1?0:c+1;
                        break;

                    }
                }
            }

            else
            {
                cout<<"in wait for thread";
                wait_For_Thread();
            }
        }
    }
}

void Server_DB::wait_For_Thread()
{
;
}



void Server_DB::thread_handler(){
    //cout<<"In thread handler\n";
    unsigned int as;
    vector<int> rs;

    while(running){

        for(int i=0;i<MAX_CLIENTS_HANDLER;i++){
            as=handlers[i]->get_Slots();
            rs=handlers[i]->get_Released_Clients();

            if(rs.size()>0){
                handlers[i]->clear_Released_Clients();
                ch.lock();
                for(auto x : rs){
                    avail_Clients.push_back(x);
                    clients[x].reset();
                }
                ch.unlock();
            }
            if(avail_Handlers[i]!=as){
                ah.lock();
                if(as==0)
                    busy_Handlers++;
                if(avail_Handlers[i]==0)
                    busy_Handlers--;

                avail_Handlers[i]=as;
                ah.unlock();
            }

        }
    }
}
