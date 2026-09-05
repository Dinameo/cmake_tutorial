cmake_minimum_required(VERSION 3.31)
project(Example4)

add_executable(MyApp)
target_sources(MyApp
    PRIVATE
        main.cpp
)
message("${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")
set(WARNING "ON")
if(WARNING STREQUAL "ON")
target_compile_options(MyApp
    PRIVATE
        -Wall
)
endif()
