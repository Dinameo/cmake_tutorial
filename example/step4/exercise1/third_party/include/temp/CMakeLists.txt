cmake_minimum_required(VERSION 3.31)

project(MyLibProject)


add_library(math)
target_sources(math
    PRIVATE
        math.cpp

    PUBLIC
        FILE_SET HEADERS
        FILES
            math.h
)

