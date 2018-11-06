#include "Game.h"
#include "Game_Window.h"
#include "Player.h"
#include "AI_Player.h"
#include "assert.h"

using namespace std;


int main() {
    Game* game;
    int testsPassed = 0;
    int numOfTests = 6;

    //Game class tests
    testsPassed += game->test_readHighScores();
    testsPassed += game->test_getWinner();
    testsPassed += game->test_isWinner();
    testsPassed += game->test_calculatePlayerScore(); // this one has three tests in it 
    cout << endl;
    cout << testsPassed << " of " << numOfTests << " tests passed... Done." << endl; 
    delete game;
    return 0;
}