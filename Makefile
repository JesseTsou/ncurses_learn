all:test
test:
	g++ test.cpp -o test -lncurses
clean:
	rm -rf test
