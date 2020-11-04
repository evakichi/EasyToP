cmake_minimum_required(VERSION 3.10)

project(helloworld VERSION 0.5)
configure_file(../include/helloworld.h.in ./include/helloworld.h)
add_executable(helloworld ../sources/helloworld.c)
