#include <stdio.h>
#include <ncurses.h>
#include <string.h>

int hello()
{
	initscr();
	printw("Hello world");
	refresh();
	getchar();
	endwin();

	return 0;
}

int init_test()
{
	int ch;
	initscr(); /*初始化*/
	raw();     /*禁用行缓存*/
	//cbreak();
	keypad(stdscr,TRUE); /*允许使用功能键*/
	noecho();            /*输入不回显*/
	//echo();            /*输入回显*/
	printw("type any character to see it in bold\n");
	ch = getch();
	if (ch == KEY_F(1))
	{
		printw("F1 key pressed\n");
	}
	else
	{
		printw("the pressed key is ");
		attron(A_BOLD);
		printw("%c", ch);
		attroff(A_BOLD);
	}
	refresh();/*打印到显示器*/
	getch();
	endwin();/*结束*/
	
	return 0;
}

/*初始化*/
int init()
{
	initscr(); 
	raw();
	keypad(stdscr,TRUE);
	noecho();
	
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

/*输出*/
int output()
{
	/*addch(ch) 输出单个字符*/
	addch('z');
	addch('z' | A_BOLD | A_UNDERLINE);
	/*mvaddch(row, col, ch) 移到指定位置输出字符*/
	mvaddch(2,0,'z');
	move(3, 0);
	addch('z');
	/* printw 输出功能
	 * mvprintw 移动到指定位置,并输出
	 * wprintw 指定窗口输出
	 * mvwprintw 指定窗口,移动到指定位置，并输出
	 */
	char msg[]= "just a string";
	int row,col;
	getmaxyx(stdscr, row, col); /*取得stdscr的行数和列数*/
	mvprintw(row/2, (col-strlen(msg))/2, "%s", msg);
	//mvprintw(0, 0, "row:%d, col:%d", row, col);
	mvprintw(row/2 + 1, (col-strlen(msg))/2, "row:%d, col:%d", row, col);
	/* addstr(string) 输出字符串
	 * mvaddstr() 指定位置输出
	 * mvwaddstr() 窗口
	 * waddstr()   窗口
	 */
	addstr(msg);
	mvaddstr(row/2 + 2, (col-strlen(msg))/2, msg);
	mvaddstr(row/2 + 3, (col-strlen(msg))/2, msg);

	return 0;
}

/*输入*/
int input()
{
	/* getch() 从键盘读取一个字符
	 * scanw() 
	 * mvscanw()
	 * wscanw()
	 * mvscanw()
	 * vwscanw()
	 * */
	char ch;
	ch = getch();
	addch(ch);
	addch('\n');
	addch(ch);
	/* getstr() 读取字符串
	 * */
	char str[16] = {0};
	getstr(str);
	addstr(str);

	return 0;
}

/*文字修饰*/
int attribute()
{
	char str[16] = {0};
	getstr(str);
	addstr(str);
	/* A_NORMAL   普通字符输出
	 * A_STANDOUT 终端字符最亮
	 * A_UNDERLINE 下划线
	 * A_REVERSE   字符反白显示
	 * A_BLINK     闪动显示
	 * A_DIM       半亮显示
	 * A_BOLD      加亮加粗
	 * A_PROTECT   保护模式
	 * A_INVIS     空白显示
	 * A_ALTCHARSET 字符交替
	 * A_CHARTEXT   字符掩盖
	 * COLOR_PAIR(n) 前景、背景色设置
	 * */
	/*调用处开始设置属性*/
	attron(A_BOLD);
	addstr(str);
	addch('\n');
	attroff(A_BOLD);

	attron(A_UNDERLINE);
	addstr(str);
	addch('\n');
	attroff(A_UNDERLINE);

	attron(A_BLINK);
	addstr(str);
	addch('\n');
	attroff(A_BLINK);

	attron(A_REVERSE);
	addstr(str);
	addch('\n');
	attroff(A_REVERSE);

	attron(A_BOLD | A_UNDERLINE);
	addstr(str);
	addch('\n');
	attroff(A_BOLD | A_UNDERLINE);

	/*设置整个窗口属性*/
	//attrset(A_UNDERLINE);
	addstr(str);
	addch('\n');

	/* attr_get 获取属性
	 * chgat()  用来修改已输出字符的修饰
	 * wchgat()
	 * mvchgat()
	 * */
	mvchgat(0, 0, -1, A_BLINK, 1, NULL);
	mvchgat(4, 0, -1, A_BLINK, 3, NULL);
		/* 1 指定行
		 * 2 指定列
		 * 3 修改字符个数, -1表示整行
		 * 4 属性
		 * 5 颜色索引
		 * 6 NULL
		 * */

	return 0;
}

WINDOW *create_newwin(int heigth, int width, int starty, int startx)
{
	WINDOW *mywin;
	/*建立窗口，内存分配等
	 * heigth 高
	 * width  宽
	 * starty 起始列
	 * startx 起始行
	 * */

	mywin = newwin(heigth, width, starty, startx);
	/*画边框*/
	//box(mywin, 0, 0);
	wborder(mywin, '|','|','-','-','x','x','x','x');
	/*显示*/
	wrefresh(mywin);
	return mywin;
}

int destroy_win(WINDOW *mywin)
{
	//box(mywin, '', '');
	wborder(mywin, ' ',' ',' ',' ',' ',' ',' ',' ');
	/* 1 当前操作的窗口
	 * 2 左边界字符
	 * 3 右边界字符
	 * 4 上边界字符
	 * 5 下边界字符
	 * 6 左上角字符
	 * 7 右上角字符
	 * 8 左下角字符
	 * 9 右下角字符
	 * */
	wrefresh(mywin);
	delwin(mywin);

	return 0;
}

int opera_win(WINDOW *mywin, int heigth, int width, int starty, int startx)
{
	int ch;
	while((ch = getch()) != 'q')
	{
		switch(ch)
		{
			case KEY_LEFT:
				destroy_win(mywin);
				mywin = create_newwin(heigth, width, starty, --startx);
				break;
			case KEY_RIGHT:
				destroy_win(mywin);
				mywin = create_newwin(heigth, width, starty, ++startx);
				break;
			case KEY_UP:
				destroy_win(mywin);
				mywin = create_newwin(heigth, width, --starty, startx);
				break;
			case KEY_DOWN:
				destroy_win(mywin);
				mywin = create_newwin(heigth, width, ++starty, startx);
				break;
		}
	}

	return 0;
}

int create_box(int heigth, int width, int starty, int startx)
{
	/* mvhline(y, x, ch, n) 指定位置划n个ch行线
	 * mvvline(y, x, ch, n) 指定位置划n个ch列线
	 * */

	/*未使用win窗口,以后完善*/

	return 0;
}


/*窗口*/
int win()
{
	WINDOW *mywin;
	int startx, starty, width, heigth;
	int ch;

	heigth = 20;
	width = 40;

	/*COLS行数 LINES列数*/
	startx = (COLS - width)/ 2;
	starty = (LINES - heigth)/ 2;
	//startx = 0;
	//starty = 0;

	printw("press q to exit");

	refresh();

	mywin = create_newwin(heigth, width, starty, startx);
	opera_win(mywin, heigth, width, starty, startx);

	return 0;
}

int color()
{
	/*检测是否支持彩色显示*/
	if (has_colors() == FALSE)
	{
		printf("no support color");
		return 0;
	}

	/*启动彩色机制*/
	start_color();
	/*设置彩色，参数, 前景色，背景色*/
	init_pair(1, COLOR_RED, COLOR_BLACK);

	attron(COLOR_PAIR(1));
	char str[16] = {0};
	getstr(str);
	addstr(str);
	attroff(COLOR_PAIR(1));

	return 0;
}

int main()
{
	init();
 	//output();
	//input();
	//attribute();
	//win();
 	color();
	end();
	return 0;
}
