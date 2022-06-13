#include "Listener.h"

Listener::Listener():AA(service),
                     UA(service),
                     MapA(MAX_PENDING_REQUEST_ADMINS),
                     MapU(MAX_PENDING_REQUEST_USERS)
{
    AA.open(asio::ip::tcp::v4());
    AA.bind(asio::ip::tcp::endpoint(asio::ip::address::from_string(ADMIN_ACC_IP),ADMIN_ACC_PORT));
    AA.listen();
    UA.open(asio::ip::tcp::v4());
    UA.bind(asio::ip::tcp::endpoint(asio::ip::address::from_string(CLIENT_ACC_IP),CLIENT_ACC_PORT));
    UA.listen();
    running=true;
}

Listener::~Listener()
{
    //dtor
}

/***
    Listener::run_Listener()
        Runs essentials methods for accepting and managing connections

***/


void Listener::run_Listener(){

    future<void> admin        = async( std::launch::async , bind(&Listener::admin_Acceptor, this ) ),
                 admin_Handler= async( std::launch::async , bind(&Listener::admin_Handler , this ) ),
                 user         = async( std::launch::async , bind(&Listener::user_Acceptor , this ) ),
                 user_Handler = async( std::launch::async , bind(&Listener::user_Handler  , this ) ),
                 RE_class     = async( std::launch::async , bind(&Request_Emitter::run_RE , &RE  ) ),
                 RE_Han       = async( std::launch::async , bind(&Listener::RE_Handler    , this ) ),
                 remove_Admin = async( std::launch::async , bind(&Listener::remove_Inactive_Admin  , this ) ),
                 remove_User  = async( std::launch::async , bind(&Listener::remove_Inactive_User   , this ) );

    if(DEBUG_LISTENER){
        cout<<"[Listener > run Listener] Threads Deployed\n";
    }
}

/***
    Listener::admin_Acceptor()
        Accepts Client Admin tcp connections and stores them.

***/
void Listener::admin_Acceptor(){
    string key;
    if(DEBUG_LISTENER){
        cout<<"[Listener > admin Acceptor] Admin Acceptor Running\n";
    }
    while(running){
        if(Admin.size()<MAX_ADMIN){

            Asockets.push_back(asio::ip::tcp::socket(service));
            AA.accept(Asockets.back());
            AR.lock();
                newA.push_back(next(Asockets.end(),-1));
            AR.unlock();
        }
    }
}

/***
    Listener::user_Acceptor()
        Accepts Client Users tcp connections and stores them.

***/

void Listener::user_Acceptor(){
    string key;
    if(DEBUG_LISTENER){
        cout<<"[Listener > user Acceptor] User Acceptor Running\n";
    }
    while(running){
        if(User.size()<MAX_USERS){
            Usockets.push_back(asio::ip::tcp::socket(service));
            UA.accept(Usockets.back());
            UR.lock();
                newU.push_back(next(Usockets.end(),-1));
            UR.unlock();
        }
    }
}

void Listener::admin_Handler(){
    if(DEBUG_LISTENER){
        cout<<"[Listener > admin Handler] Running\n";
    }
    while(running){
        if(!newA.empty()){

            AR.lock();
                auto temp=newA.front();
                newA.pop_front();
            AR.unlock();
            string key = temp->remote_endpoint().address().to_string();
            Con_Detail info;
            info.sock=temp;

            MA.lock();

                if(Admin.find(key)==Admin.end() && adminThreads.size()<MAX_ADMIN-1){
                    auto ptr=Admin.insert({ key , info }).first;
                    auto tptr= adminThreads.insert(adminThreads.end(),async(std::launch::async,bind(&Listener::admin_Thread,this,ptr)));
                    ptr->second.F= tptr;
                }
            MA.unlock();
        }
    }
}

void Listener::user_Handler(){
     if(DEBUG_LISTENER){
        cout<<"[Listener > user Handler] Running\n";
    }
     while(running){
      if(!newU.empty()){

            UR.lock();
                auto temp=newU.front();
                newU.pop_front();
            UR.unlock();
            string key = temp->remote_endpoint().address().to_string();
            Con_Detail info;
            info.sock=temp;

            MU.lock();
                if(User.find(key)==User.end() && User.size()<MAX_USERS-1){
                    auto ptr=User.insert({ key , info }).first;
                    auto tptr= userThreads.insert(adminThreads.end(),async(std::launch::async,bind(&Listener::admin_Thread,this,ptr)));
                    ptr->second.F= tptr;
                }
            MU.unlock();
        }
    }
}

