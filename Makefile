all:test
test:
	g++ -g test.cpp -o test -lncurses
clean:
	rm -rf test
