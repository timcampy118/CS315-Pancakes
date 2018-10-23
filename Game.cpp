#include <ncurses.h> 

int main()
{
	initscr();

	// Write a string to the screen.
	printw("Hellow World");

	// Get the key code of what the user typed.
	int c = getch();

	// Print the code to the screen.
	printw("%d", c);

	// Refresh the window to reflect the 'c' that's in memory.
	refresh();

	// This code is necessary for ending the window.
	getch();
	endwin();

	return 0;
}
