//
// Created by zerone on 19-4-26.
//

#ifndef MYCLOUD_USERFUN_H
#define MYCLOUD_USERFUN_H

#include <mysql++/mysql++.h>

#include "User.h"
/***登录信息***/
static const int _success = 0;
static const int _no_user = 1;
static const int _password_error = 2;
static const int _db_error = 3;

class UserFun {
private:
    mysqlpp::Connection *_conn;
    User _user;
public:
    /***构造函数***/
    explicit UserFun(mysqlpp::Connection *conn, const User &user);
    UserFun() = default;
    /***析构函数***/
    ~UserFun() = default;
    /***登录***/
    int login();
    /***注册***/
    int regist();
    /***注销***/
    int logout() {}
};


#endif //MYCLOUD_USERFUN_H
