link_directories(/usr/local/lib /usr/local/lib64)
add_executable(helloworld helloworld.c)
add_executable(analyzer analyzer.cpp)
target_include_directories(analyzer INTERFACE /usr/local/include/ /usr/include/)
target_link_libraries(analyzer clang)

add_clang_executable(parser parser.cpp)
#add_executable(parser parser.cpp)
target_include_directories(parser INTERFACE /usr/local/include/ /usr/include/)
target_link_libraries(parser clang)

add_executable(creater creater.cpp)
add_executable(optimizer optimizer.cpp)
add_executable(measure measure.cpp)
