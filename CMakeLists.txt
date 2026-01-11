cmake_minimum_required(VERSION 4.0)
project(chat_bot)

set(CMAKE_CXX_STANDARD 20)

add_executable(chat_bot main.cpp
        functions.cpp
        header.h)
