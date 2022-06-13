#ifndef FUNCTIONS_SERVER_H
#define FUNCTIONS_SERVER_H

#include<vector>
#include<algorithm>
#include<iostream>
#include<asio.hpp>
#include<list>
#include"paramDefinitions.h"

using namespace std;

namespace functions_Server
{
    struct Con_Detail{
        list<asio::ip::tcp::socket>::iterator sock;
        list<future<void> >::iterator F;
    };

    pair<tuple<unsigned long long,bool,string>,string> separate_header(string);
}
//    string vvss_to_string( vector<vector<pair<string,string > > > data);
//    vector<vector<pair<string,string > > > string_to_vvss(string data);

//    bool read_Completion(asio::error_code err, string buffer,unsigned size);
//    vector<pair<string,string> > parse_Request(const string& query);
#endif // FUNCTIONS_SERVER_H
