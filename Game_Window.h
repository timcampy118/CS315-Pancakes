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
#include "Player.h"

class Game_Window {
    public:
        Game_Window();
	WINDOW *create_newwin(int height, int width, int starty, int startx);
	void displayStartScreen();
	void queryGameOptions();
	void printPancakes(int x, int y);
    private:
	void printMenu(WINDOW *menu_win, int highlight, vector<std::string> choices);
};

// Struct to hold the options provided by the user.
struct GameOptions {
	int numPancakes;
	int difficultyLevel;
}


#endif
