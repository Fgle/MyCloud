//
// Created by zerone on 19-4-26.
//

#ifndef MYCLOUD_SESSION_H
#define MYCLOUD_SESSION_H

#include <iostream>
#include <string>

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

#define REPLY_SIZE (32)

// 会话类
class Session : public boost::enable_shared_from_this<Session>
{

public:

    typedef void pSessionCallback(std::string, std::string);

public:

    Session(boost::asio::io_service& io_ervice);
    virtual ~Session() = default;

    void start();

    void setCallback(pSessionCallback* _callback) { callback = _callback; }

    // socket 实例
    boost::asio::ip::tcp::socket& socket(void);

private:

    // 第一个协议包
    void init_handler(const boost::system::error_code&);

    // 解析协议包
    void analyse_handler(const boost::system::error_code&);

    // 完成数据传输后触发的收尾工作
    void done_handler(const boost::system::error_code&);

    // 读取成功后触发的函数
    void read_handler(const boost::system::error_code&, size_t);

    // 写入完成后触发的函数
    void write_handler(const boost::system::error_code&);

private:
    // 临时信息缓冲区
    char msg[1024];
    std::string current_msg;
    // 数据总数量
    int sumSize_;
    // 单个数据包大小
    unsigned int max_size;
    // socket句柄
    boost::asio::ip::tcp::socket socket_;
    // 回调
    pSessionCallback* callback;

};

#endif //MYCLOUD_SESSION_H
