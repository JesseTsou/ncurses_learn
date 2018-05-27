#include <stdio.h>
#include <ncurses.h>
#include <menu.h>
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

int menu_init()
{
	ITEM **my_items;
	ITEM *cur_item;
	MENU *my_menu;
	char c;
	char *choices[] = {"choice 1", "choice 2", "choice 3", "choice 4", "exit"};
	int size = sizeof(choices) / sizeof (choices[0]);

	//菜单项
	my_items = (ITEM **) calloc(size + 1, sizeof (ITEM *));

	for (int i = 0; i < size; i ++)
	{
		my_items[i] = new_item(choices[i], choices[i]);
	}

	my_items[size] = (ITEM *) NULL;

	//菜单
	my_menu = new_menu((ITEM **) my_items);

	mvprintw(LINES - 2, 0, "q to exit");

	//递送菜单，刷新屏幕
	post_menu(my_menu);

	refresh();

	//while ((c = getch()) != KEY_F(1))
	while ((c = getch()) != 'q')
	{
		switch(c)
		{
			case 'j':
			case KEY_DOWN:
				//更新菜单
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case 'k':
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
		}
	}
	
	//释放菜单项
	for (int i = 0; i < size; i ++)
	{
		free_item(my_items[i]);
	}

	//释放菜单
	free_menu(my_menu);

	return 0;
}

int print_in_middle(WINDOW *win, int starty, int startx, int width, char *string)
{
	int len, x, y;

	if (win == NULL)
	{
		win = stdscr;
	}
	getyx(win, y, x);

	if (startx != 0)
	{
		x = startx;
	}

	if (starty != 0)
	{
		y = starty;
	}

	if (width == 0)
	{
		width = 80;
	}

	len = strlen(string);

	int temp = (width - len) / 2;

	x = startx + temp;

	mvwprintw(win, y, x, "%s", string);
	refresh();
	
	return 0;
}

int menu_win()
{
	ITEM **my_items;
	ITEM *cur_item;
	MENU *my_menu;
	WINDOW *my_menu_win;
	char c;
	char *choices[] = {"choice 1", "choice 2", "choice 3", "choice 4", "exit"};
	int size = sizeof(choices) / sizeof (choices[0]);

	//菜单项
	my_items = (ITEM **) calloc(size + 1, sizeof (ITEM *));

	for (int i = 0; i < size; i ++)
	{
		my_items[i] = new_item(choices[i], choices[i]);
	}

	my_items[size] = (ITEM *) NULL;

	//菜单
	my_menu = new_menu((ITEM **) my_items);

	my_menu_win = newwin(10, 40, 4, 4);
	keypad(my_menu_win, TRUE);

	//设置主窗口与子窗口
	set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

	set_menu_mark(my_menu, "*");

	box(my_menu_win, 0, 0);

	print_in_middle(my_menu_win, 1, 0, 40, "my menu");

	mvwaddch(my_menu_win, 2, 0, ACS_LTEE);
	mvwhline(my_menu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(my_menu_win, 2, 39, ACS_RTEE);

	mvprintw(LINES - 2, 0, "q to exit");

	refresh();

	//递送菜单，刷新屏幕
	post_menu(my_menu);

	while ((c = wgetch(my_menu_win)) != 'q')
	{
		switch(c)
		{
			case 'j':
			case KEY_DOWN:
				//更新菜单
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case 'k':
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
		}
	}

	unpost_menu(my_menu);

	//释放菜单
	free_menu(my_menu);
	
	//释放菜单项
	for (int i = 0; i < size; i ++)
	{
		free_item(my_items[i]);
	}


	return 0;
}
int main()
{
	init();
	//menu_init();
	menu_win();
	end();
	return 0;
}
