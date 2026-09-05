cmake_minimum_required(VERSION 3.31)
project(MyProject)

add_executable(MyApp)
target_sources(MyApp
    PRIVATE
    main.cpp
)
target_compile_features(MyApp
    PRIVATE
        cxx_std_20
)
