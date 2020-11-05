link_directories(/usr/local/lib /usr/local/lib64)
add_executable(analyzertest analyzertest.cpp)
target_include_directories(analyzer INTERFACE /usr/local/include/ /usr/include/)
target_link_libraries(analyzertest clang)
