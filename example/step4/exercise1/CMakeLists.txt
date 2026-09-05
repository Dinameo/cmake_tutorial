cmake_minimum_required(VERSION 3.31)

project(MyProject)

add_executable(MyApp)
target_sources(MyApp
    PRIVATE
        src/main.cpp
)

target_include_directories(MyApp
    PRIVATE
        third_party/include
)
target_link_directories(MyApp
    PRIVATE
        third_party/lib
)
target_link_libraries(MyApp
    PRIVATE
        math
)
