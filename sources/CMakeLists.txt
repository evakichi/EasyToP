link_directories(/usr/local/lib /usr/local/lib64)

add_executable(creater creater.cpp)
add_executable(optimizer optimizer.cpp)
add_executable(measure measure.cpp)

add_executable(analyzer analyzer.cpp)
target_include_directories(analyzer INTERFACE /usr/local/include/ /usr/include/)
target_link_libraries(analyzer clang)

add_compile_definitions(
    GNU_SOURCE 
    DEBUG 
    __STDC_CONSTANT_MACROS 
    __STDC_FORMAT_MACROS 
    __STDC_LIMIT_MACROS 
    _GNU_SOURCE 
    _DEBUG 
    __STDC_CONSTANT_MACROS 
    __STDC_FORMAT_MACROS 
    __STDC_LIMIT_MACROS
    )
add_compile_options(
    -fno-exceptions 
    -fno-rtti 
)
add_executable(parser parser.cpp)
target_include_directories(parser INTERFACE /usr/local/include/ /usr/include/)
target_link_libraries(parser clang)
target_link_libraries(parser clang-cpp)
target_link_libraries(parser ${STATIC_LLVM_LIBRARIES})
target_link_libraries(parser ${STATIC_SYSTEM_LIBRARIES})
target_link_libraries(parser ${SHARED_SYSTEM_LIBRARIES})
