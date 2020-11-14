link_directories(/usr/local/lib /usr/local/lib64)

add_executable(helloworld helloworld.c)
add_executable(analyzer analyzer.cpp)
target_include_directories(analyzer INTERFACE /usr/local/include/ /usr/include/)
target_link_libraries(analyzer clang)

add_definitions(-D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -fno-exceptions -fno-rtti -D_GNU_SOURCE -D_DEBUG -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)
add_executable(parser parser.cpp)
target_include_directories(parser INTERFACE /usr/local/include/ /usr/include/)
target_link_libraries(parser clang)
target_link_libraries(parser clang-cpp)
target_link_libraries(parser ${STATIC_LLVM_LIBRARIES})
target_link_libraries(parser ${STATIC_SYSTEM_LIBRARIES})
target_link_libraries(parser ${SHARED_SYSTEM_LIBRARIES})

add_executable(creater creater.cpp)
add_executable(optimizer optimizer.cpp)
add_executable(measure measure.cpp)
