#include "Game_Window.h"

#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <menu.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string.h>
#include "Player.h"

#define WIDTH 30
#define HEIGHT 10 

Game_Window::Game_Window() {
	return;
}

void Game_Window::displayStartScreen(){
	int rows, cols = 0;
        WINDOW *my_win;

        initscr();
        getmaxyx(stdscr,rows,cols);
        cout << rows << endl;

        printPancakes(0,0);
        mvprintw(7, 0, "Team Teamwork (18)");
        mvprintw(rows-1, 0, "Jack Shirley, Jay Khatri, Zackary Ramirez, Timothy Nguyen");
        refresh();

        my_win = create_newwin(HEIGHT, WIDTH, (rows/2)-12, (cols/2)-3);
        keypad(my_win,true);

        int choice = 0;
        while(true){
                wattron(my_win, A_BLINK);
                mvwprintw(my_win, 1, 1, "Press ENTER to start");
				choice = wgetch(my_win);
                if(choice == 10){
                        break;
                }
                wrefresh(my_win);
        }
        mvprintw(25, 0, "The goal of the game is to get the pancakes");
        mvprintw(26, 0, "in an ordered stack with the largest on the bottom");
        mvprintw(27, 0, "and the smallest on top, and beat the AI by having");
        mvprintw(28, 0, "less moves. The catch is, you can only sort");
        mvprintw(29, 0, "pancakes by repeatedly flipping a partial top");
        mvprintw(30, 0, "of the stack.");
        endwin();
}

GameOptions Game_Window::queryGameOptions(){
	GameOptions options = GameOptions();
	vector<int> pancakeChoices = {2,3,5,6,7,8,9};
	int pancakeChoice = chooseNumbers(pancakeChoices, "Please choose the number of pancakes");
	vector<int> difficultyChoices;
	for (int i = 1; i <= pancakeChoice; i++) {
		difficultyChoices.push_back(i);
	}
	int difficultyChoice = chooseNumbers(difficultyChoices, "Please choose the difficulty");
	options.numPancakes = pancakeChoice;
	options.difficultyLevel = difficultyChoice;
	return options;
}

// Function takes in a list of numbers and a message, and asks which number the user would like to use.
// Returns what the user chose.
int Game_Window::chooseNumbers(std::vector<int> choices, std::string message) {
	vector<std::string> str_choices;
	int n_choices = choices.size();

	for (int i = 0; i < n_choices; i++) {
		str_choices.push_back(std::to_string(choices[i]));
	}

	int highlight = 1;
	int choice = 0;
	int rows, cols = 0;
	int input_char;

	initscr();
	clear();
	noecho();
	cbreak();
        getmaxyx(stdscr,rows,cols);
	WINDOW* menu_win = create_newwin(HEIGHT, WIDTH, (rows/2)-12, (cols/2)-3);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, message.c_str());
	refresh();
	printMenu(menu_win, highlight, str_choices);
	while(1){	
		input_char = wgetch(menu_win);
		switch(input_char)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", input_char, input_char);
				refresh();
				break;
		}
		printMenu(menu_win, highlight, str_choices);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	clrtoeol();
	refresh();
	endwin();
	return choices[choice-1];
}

vector<int> Game_Window::displaySetupScreen(int size){
        initscr(); noecho(); timeout(0); int x;
        vector<int> order; vector<int> remain; vector<int> random;
         for(int x=0; x<size; x++){
                remain.push_back(x+1);}
        while((int)(order.size())!=size){
                move(x,0);
                printw("Type in the next pancake 1-%d, type 0 for a random list",size);
                x++;int c=getch();
                while(getch()!=10){
                        int tmp=c; c=getch()-48;
                        if(c==-38||c==tmp||c==-49)
                                c=tmp;
                        else{
                        move(0+x,0);
                        printw("%d\n", c); x++;}}
                if(c==0){       
                        for(int x=0; x<size; x++){
                                random.push_back(x);
			}
                        random_shuffle(random.begin(), random.end());
			return random;
		}
                else if(c>0&&c<=(size)){
                                order.push_back(c);
                                printw("Added"); x++;}
                else
                printw("Invalid input");}
        printw("Done"); 
	return order;
}

WINDOW* Game_Window::create_newwin(int height, int width, int starty, int startx)
{       
	WINDOW *local_win;

        local_win = newwin(height, width, starty, startx);
        box(local_win, 0 , 0);
        wrefresh(local_win);

        return local_win;
}

void Game_Window::printMenu(WINDOW *menu_win, int highlight, vector<std::string> choices)
{
	int n_choices = choices.size();
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
		++y;
	}
	wrefresh(menu_win);
}


void Game_Window::printPancakes(int y, int x){
        mvprintw(y, x, "__________                              __                  ");
        mvprintw(y+1, x, "|______   |_____    ____   ____ _____ |  | __ ____   ______");
        mvprintw(y+2, x, " |     ___||__  |  /    \\_/ ___\\__ \\  |  |/ // __ \\/  ___/");
        mvprintw(y+3, x, " |    |    / __ | |   |  \\  \\___ / __\\|    <\\ ___/\\___\\ ");
        mvprintw(y+4, x, " |____|    (____  /___|  /\\___  >____ |__|_ \\___  >____  >");
        mvprintw(y+5, x, "                \\/     \\/     \\/     \\/    \\/   \\/     \\/ ");
}
