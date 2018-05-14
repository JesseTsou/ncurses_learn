all:test
test:
	g++ -g win.cpp -o win -lncurses -lpanel
	g++ -g panel.cpp -o panel -lncurses -lpanel
	g++ -g menu.cpp -o menu -lncurses -lpanel
clean:
	rm -rf win
	rm -rf panel
	rm -rf menu
