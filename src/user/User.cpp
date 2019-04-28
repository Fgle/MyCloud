//
// Created by zerone on 19-4-26.
//

#include "User.h"

User& User::operator=(User const &user) {
        this->_usermame = user._usermame;
        this->_password = user._password;
        this->_home = user._home;
        this->_permission = user._permission;
        this->_size = user._size;
}

void User::SetUsername(const std::string &username) {
    this->_usermame = username;
}
std::string User::GetUsername() const {
    return this->_usermame;
}

void User::SetPassword(const std::string &password) {
    this->_password = password;
}
std::string User::GetPassword() const {
    return this->_password;
}

void User::SetPermission(const std::string &permission) {
    this->_permission = permission;
}
std::string User::GetPermission() const {
    return this->_permission;
}

void User::SetHome(const std::string home) {
    this->_home = home;
}
std::string User::GetHome() const {
    return this->_home;
}

void User::SetSize(const std::string size) {
    this->_size = size;
}
std::string User::GetSize() const {
    return this->_size;
}