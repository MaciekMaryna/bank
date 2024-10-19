cmake_minimum_required(VERSION 3.10)
project(BankServer)

set(HEADER_DIR "${CMAKE_SOURCE_DIR}/Inc")
set(SOURCE_DIR "${CMAKE_SOURCE_DIR}/Src")

set(SRC
    main.cpp
    ${SOURCE_DIR}/TestApp.cpp
    ${SOURCE_DIR}/Account.cpp
    ${SOURCE_DIR}/PersonalAccount.cpp
    ${SOURCE_DIR}/CheckingAccount.cpp
    ${SOURCE_DIR}/SavingsAccount.cpp
    ${SOURCE_DIR}/ForeginCurrencyAccount.cpp
)

message("${SRC}") # print to the console
add_executable(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PUBLIC ./Inc)
