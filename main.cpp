
#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <menu.h>

#include <cstring>
#include <string.h>
#include "Game_Window.h"
#include "Game.h"

using namespace std;

int main(){
	Game* game = new Game();
	game->play();
	delete game;
	return 0;
}

