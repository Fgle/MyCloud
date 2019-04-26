//
// Created by zerone on 19-4-26.
//

#ifndef MYCLOUD_FUNCTIONS_H
#define MYCLOUD_FUNCTIONS_H

#include <mysql++/mysql++.h>

class Destory {
    virtual bool destory() = 0;
};

class DestoryConnection : public Destory {
    bool destory(mysqlpp::Connection *);
    bool destory() override ;
};

class DestoryPool : public Destory {
    bool destory(mysqlpp::Connection *);
    bool destory() override ;
};

#endif //MYCLOUD_FUNCTIONS_H
