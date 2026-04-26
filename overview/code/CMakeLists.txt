# Yêu cầu phiên bản tối thiểu Cmake
cmake_minimum_required(VERSION 3.10)
# Tên project, ngôn ngữ
project(hello_cmake C)
# Tạo executable bới tên là hello_cmake từ file main.c
add_executable(hello_cmake main.c)