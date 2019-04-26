//
// Created by zerone on 19-4-25.
//
#include <exception>
#include <iostream>

#include "ConnPool.h"

ConnPool *ConnPool::connPool = nullptr;

ConnPool::ConnPool() {
    this->db_mane = "mysql";
    this->url = "127.0.0.1";
    this->username = "root";
    this->password = "password";
    this->cur_size = 0;
    this->max_size = 32;
    this->port = 3306;
}

ConnPool *ConnPool::GetInstance() {
    std::mutex mx;
    if(connPool == nullptr) {
        mx.lock();
        if(connPool == nullptr) {
            connPool = new ConnPool();
        }
        mx.unlock();
    }
    return connPool;
}

void ConnPool::InitConnection(int size) {
    try {
        mysqlpp::Connection *conn;
        mx.lock();
        for (int i = 0; i < size; ++i) {
            conn = this->CreateConnection();
            if (conn) {
                this->conn_list.emplace_back(conn);
                ++(this->cur_size);
            }
            else {
                std::cerr << "Init connection error." << std::endl;
            }
        }
        mx.unlock();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

mysqlpp::Connection *ConnPool::CreateConnection() {
    auto conn = new mysqlpp::Connection(false);
    try
    {
        // 建立连接
        conn->connect(this->db_mane.data(), this->url.data(), this->username.data(), this->password.data(), this->port);
        return conn;
    }
    catch (std::exception &e)
    {
        std::cerr << "error: " << e.what() << std::endl;
        return nullptr;
    }
}

mysqlpp::Connection *ConnPool::GetConnection() {
    mysqlpp::Connection* conn;
    mx.lock();

    // 连接池容器中还有连接
    if (!conn_list.empty()) {
        // 获取第一个连接
        conn = conn_list.front();
        // 移除第一个连接
        conn_list.pop_front();
        // 判断获取到的连接的可用性
        // 如果连接已经被关闭，删除后重新建立一个
        if (conn == nullptr) {
            delete conn;
            conn = this->CreateConnection();
            // 如果连接为空，说明创建连接出错
            if (conn == nullptr) {
                // 从容器中去掉这个空连接
                --cur_size;
            }
        }

        mx.unlock();
        return conn;
    }
        // 连接池容器中没有连接
    else {
        // 当前已创建的连接数小于最大连接数，则创建新的连接
        if (cur_size < max_size)
        {
            conn = this->CreateConnection();
            if (conn != nullptr) {
                ++cur_size;
                mx.unlock();
                return conn;
            } else {
                mx.unlock();
                return nullptr;
            }
        }
            // 当前建立的连接数已经达到最大连接数
        else {
            std::cerr << "[GetConnection] connections reach the max number." << std::endl;
            mx.unlock();
            return nullptr;
        }
    }
}

void ConnPool::ReleaseConnection(mysqlpp::Connection *conn) {
    if (conn != nullptr) {
        mx.lock();
        conn_list.emplace_back(conn);
        mx.unlock();
    }
}
/***
 *
 * Drop the connection to the database server
 *
 * ***/
void ConnPool::DestoryConnection(mysqlpp::Connection *conn) {
    if (conn != nullptr) {
        try {

            conn->disconnect();
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        delete conn;
    }
}
/***
 * destory connection pool
 * delete all connection of pool
 *
 ***/
void ConnPool::DestoryConnPool() {
    auto iter = conn_list.begin();

    mx.lock();
    while (iter != conn_list.end()) {
        this->DestoryConnection(*iter);
    }
    cur_size = 0;
    conn_list.clear();
    mx.unlock();
}

ConnPool::~ConnPool() {
    this->DestoryConnPool();
}

/***
 *
 * get() and set() of db_name
 *
 ***/
void ConnPool::SetDBName(const std::string &name) {
    this->db_mane = name;
}
std::string ConnPool::GetDBName() const {}

/***
 *
 * get() and set() of url
 *
 ***/
void ConnPool::SetUrl(const std::string &u) {
    this->url = u;
}
std::string ConnPool::GetUrl() const {}

/***
 *
 * get() and set() of username
 *
 ***/
 void ConnPool::SetUserName(const std::string &user) {
     this->username = user;
 }
 std::string ConnPool::GetUserName() const {}

 /***
  *
  * get() and set() of password
  *
  ***/
  void ConnPool::SetPassword(const std::string &pwd) {
      this->password = pwd;
  }
  std::string ConnPool::GetPassword() const {}

  /***
   *
   * get() and set() of max_size
   *
   ***/
   void ConnPool::SetMaxSize(const int size) {
       this->max_size = size;
   }
   int ConnPool::GetMaxSize() const {}

   /***
    *
    * get() and set() of port
    *
    ***/
    void ConnPool::SetPort(const int p) {
        this->port = p;
    }
    int ConnPool::GetPort() const {}