cmake_minimum_required(VERSION 3.10)
project(BankServer)

set(HEADER_DIR "${CMAKE_SOURCE_DIR}/Inc")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Src")

set(SRC
    main.cpp
    ${HEADER_DIR}/TestApp.hpp
    ${SOURCE_DIR}/TestApp.cpp
)

add_executable(${PROJECT_NAME} ${SRC})

