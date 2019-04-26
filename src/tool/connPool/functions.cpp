//
// Created by zerone on 19-4-26.
//

#include <mysql++/mysql++.h>
#include <iostream>
#include <exception>
#include "functions.h"
//
//bool DestoryConnection::destory(mysqlpp::Connection *conn) {
//    if (conn == nullptr)
//        return true;
//    try {
//        conn->disconnect();
//    } catch (std::exception &e) {
//        std::cerr << "Error : " << e.what() << std::endl;
//        return false;
//    }
//    return true;
//}
//bool DestoryConnection::destory() {
//    return destory();
//}
//
//bool DestoryPool::destory(mysqlpp::Connection *) {
//    auto iter = conn_list.begin();
//
//    mx.lock();
//    while (iter != conn_list.end()) {
//        this->DestoryConnection(*iter);
//    }
//    cur_size = 0;
//    conn_list.clear();
//    mx.unlock();z
//}