cmake_minimum_required(VERSION 3.31)
project(Example3)



add_executable(MyApp)
target_sources(MyApp
    PRIVATE
        main.cpp
)

target_compile_definitions(MyApp
    PRIVATE
        DEBUG
        VER="1.0"
)
