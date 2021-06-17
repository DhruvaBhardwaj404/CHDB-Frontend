#ifndef FUNCTIONS_SERVER_H
#define FUNCTIONS_SERVER_H

#include<vector>
#include<algorithm>
#include<iostream>
#include<asio.hpp>

using namespace std;

namespace functions_Server
{
    bool read_Completion(asio::error_code err, string buffer,unsigned size);
    vector<pair<string,string> > parse_Request(const string& query);
}

#endif // FUNCTIONS_SERVER_H
