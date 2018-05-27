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

int main()
{
	init();
	menu_init();
	end();
	return 0;
}
