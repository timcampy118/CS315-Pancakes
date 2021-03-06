#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <menu.h>
#include <algorithm>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>
#include <string.h>
#include "Player.h"

struct GameOptions;

// Struct to hold the options provided by the user.
struct GameOptions {
	public: 
		int numPancakes;
		int difficultyLevel;
};

class Game_Window {
    public:
        Game_Window();
		WINDOW *create_newwin(int height, int width, int starty, int startx);
		int chooseNumbers(std::vector<int> choices, std::string message);
		int chooseNumbersSetup(std::vector<int> choices, std::string message);
		void displayStartScreen();
		GameOptions queryGameOptions();
		void printPancakes(int x, int y);
		vector<int> displaySetupScreen(int size);
		vector<int> makeStartVec(int size, string msg);
		void drawBottomHumanPancake(int pancakeSize, int playerStackSize);
		void renderStacks(vector<int> playerStack, vector<int> aiStack);
		void drawHumanPancake(int x, int pancakeSize, int playerStackSize);
		void drawAiPancake(int x, int pancakeSize, int aiStackSize);
		void printMenu(WINDOW *menu_win, int highlight, vector<std::string> choices);
		void getInitials(Player& player);
		void printHighScores(vector<string> entry, Player player);
		void displayInstructions();
		vector<int> makeAiStack(int size);
		int selectPancake(int size);	
		void playAgain(Player& playr);
		void printEndMessage(int winner, Player& playr);
		void destroyWindow();	
};

#endif
