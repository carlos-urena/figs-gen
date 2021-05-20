.SUFFIXES:
.PHONY: test 

test: main_exe
	./$<

main_exe : main.cpp $(wildcard *.h) makefile 
	g++ -o main_exe main.cpp