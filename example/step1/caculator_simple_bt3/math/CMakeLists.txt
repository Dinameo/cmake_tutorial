add_library(math)
target_sources(math
    PRIVATE
        math.c
    PUBLIC
        FILE_SET HEADERS
        FILES
            math.h
)

