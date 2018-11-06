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
	    Player flipStack(Player player, int index);
        void flipStackTest(Player player);
        void renderStacksTest();
        bool isWinner(Player playr, AI_Player comp);
        int getWinner(Player playr, AI_Player comp);
        void calculatePlayerScore(Player& play, int winner, int pancakes, int difficultt);
        void pregameProcedures();
        void determineWinnerInfo(bool &shouldPlay);



        //test functions 
        int test_readHighScores();
        int test_getWinner();
        int test_isWinner();
        int test_calculatePlayerScore();
};

#endif

