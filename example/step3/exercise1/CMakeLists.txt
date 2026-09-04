cmake_minimum_required(VERSION 3.31)
project(tutorial_project)


option(TUTORIAL_BUILD_UTILITIES "Lua chon build tutoral" ON)

add_library(MathFunctions)
target_sources(MathFunctions
    PRIVATE
        src/MathFunctions.c
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            inc
        FILES
            inc/MathFunctions.h
)

if(TUTORIAL_BUILD_UTILITIES )
    add_executable(Tutorial)
    target_sources(Tutorial
        PRIVATE
            src/Tutorial.c
    )
    target_link_libraries(
        Tutorial
        PRIVATE
            MathFunctions
    )
    message("Build tutorial")
else()
    message("Khong build tutorial")
endif()




