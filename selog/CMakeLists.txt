cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr)

project(selog)

target_sources(
    app 
    PRIVATE
    src/main.c
    src/read_thread.c
    src/shell.c
    src/net_thread.c
)
