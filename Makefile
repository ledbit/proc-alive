

all: runner checker

mkbin:
	mkdir -p bin

checker: mkbin
	gcc -o bin/checker src/checker.cpp

runner: mkbin
	gcc -o bin/runner src/runner.cpp

clean: 
	rm bin/*
