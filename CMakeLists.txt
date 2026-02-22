cmake_minimum_required(VERSION 3.15)
project(Image_To_ASCII)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(Image_To_ASCII
    src/main.c
)

target_link_libraries(Image_To_ASCII m)