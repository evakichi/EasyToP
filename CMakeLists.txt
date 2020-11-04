cmake_minimum_required(VERSION 3.10)

project(helloworld VERSION 0.5)
add_subdirectory(sources)
add_subdirectory(tests)

configure_file(include/helloworld.h.in include/helloworld.h)
enable_testing()
add_test(NAME Runs COMMAND helloworld WORKING_DIRECTORY sources)
