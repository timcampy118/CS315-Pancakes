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
        vector<string> highscoreRows;
        GameOptions options;
    public:
        Game();
	void play();
	void printHighScores(Player player);
        vector<Player> fillPlayerVector();
        vector<string> readHighScores(string file);
	void flipStack(Player player, int index);
        bool isWinner();
        int getWinner();
        void calculatePlayerScore(int winner);
        void pregameProcedures();
        void determineWinnerInfo(bool &shouldPlay);



        //test functions 
        void test_readHighScores();
};

#endif

