//#include<gtest/gtest.h>
//#include"paramDefinitions.h"
//#include"Listener.h"
//
//using namespace std;
//
//class ListenerTEST : public ::testing::Test{
//protected:
//    ListenerTEST():Admin(asio::ip::address::from_string(ADMIN_ACC_IP),ADMIN_ACC_PORT),
//                   User(asio::ip::address::from_string(CLIENT_ACC_IP),CLIENT_ACC_PORT)
//    {}
//
//    void SetUp() override {
//
//    }
//
//    void TearDown() override{
//        con.clear();
//    }
//
//    asio::io_context service;
//    vector<asio::ip::tcp::socket> con;
//    asio::ip::tcp::endpoint Admin,User;
//};
//
//TEST_F(ListenerTEST,ADMIN_TEST){
//    asio::error_code e;
//    char buff[MAX_PAC_SIZE]="<<?[(1,2)][(3,4)]?>>";
//    for(int i=0;i<6;i++){
//
//        con.push_back(asio::ip::tcp::socket(service));
//
//        con[i].connect(Admin,e);
//        int val=e.value();
//        EXPECT_EQ(val,0);
//        EXPECT_NO_FATAL_FAILURE(con[i].send(asio::buffer(buff,MAX_PAC_SIZE)));
//    }
//    con.push_back(asio::ip::tcp::socket(service));
//    EXPECT_NO_FATAL_FAILURE(con[6].connect(Admin));
//
//}
//
//TEST_F(ListenerTEST,USER_TEST){
//    con.push_back(asio::ip::tcp::socket(service));
//    EXPECT_NO_FATAL_FAILURE(con[0].connect(User));
//}

//TEST_F(Listener)
