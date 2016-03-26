cmake_minimum_required (VERSION 2.8)
project (encryptor)

add_subdirectory(cryptopp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cryptopp)
set(CMAKE_CXX_FLAGS "-std=c++0x")

set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/crypto.cpp
)

add_executable(encryptor ${SOURCE})
target_link_libraries(encryptor cryptopp-static)