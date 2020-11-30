cmake_minimum_required(VERSION 3.16)
project(ClionProjects)

set(CMAKE_CXX_STANDARD 17)

add_executable(ClionProjects main.cpp Lexem/Lexem.cpp Lexem/Lexem.h FSM/FSM.cpp FSM/FSM.h Lexer/Lexer.cpp Lexer/Lexer.h)