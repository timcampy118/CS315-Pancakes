#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "AI_Player.h"
#include "Game_Window.h"

class Game {
    private:
        Player player;
        AI_Player computer;
        Game_Window window;
        int numOfPancakes;
        int diff;
    public:
        Game();
	void printHighScores(Player player);
        vector<Player> fillPlayerVector();
        vector<string> readHighScores();
};

#endif

