# This is a very simple makefile for building the Lisp interpreter
# project when using C++ on stdlinux. Feel free to add any improvements:
# e.g. pattern rules, automatic tracking of dependencies, etc. There
# is a lot of info about "make" on the web.

# C++ compiler
CXX = g++

# C++ compiler flags
CXXFLAGS = -g -Wall -std=c++0x

# Creating a .o file
COMPILE = $(CXX) $(CXXFLAGS) -c

# Name of the executable; should match the contents of Runfile
EXE = part1

# All object files
OBJS = main.o Lexer.o Parser.o Token.o SExpression.o

# The first target is the one that is executed when you invoke
# "make". The line describing the action starts with <TAB>. Variable
# "$@" stands for the current target. 

$(EXE) : $(OBJS) # depends on all object files
	$(CXX) $^ -o $@
clean : 
	rm *.o part1

# An object file is dependent on the corresponding source file

%.o : %.cc
	$(COMPILE) -o $@ $<

main.o : Parser.h

Lexer.o : Lexer.h Token.h

Parser.o : Lexer.h Token.h

Token.o : Token.h

SExpression.o : SExpression.h
