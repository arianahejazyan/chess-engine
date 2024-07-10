cmake_minimum_required(VERSION 3.29.0)

project(TALIA)

#add_subdirectory(interface)
#add_subdirectory(setting)

add_executable(talia talia.cc ./interpreter/cli.cpp ./setting/config.cpp)

#target_link_libraries(talia PRIVATE cli)

target_include_directories(talia PRIVATE ${CMAKE_SOURCE_DIR}/interface ${CMAKE_SOURCE_DIR}/setting)