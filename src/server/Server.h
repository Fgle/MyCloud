//
// Created by zerone on 19-4-26.
//

#ifndef MYCLOUD_SERVER_H
#define MYCLOUD_SERVER_H
#include <string>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

#include "Session.h"

class Server {
private:
    /***会话***/
    typedef boost::shared_ptr<Session> session_ptr;
public:
    explicit Server(boost::asio::io_service &, boost::asio::ip::tcp::endpoint &);
    virtual ~Server() = default;
    // 监听
    void start();
    // 异步
    void run();
private:
    // 数据导出接口
    void callback_session(std::string, std::string);
    // 会话启动
    void accept_handler(session_ptr , const boost::system::error_code& );
private:
    boost::asio::io_service &io_service;
    boost::asio::ip::tcp::acceptor acceptor;
};


#endif //MYCLOUD_SERVER_H
