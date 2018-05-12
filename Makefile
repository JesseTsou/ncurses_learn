all:test
test:
	g++ -g test.cpp -o test -lncurses -lpanel
clean:
	rm -rf test
