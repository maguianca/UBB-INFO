cmake_minimum_required(VERSION 3.22)
project(oop_lab2_4_inchirieremasini C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_executable(oop_lab2_4_inchirieremasini UI.c
        service.c
        repo.c
        domain.c
        teste.h
        teste.c
        validator.h
        validator.c
)