void Listener::remove_Inactive_Admin(){
    if(DEBUG_LISTENER){
        cout<<"[Listener > remove Inactive Admin] Running\n";
    }
    while(running){
        if(!remAdmin.empty()){
            MA.lock();
                auto ptr=remAdmin.front();
                adminThreads.erase(ptr);
                remUser.pop_front();
            MA.unlock();
        }
    }
}

void Listener::remove_Inactive_User(){
    if(DEBUG_LISTENER){
        cout<<"[Listener > remove Inactive User] Running\n";
    }
    while(running){
        if(!remUser.empty()){
            TU.lock();
                auto ptr=remUser.front();
                userThreads.erase(ptr);
                remUser.pop_front();
            TU.unlock();
        }
    }
}

void Listener::user_Thread(unordered_map<string,Con_Detail>::iterator U){
    if(DEBUG_LISTENER){
        cout<<"[Listener > User Thread] Client IP "<<U->first<<endl;
    }
    char buffer[MAX_PAC_SIZE];
    auto sock=U->second.sock;
    sock->set_option(rcv_timeout_option{ MAX_IDEL_USER });
    try{
        while(true){
            sock->read_some(asio::buffer(buffer,MAX_PAC_SIZE));
            NU.lock();
                unsigned long long reqN=reqNumU;

                if(reqNumU==MAX_PENDING_REQUEST_USERS)
                    reqNumU=0;
                else
                    reqNumU++;

            NU.unlock();

            string head="<<!REQ:"+to_string(reqN)+"U,IP:"+U->first+"!>>";
            MapU[reqN]=sock;
            RI.send_AH(head,buffer);
        }
    }
    catch(...){
        TU.lock();
        UR.lock();
            remUser.push_back(U->second.F);
            Usockets.erase(U->second.sock);
            User.erase(U);
        UR.unlock();
        TU.unlock();
    }
}

void Listener::admin_Thread(unordered_map<string,Con_Detail>::iterator U){
    if(DEBUG_LISTENER){
        cout<<"[Listener > admin Thread] admin IP "<<U->first<<endl;
    }
    char buffer[MAX_PAC_SIZE];
    auto sock=U->second.sock;
    sock->set_option(rcv_timeout_option{ MAX_IDEL_ADMIN });
    try{
        while(true){
            sock->read_some(asio::buffer(buffer,MAX_PAC_SIZE));
             NA.lock();
                unsigned long long reqN=reqNumA;

                if(reqNumA==MAX_PENDING_REQUEST_ADMINS)
                    reqNumA=0;
                else
                    reqNumA++;

            NA.unlock();

            string head="<<!REQ:"+to_string(reqN)+"A,IP:"+U->first+"!>>";
            MapA[reqN]=sock;
            RI.send_CH(head,buffer);
        }
    }
    catch(...){
        TU.lock();
        AR.lock();
            remAdmin.push_back(U->second.F);
            Asockets.erase(U->second.sock);
            Admin.erase(U);
        AR.unlock();
        TU.unlock();
    }
}

void Listener::RE_Handler(){
    if(DEBUG_LISTENER){
        cout<<"[Listener > RE Handler] Running\n";
    }
    while(running){
        if(!mesRE.empty()){
            MRE.lock();
                auto temp= mesRE.front();
                mesRE.pop_front();
            MRE.unlock();
            auto mess=separate_header(temp);
            if(get<1>(mess.first)==false){
                auto sock=MapA[get<0>(mess.first)];
                sock->send(asio::buffer(mess.second.c_str(),MAX_PAC_SIZE));
            }
            else{
                auto sock=MapU[get<0>(mess.first)];
                sock->send(asio::buffer(mess.second.c_str(),MAX_PAC_SIZE));
            }
        }
    }
}

//
//void Listener::user_Async_Handler(boost::system::error_code e,size_t len,unordered_map<string,Con_Detail>::iterator &it){
//    if(e.value()!=0)
//        return;
//    string head="<<!REQ:"+to_string(reqNumU)+"U,IP:"+it->first+"!>>";
//    it->second.last = time(nullptr);
//    it->second.request.push_back(reqNumU);
//    reqNumU++;
//    if(reqNumU==ULLONG_MAX)
//        reqNumU=0;
//    RI.send_AH(head,it->second.buffer);
//}
//
//void Listener::admin_Async_Handler(boost::system::error_code e,size_t len,unordered_map<string,Con_Detail>::iterator &it){
//    if(e.value()!=0)
//        return;
//    string head="<<!REQ:"+to_string(reqNumA)+"A,IP:"+it->first+"!>>";
//    it->second.last = time(nullptr);
//    it->second.request.push_back(reqNumA);
//    reqNumA++;
//    if(reqNumA==ULLONG_MAX)
//        reqNumA=0;
//    RI.send_CH(head,it->second.buffer);
//}


/*
    <<! Front End Added Data !>><<? Original Request ?>>
*/
