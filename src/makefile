.SUFFIXES:
.PHONY: test

test: main_exe
	./$<

main_exe : main_test.cpp vec_mat.h makefile
	g++ -std=c++11 -Wfatal-errors -I. -o main_exe main_test.cpp

clean:
	rm *_exe
