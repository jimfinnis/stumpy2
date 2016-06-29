cmake_minimum_required(VERSION 2.6)
project(SERVERBASE)

set(SOURCES controller.cpp errors.cpp model.cpp server.cpp timer.cpp
    stdConns.cpp)

add_executable(test test.cpp ${SOURCES})


