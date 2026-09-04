set(VERSION "3.31" CACHE STRING "A cache variable")
set(VERSION "3.32")

message(${VERSION})
unset(VERSION)
message(${VERSION})