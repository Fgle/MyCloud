//
// Created by zerone on 19-4-26.
//
#include <string>

#include "UserFun.h"

UserFun::UserFun(mysqlpp::Connection *conn, const User &user) {
    this->_conn = conn;
    this->_user = user;
}

int UserFun::login() {

    std::string sql = "select password from user where username = ";
    sql.append(this->_user.GetUsername());

    mysqlpp::Query query = this->_conn->query(sql);
    if (query.store().empty())
        return _password_error;
    else if (query.store().front().front() == this->_user.GetPassword())
        return _success;
}

int UserFun::regist() {
    std::string sql = "insert into user table(name,password,permission,home,size) values(";
    sql +=  this->_user.GetUsername() + ',' +
            this->_user.GetPassword() + ',' +
            this->_user.GetPermission() +',' +
            this->_user.GetHome() + ',' +
            this->_user.GetSize();

    mysqlpp::Query query = this->_conn->query();
    if(query.exec(sql))
        return _success;
    else
        return _db_error;
}