//
// Created by zerone on 19-4-25.
//

#ifndef MYCLOUD_CONNPOOL_H
#define MYCLOUD_CONNPOOL_H

#include <mysql++/mysql++.h>
#include <string>
#include <list>
#include <thread>
#include <mutex>

class ConnPool {
public:
    ~ConnPool();
    // 获取数据库连接
    mysqlpp::Connection* GetConnection();
    // 将数据库连接放回到连接池的容器中
    void ReleaseConnection(mysqlpp::Connection *conn);
    // 获取数据库连接池对象
    static ConnPool* GetInstance();

private:
    // 当前已建立的数据库连接数量
    int cur_size;
    // 连接池定义的最大数据库连接数
    int max_size;
    std::string username;
    std::string password;
    std::string url;
    std::string db_mane;
    int port;
    // 连接池容器
    std::list<mysqlpp::Connection*> conn_list;
    // 线程锁
    std::mutex mx;
    static ConnPool* connPool;
//    mysqlpp::Driver* driver;

    /*** 创建一个连接 ***/
    mysqlpp::Connection* CreateConnection();
    /*** 初始化数据库连接池 ***/
    void InitConnection(int);
    /*** 销毁数据库连接对象 ***/
    void DestoryConnection(mysqlpp::Connection *conn);
    /*** 销毁数据库连接池 ***/
    void DestoryConnPool();
    /*** 构造方法 ***/
    ConnPool();
    /***set() and get()函数***/
    void SetDBName(const std::string&);
    std::string GetDBName() const ;

    void SetUrl(const std::string&);
    std::string GetUrl() const;

    void SetUserName(const std::string&);
    std::string GetUserName() const;

    void SetPassword(const std::string&);
    std::string GetPassword() const;

    void SetMaxSize(int);
    int GetMaxSize() const;

    void SetPort(int);
    int GetPort() const;
};


#endif //MYCLOUD_CONNPOOL_H
