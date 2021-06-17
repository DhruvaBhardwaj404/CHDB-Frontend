#include "Client_DB.h"

Client_DB::Client_DB(asio::io_context &service,int index):socket(service)
{
    Id=index;

}

Client_DB::~Client_DB()
{
   // Self->disconnect_Client(Id);
   cout<<"destructor\n";
}

int Client_DB::connect_Handler(){
    if(socket.is_open()){
        strcpy(writeBuff,"{connection:open}");
        asio::write(socket,asio::buffer(writeBuff));
        read_Request();
    }
    return Id;
}


asio::ip::tcp::socket& Client_DB::get_Socket(){
    return socket;
}

void Client_DB::read_Request(){
   // cout<<"in read request\n";
    asio::read(socket,asio::buffer(readBuff),bind(read_Completion,_1,readBuff,_2));
    cout<<readBuff<<endl;
    strcpy(writeBuff,"{test:Test}");
    send_Data();
}

void Client_DB::send_Data(){
        write(socket,asio::buffer(writeBuff));
}

void Client_DB::ping(){
    cout<<"In Ping\n";
    disconnect_Handler();
}

void Client_DB::disconnect_Handler(){
    cout<<"In disconnect\n";
    socket.close();
}

