//
// Created by zerone on 19-4-25.
//
#include <exception>
#include <iostream>
#include <unistd.h>

#include "ConnPool.h"

ConnPool *ConnPool::conn_pool = nullptr;


mysqlpp::Connection* ConnPool::grab(){
    while(f_conns_in_use_ > f_max_size) {
        std::cout << "wait conn release" << std::endl;
        sleep(1);
    }
    ++f_conns_in_use_;
    return mysqlpp::ConnectionPool::grab();
}

void ConnPool::release(const mysqlpp::Connection* conn)
{
    --f_conns_in_use_;
    mysqlpp::ConnectionPool::release(conn);
}

mysqlpp::Connection* ConnPool::create(){
    auto conn = new mysqlpp::Connection(true);
    auto pOpt = new  mysqlpp::SetCharsetNameOption(info.GetCharset());
    conn->set_option(pOpt);
    mx.lock();
    conn->connect(info.GetDBName().empty() ? nullptr : info.GetDBName().data(),
                  info.GetServerIP().empty() ? nullptr : info.GetServerIP().data(),
                  info.GetUsername().empty() ? nullptr : info.GetUsername().data(),
                  info.GetPassword().empty() ? "" : info.GetPassword().data(),
                  info.GetPort());
    mx.unlock();
    return conn;
}

void ConnPool::destroy(mysqlpp::Connection* conn){
    mx.lock();
    delete conn;
    mx.unlock();
}

unsigned int ConnPool::max_idle_time()
{
    return this->f_max_idle_time;
}

ConnPool *ConnPool::GetInstance() {
    std::mutex mx;
    if(conn_pool == nullptr) {
        mx.lock();
        if(conn_pool == nullptr) {
            conn_pool = new ConnPool();
        }
        mx.unlock();
    }
    return conn_pool;
}


     /***
      *
      * get() of conns_in_use
      *
      ***/
      const int ConnPool::GetConnUse() const {
          return this->f_conns_in_use_;
      }
/***
*
* get() and set() of max_size
*
***/
void ConnPool::SetMaxSize(const int size) {
    this->f_max_size = size;
}
const int ConnPool::GetMaxSize() const {
    return this->f_max_size;
}
/***
 *
 * get() and set() of max_idle_time
 *
 ***/
void ConnPool::SetMaxIdleTime(int max_idle)
{
    this->f_max_idle_time = max_idle;
}
const int ConnPool::GetMaxIdleTime() const {
    return this->f_max_idle_time;
}

void ConnPool::SetDBInfo(const DBInfo &info_) {
    this->info = info_;
}