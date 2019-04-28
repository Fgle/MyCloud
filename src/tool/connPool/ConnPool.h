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

#include "../database/DBInfo.h"

class ConnPool : public mysqlpp::ConnectionPool{
public:
    // 获取数据库连接
    mysqlpp::Connection* grab() override ;
    // 将数据库连接放回到连接池的容器中
    void release(const mysqlpp::Connection* coon) override ;
    //void remove(const mysqlpp::Connection* conn);
    // 获取数据库连接池对象
    static ConnPool* GetInstance();
    ~ConnPool() override {
        clear();
    }
    inline int getSize() {
        return mysqlpp::ConnectionPool::size();
    }

protected:
    /*** 创建一个连接 ***/
    mysqlpp::Connection* create() override ;
    /*** 销毁数据库连接对象 ***/
    void destroy(mysqlpp::Connection* cp) override ;
    unsigned int max_idle_time() override ;
    /*** 构造方法 ***/
    ConnPool() = default;
    /***set() and get()函数***/
    void SetMaxIdleTime(int);
    const int GetMaxIdleTime() const;


    void SetMaxSize(int);
    const int GetMaxSize() const;

    const int GetConnUse() const;

    void SetDBInfo(const DBInfo &info_);
private:
    DBInfo info;
    int         f_max_idle_time;    //
    unsigned int f_conns_in_use_;   //正在使用的链接
    int f_max_size;                 //最大连接数
    std::mutex mx;                  //线程
    static ConnPool *conn_pool;

};


#endif //MYCLOUD_CONNPOOL_H
