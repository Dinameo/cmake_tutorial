cmake_minimum_required(VERSION 3.31)
project(Example_project)


add_library(Example)
target_sources(Example
    PRIVATE
        example.c
)

set_target_properties(Example
    PROPERTIES
        Key Value
)

get_target_property(KeyVar Example Key)

message("[Key] = ${KeyVar}")