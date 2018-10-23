#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H
#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <menu.h>

#include <thread>
#include <chrono>

#include <cstring>
#include <string.h>
#include "Game.h"

class Game_Window {
    public:
        Game_Window();
	WINDOW *create_newwin(int height, int width, int starty, int startx);
	void displayStartScreen();
	void printPancakes(int x, int y);
		
};

Game_Window::Game_Window(){
//	int x = 24;
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

        my_win = create_newwin(5, 23, (rows/2)-12, (cols/2)-3);
        keypad(my_win,true);


        int choice = 0;
        while(true){
                wattron(my_win, A_REVERSE);
                mvwprintw(my_win, 1, 1, "Press ENTER to start");
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
                wattroff(my_win, A_REVERSE);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		choice = wgetch(my_win);
                if(choice == 10){
                        break;
                }
                wrefresh(my_win);
        }

        mvprintw(25, 0, "Started");

        getch();
        endwin();
	
}




WINDOW* Game_Window::create_newwin(int height, int width, int starty, int startx)
{       
	WINDOW *local_win;

        local_win = newwin(height, width, starty, startx);
        box(local_win, 0 , 0);
        wrefresh(local_win);

        return local_win;
}


void Game_Window::printPancakes(int y, int x){
        mvprintw(y, x, "__________                              __                  ");
        mvprintw(y+1, x, "|______   |_____    ____   ____ _____ |  | __ ____   ______");
        mvprintw(y+2, x, " |     ___||__  |  /    \\_/ ___\\__ \\  |  |/ // __ \\/  ___/");
        mvprintw(y+3, x, " |    |    / __ | |   |  \\  \\___ / __\\|    <\\ ___/\\___\\ ");
        mvprintw(y+4, x, " |____|    (____  /___|  /\\___  >____ |__|_ \\___  >____  >");
        mvprintw(y+5, x, "                \\/     \\/     \\/     \\/    \\/   \\/     \\/ ");
}








#endif
