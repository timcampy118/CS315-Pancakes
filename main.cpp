
#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <menu.h>

#include <cstring>
#include <string.h>
#include "Game_Window.h"

using namespace std;

int main(){
	Game_Window game1;
	game1.displayStartScreen();
	vector<int> pancakeChoices = {2,3,5,6,7,8,9};
	int pancakeChoice = game1.chooseNumbers(pancakeChoices, "Please choose the number of pancakes");
	vector<int> difficultyChoices;
	for (int i = 1; i <= pancakeChoice; i++) {
		difficultyChoices.push_back(i);
	}
	int difficultyChoice = game1.chooseNumbers(difficultyChoices, "Please choose the difficulty");
	cout << difficultyChoice;
	return 0;
}

