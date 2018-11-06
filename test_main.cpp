#include "Game.h"
#include "Game_Window.h"
#include "Player.h"
#include "AI_Player.h"
#include "assert.h"

using namespace std;


int main() {
    Game* game;
    int testsPassed = 0;
    int numOfTests = 3;

    //Game class tests
    testsPassed += game->test_readHighScores();
    testsPassed += game->test_getWinner();
    testsPassed += game->test_isWinner();

    cout << endl;
    cout << testsPassed << " of " << numOfTests << " tests passed... Done." << endl; 
    return 0;
}