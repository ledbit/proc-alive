

all: runner checker

checker:
	gcc -o checker src/checker.cpp

runner: 
	gcc -o runner src/runner.cpp

clean: 
	rm runner checker
