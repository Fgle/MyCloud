//
// Created by zerone on 19-4-26.
//
#include <boost/bind.hpp>

#include "Session.h"


Session::Session(boost::asio::io_service& io_service)
        :socket_(io_service) {
    memset(msg, 0, sizeof(msg));
}

void Session::start() {
    // 告诉链接成功的客户端，你想要的信息。
    char msg[256] = "001:Connect Succeed! Please tell me with 10 bytes, the total data and the size of each package, example:128 1024";
    boost::asio::async_write(socket_, boost::asio::buffer(msg, strlen(msg)),
                             boost::bind(&Session::init_handler, shared_from_this(),
                                         boost::asio::placeholders::error));
}

boost::asio::ip::tcp::socket& Session::socket(void) {
    return socket_;
}


// 第一个协议包
void Session::init_handler(const boost::system::error_code& error) {
    if (error) {
        return;
    }
    // 读取客户端发来的 10 bytes，确定单个包的大小以及数据总大小
    boost::asio::async_read(socket_, boost::asio::buffer(msg, 10),
                            boost::bind(&Session::analyse_handler, shared_from_this(),
                                        boost::asio::placeholders::error));

}

void Session::analyse_handler(const boost::system::error_code& error) {
    if (error) {
        return;
    }
    // 分析协议包格式
    bool bflag = true;
    // 正则分析格式

    // do something.
    if (!bflag) {
        start();
        return;
    }

    // 格式化保存协议包数据
    std::stringstream io(msg);
    io >> max_size;
    io >> sumSize_;

    // 发送接收请求信息
    char msg[REPLY_SIZE];
    sprintf(msg, "001:is ok, data remaining %d.", sumSize_);
    boost::asio::async_write(socket_, boost::asio::buffer(msg, REPLY_SIZE),
                             boost::bind(&Session::write_handler, shared_from_this(),
                                         boost::asio::placeholders::error));
}


// 完成数据传输
void Session::done_handler(const boost::system::error_code& error) {
    if (error) {
        return;
    }
    current_msg += msg;
    // 发送信息到回调
    if (!current_msg.empty() && callback != nullptr) {
        callback(socket_.remote_endpoint().address().to_string(), current_msg);
        current_msg.clear();
    }
    memset(msg, 0, sizeof(msg));

    char msg[32] = "001:will done.";
    boost::asio::async_write(socket_, boost::asio::buffer(msg, REPLY_SIZE),
                             boost::bind(&Session::init_handler, shared_from_this(),
                                         boost::asio::placeholders::error));
}

void Session::read_handler(const boost::system::error_code& error, size_t read_size) {
    if (error) {
        return;
    }
    // 数据处理
    current_msg += msg;
    if (current_msg.size() > 1024 * 512) {
        // 发送信息到回调
        if (callback != nullptr) {
            callback(socket_.remote_endpoint().address().to_string(), current_msg);
            current_msg.clear();
        }
    }
    memset(msg, 0, sizeof(msg));

    // 计算当前剩余数据数量
    sumSize_ -= read_size;

    // 接收完成
    if (0 > sumSize_) {
        done_handler(error);
    }
        // 继续接收
    else {
        char msg[REPLY_SIZE];
        sprintf(msg, "001:%d.", sumSize_);
        boost::asio::async_write(socket_, boost::asio::buffer(msg, REPLY_SIZE),
                                 boost::bind(&Session::write_handler, shared_from_this(),
                                             boost::asio::placeholders::error));

        std::cout << "send client recv succeed: " << msg << std::endl;
    }



}
void Session::write_handler(const boost::system::error_code& error) {
    if (error) {
        return;
    }

    boost::asio::async_read(socket_, boost::asio::buffer(msg, max_size),
                            boost::bind(&Session::read_handler, shared_from_this(),
                                        boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}