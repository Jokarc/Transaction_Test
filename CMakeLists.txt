cmake_minimum_required(VERSION 3.19)
project(Transaction_Test)

set(CMAKE_CXX_STANDARD 14)
file(GLOB SOURCES
        *.h						//*号对应具体的文件名
        *.cpp
        )

add_executable(Transaction_Test main.cpp ${SOURCE_FILES} ${SOURCES} ShopCart.h)
