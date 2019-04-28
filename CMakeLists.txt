cmake_minimum_required(VERSION 3.13)
project(MyCloud)

set(CMAKE_CXX_STANDARD 17)

add_executable(LinuxSystemLearn main.cpp src/tool/connPool/ConnPool.cpp src/tool/connPool/ConnPool.h src/server/Server.cpp src/server/Server.h src/server/Session.cpp src/server/Session.h src/user/User.cpp src/user/User.h src/user/UserFun.cpp src/user/UserFun.h src/tool/database/DBInfo.h src/tool/database/DBInfo.cpp)
#target_link_libraries(MyCloud)