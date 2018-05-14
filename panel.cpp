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

/*面板*/
int panel_show()
{
	WINDOW *mywin[3];
	PANEL *mypanel[3];
	int lines = 10, cols = 40, y = 2, x = 4, i;

	mywin[0] = newwin(lines, cols, y, x);
	mywin[1] = newwin(lines, cols, y + 1, x + 5);
	mywin[2] = newwin(lines, cols, y + 2, x + 10);

	for (i = 0; i < 3; i ++)
	{
		box(mywin[i], 0, 0);
	}

	/*面板关联窗口*/
	/*面板0压进栈*/
	mypanel[0] = new_panel(mywin[0]);
	/*面板1压进栈*/
	mypanel[1] = new_panel(mywin[1]);
	/*面板2压进栈*/
	mypanel[2] = new_panel(mywin[2]);

	/*面板2位于栈顶*/
	update_panels();

	/*显示*/
	doupdate();

	return 0;
}

/*面板切换*/
int panel_tab()
{
	WINDOW *mywin[3];
	PANEL *mypanel[3];
	int lines = 10, cols = 40, y = 2, x = 4, i;

	mywin[0] = newwin(lines, cols, y, x);
	mywin[1] = newwin(lines, cols, y + 1, x + 5);
	mywin[2] = newwin(lines, cols, y + 2, x + 10);

	for (i = 0; i < 3; i ++)
	{
		box(mywin[i], 0, 0);
	}

	/*面板关联窗口*/
	/*面板0压进栈*/
	mypanel[0] = new_panel(mywin[0]);
	/*面板1压进栈*/
	mypanel[1] = new_panel(mywin[1]);
	/*面板2压进栈*/
	mypanel[2] = new_panel(mywin[2]);


	/*建立用户指针, 此处存储下一个面板*/
	set_panel_userptr(mypanel[0], mypanel[1]);
	set_panel_userptr(mypanel[1], mypanel[2]);
	set_panel_userptr(mypanel[2], mypanel[0]);

	/*面板2位于栈顶*/
	update_panels();

	/*显示*/
	doupdate();

	int ch;
	PANEL *top = mypanel[2];

	while((ch = getch()) != 'q')
	{
		switch(ch)
		{
			case 'c':
				top = (PANEL *) panel_userptr(top);
				/*设为栈顶*/
				top_panel(top);
				break;
		}
		update_panels();
		doupdate();
	}

	return 0;
}

/*我是分隔线*/
typedef struct st_panel_data
{
	int x, y, h, w;
	char label[80];
	PANEL *next;
}PANEL_DATA;

int set_panel_data(PANEL **panels, int n)
{
	PANEL_DATA *ptrs;
	WINDOW *win;
	int x, y, w, h,i;
	char temp[80];
	
	ptrs = (PANEL_DATA *) calloc(n, sizeof(PANEL_DATA));

	for (i = 0; i < n; i ++)
	{
		win = panel_window(panels[i]);
		getbegyx(win, y, x);
		getmaxyx(win, h, w);

		ptrs[i].x = x;
		ptrs[i].y = y;
		ptrs[i].h = h;
		ptrs[i].w = w;

		sprintf(temp,"window number:%d", i + 1);
		strcpy(ptrs[i].label, temp);
		
		if (i + 1 == n)
		{
			ptrs[i].next = panels[0];
		}
		else
		{
			ptrs[i].next = panels[i + 1];
		}

		set_panel_userptr(panels[i], &ptrs[i]);
	}

	return 0;
}

int print_in_middle(WINDOW *win, int starty, int startx, int width, char *szstring)
{
	int len, x, y;
	int temp;
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
		width = 80;

	len = strlen(szstring);
	temp = (width - len) / 2;

	x = startx + temp;
	mvwprintw(win, y, x, "%s", szstring);

	refresh();
	return 0;
}

int win_show(WINDOW *win, char *szlabel)
{
	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);

	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE, width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);

	print_in_middle(win, 1, 0, width, szlabel);

	return 0;
}
int init_wins(WINDOW **wins, int n)
{
	int x, y, i;
	char szlabel[80] = {0};

	y = 2;
	x = 10;

	for (int i = 0; i < n; i ++)
	{
		wins[i] = newwin(10, 40, y, x);
		sprintf(szlabel, "window number %d", i + 1);
		win_show(wins[i], szlabel);
		y += 3;
		x += 7;
	}

	return 0;
}

/*面板移动与设置大小*/
int panel_change()
{
	WINDOW *mywin[3];
	WINDOW *new_win, *old_win;
	PANEL *mypanel[3];
	int lines = 10, cols = 40, y = 2, x = 4, i;

	init_wins(mywin, 3);

	/*面板关联窗口*/
	/*面板0压进栈*/
	mypanel[0] = new_panel(mywin[0]);
	/*面板1压进栈*/
	mypanel[1] = new_panel(mywin[1]);
	/*面板2压进栈*/
	mypanel[2] = new_panel(mywin[2]);

	set_panel_data(mypanel, 3);

	/*面板2位于栈顶*/
	update_panels();

	/*显示*/
	doupdate();

	bool issize = false, ismove = false;
	int ch;
	int newx, newy, newh, neww;
	PANEL *top = mypanel[2];
	PANEL_DATA *top_data = (PANEL_DATA *) panel_userptr(top);
	newx = top_data->x;
	newy = top_data->y;
	newh = top_data->h;
	neww = top_data->w;

	while((ch = getch()) != 'q')
	{
		switch(ch)
		{
			case 'c':
				top_data = (PANEL_DATA *) panel_userptr(top);
				top_panel(top_data->next);
				top = top_data->next;
				top_data = (PANEL_DATA *) panel_userptr(top);
				newx = top_data->x;
				newy = top_data->y;
				newh = top_data->h;
				neww = top_data->w;
				break;
			case 'r':
				issize = true;
				mvprintw(LINES - 4, 0, "entered key to resize, and <ENTER> to end resize");
				refresh();
				break;
			case 'm':
				ismove = true;
				mvprintw(LINES - 4, 0, "entered key to move, and <ENTER> to end move");
				refresh();
				break;
			case KEY_LEFT:
				if (issize)
				{
					--newx;
					++neww;
				}
				if (ismove)
				{
					--newx;
				}
				break;
			case KEY_RIGHT:
				if (issize)
				{
					++newx;
					--neww;
				}
				if (ismove)
				{
					++newx;
				}
				break;
			case KEY_UP:
				if (issize)
				{
					--newy;
					++newh;
				}
				if (ismove)
				{
					--newy;
				}
				break;
			case KEY_DOWN:
				if (issize)
				{
					++newy;
					--newh;
				}
				if (ismove)
				{
					++newy;
				}
				break;
			case 10:
				if (issize)
				{
					old_win = panel_window(top);
					new_win = newwin(newh, neww, newy, newx);
					replace_panel(top, new_win);
					win_show(new_win, top_data->label);
					delwin(old_win);
					issize = false;
				}
				if (ismove)
				{
					move_panel(top, newy, newx);
					ismove = false;
				}
		}
		refresh();
		update_panels();
		doupdate();
	}

	return 0;
}
/*我是分隔线*/
int main()
{
	init();
	//panel_show();
	//panel_tab();
	panel_change();
	end();
	return 0;
}
