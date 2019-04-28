//
// Created by zerone on 19-4-26.
//
#include "DBInfo.h"
/***
 *
 * get() and set() of db_name
 *
 ***/
void DBInfo::SetDBName(const std::string &dbname) {
    this->f_dbname = dbname;
}
const std::string& DBInfo::GetDBName() const {
    return this->f_dbname;
}

/***
 *
 * get() and set() of url
 *
 ***/
void DBInfo::SetServerIp(const std::string &server_ip) {
    this->f_server_ip = server_ip;
}
const std::string& DBInfo::GetServerIP() const {
    return this->f_server_ip;
}

/***
 *
 * get() and set() of username
 *
 ***/
void DBInfo::SetUsername(const std::string &user) {
    this->f_user = user;
}
const std::string& DBInfo::GetUsername() const {
    return this->f_user;
}

/***
 *
 * get() and set() of password
 *
 ***/
void DBInfo::SetPassword(const std::string &password) {
    this->f_password = password;
}
const std::string& DBInfo::GetPassword() const {
    return this->f_password;
}


/***
 *
 * get() and set() of port
 *
 ***/
void DBInfo::SetPort(const int port) {
    this->f_port = port;
}
const int DBInfo::GetPort() const {
    return this->f_port;
}
/***
 *
 *get() and set() of charset
 *
 ***/
void DBInfo::SetCharset(const std::string &charset) {
    this->f_charset = charset;
}
const std::string& DBInfo::GetCharset() const {
    return this->f_charset;
}
