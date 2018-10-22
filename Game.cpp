#include <ncurses.h> 

int main()
{
	initscr();
	printw("Hellow World");
	refresh();
	getch();
	return 0;
}