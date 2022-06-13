#ifndef PARAMDEFINITIONS_H
#define PARAMDEFINITIONS_H

//STL
#include<mutex>
#include<atomic>
#include<iostream>
#include<future>
#include<unordered_map>
#include<list>
#include<string>
#include<time.h>


//Boost libary
#include<asio.hpp>
#include<boost/system/error_code.hpp>

//Listener
#define MAX_ADMIN 5
#define MAX_USERS 100
#define ADMIN_ACC_IP "127.0.0.1"
#define ADMIN_ACC_PORT 10000
#define CLIENT_ACC_IP "127.0.0.1"
#define CLIENT_ACC_PORT 10001
#define MAX_IDEL_ADMIN 100000
#define MAX_IDEL_USER 10000
#define MAX_PENDING_REQUEST_USERS 100
#define MAX_PENDING_REQUEST_ADMINS 10
#define DEBUG_LISTENER true

//RE
#define DEBUG_RE true

//RI


//Backend socket addresses and ports
#define SOCKET_ALIVE_IP "127.0.0.1"
#define SOCKET_ALIVE_PORT 5010
#define SOCKET_CONHAN_IP "127.0.0.1"
#define SOCKET_CONHAN_PORT  5009
#define SOCKET_QPAR_IP "127.0.0.1"
#define SOCKET_QPAR_PORT 5008

//Parameters
#define MAX_PAC_SIZE 1024

#endif // PARAMDEFINITIONS_H
