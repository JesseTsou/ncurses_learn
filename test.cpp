#include <stdio.h>
#include <ncurses.h>

int hello()
{
	initscr();
	printw("Hello world");
	refresh();
	getchar();
	endwin();

	return 0;
}

int main()
{
	hello();

	return 0;
}
