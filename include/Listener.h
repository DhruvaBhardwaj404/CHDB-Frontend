#ifndef LISTENER_H
#define LISTENER_H
#include"Request_Emitter.h"
#include"Request_Identifier.h"
#include"functions_Server.h"

typedef asio::detail::socket_option::integer<SOL_SOCKET, SO_RCVTIMEO> rcv_timeout_option;

extern list<string> mesRE;
extern mutex MRE;

using namespace functions_Server;

using namespace std;


class Listener
{
    public:
        Listener();
        void run_Listener();
        void admin_Acceptor();
        void user_Acceptor();
        void admin_Handler();
        void user_Handler();
        void remove_Inactive_Admin();
        void remove_Inactive_User();
        void user_Thread(unordered_map<string,Con_Detail>::iterator U);
        void admin_Thread(unordered_map<string,Con_Detail>::iterator U);
        void RE_Handler();
        ~Listener();

    private:
        asio::io_context service;
        asio::ip::tcp::acceptor AA,UA;
        list<asio::ip::tcp::socket> Usockets,Asockets;
        unordered_map<string,Con_Detail> User;
        unordered_map<string,Con_Detail > Admin;
        list< list<asio::ip::tcp::socket>::iterator > newA,newU;
        list<future<void>> userThreads,adminThreads;
        list<list<future<void> >::iterator> remUser,remAdmin;
        Request_Emitter RE;
        Request_Identifier RI;
        mutex AR,UR,MA,MU,TA,TU,NA,NU;
        vector<list<asio::ip::tcp::socket>::iterator> MapA,MapU;
        atomic<unsigned long long> reqNumA,reqNumU;
        atomic<bool> running;



};

#endif // LISTENER_H
