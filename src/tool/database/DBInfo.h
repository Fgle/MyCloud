//
// Created by zerone on 19-4-26.
//

#ifndef MYCLOUD_DBINFO_H
#define MYCLOUD_DBINFO_H

#include <string>

class DBInfo {

public:
    void SetDBName(const std::string&);
    const std::string& GetDBName() const ;

    void SetServerIp(const std::string&);
    const std::string& GetServerIP() const;

    void SetUsername(const std::string&);
    const std::string& GetUsername() const;

    void SetPassword(const std::string&);
    const std::string& GetPassword() const;

    void SetPort(int);
    const int GetPort() const;

    void SetCharset(const std::string&);
    const std::string& GetCharset() const ;



private:
    std::string f_dbname;           //数据库名
    std::string f_server_ip;        //数据库链接地址
    std::string f_user;             //用户名
    std::string f_password;         //密码
    std::string f_charset;          //字符集
    int         f_port;             //端口号
};


#endif //MYCLOUD_DBINFO_H
