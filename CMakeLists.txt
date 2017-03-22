cmake_minimum_required(VERSION 3.6)
project(LispInterpreter)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SExpression.cpp SExpression.h Token.cpp Token.h Parser.cpp Parser.h Lexer.cpp Lexer.h Evaluator.cpp Evaluator.h)
add_executable(LispInterpreter ${SOURCE_FILES})