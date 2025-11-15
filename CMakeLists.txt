cmake_minimum_required(VERSION 4.0)
project(Centralinaio C)

set(CMAKE_C_STANDARD 23)

add_executable(Centralinaio src/main.c
        includes/centraline.h
        includes/impostazioni.h
        includes/liste.h
        src/liste.c
        src/centraline.c)
