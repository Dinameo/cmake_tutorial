cmake_minimum_required(VERSION 3.31)
project(calculator_app)

add_library(math)
target_sources(math
    PRIVATE
        src/math.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/math.h
)

add_executable(calculator)
target_sources(calculator
    PRIVATE
        src/main.c
)
target_link_libraries(calculator
    PRIVATE
        math
)
