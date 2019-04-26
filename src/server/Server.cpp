//
// Created by zerone on 19-4-26.
//

#include <boost/bind.hpp>
#include "Server.h"
Server::Server(boost::asio::io_service &io_service, boost::asio::ip::tcp::endpoint &endpoint)
        : io_service(io_service), acceptor(io_service, endpoint) {
    start();
}

void Server::start() {
    session_ptr	new_chat_session(new Session(io_service));

    acceptor.async_accept(new_chat_session->socket(),
                           boost::bind(&Server::accept_handler, this, new_chat_session,
                                       boost::asio::placeholders::error));
}

void Server::run() {
    io_service.run();
}

void Server::callback_session(std::string /*_fromIp*/, std::string /*_info*/) {
    return;
}

void Server::accept_handler(session_ptr chat_session, const boost::system::error_code& error) {
    if (!error && chat_session) {
        try {
            chat_session->start();
            start();
        }
        catch (...) {
            return;
        }
    }
}