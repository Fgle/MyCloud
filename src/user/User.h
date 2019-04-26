//
// Created by zerone on 19-4-26.
//

#ifndef MYCLOUD_USER_H
#define MYCLOUD_USER_H

#include <string>
#define _ADMINISTRATOR
#define _USER
#define _VIP_1
class User {
private:
    std::string _usermame;       //用户名
    std::string _password;       //用户密码
    std::string _permission;     //用户权限
    std::string _home;           //用户根目录
    std::string _size;           //用户磁盘大小
public:
    User() = default;
    ~User() = default;

    void SetUsername(const std::string &username);
    std::string GetUsername() const ;

    void SetPassword(const std::string &password);
    std::string GetPassword() const ;

    void SetPermission(const std::string &permission);
    std::string GetPermission() const ;

    void SetHome(const std::string home);
    std::string GetHome() const ;

    void SetSize(const std::string size);
    std::string GetSize() const;
};


#endif //MYCLOUD_USER_H
