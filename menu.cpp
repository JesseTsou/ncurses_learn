#include <stdio.h>
#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*初始化*/
int init()
{
	initscr(); 
	raw();
	keypad(stdscr,TRUE);
	noecho();
	cbreak();
	
	return 0;
}

/*结束*/
int end()
{
	refresh();
	getch();
	endwin();

	return 0;
}

/*我是分隔线*/
int main()
{
	init();
	end();
	return 0;
}
