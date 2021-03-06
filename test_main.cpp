#include "Game.h"
#include "Game_Window.h"
#include "Player.h"
#include "AI_Player.h"
#include "assert.h"

using namespace std;

int main() {
    Game* game;
    AI_Player computer = AI_Player();
    Player player = Player();
    Game_Window window = Game_Window();
    int testsPassed = 0;
    int numOfTests = 6;

    //AI Player class tests
    testsPassed += computer.test_searchAndGenerateNewMove();

    //Game class tests
    testsPassed += game->test_readHighScores();
    testsPassed += game->test_getWinner();
    testsPassed += game->test_isWinner();
    testsPassed += game->test_calculatePlayerScore(); // this one has three tests in it 
    cout << endl;
    cout << testsPassed << " of " << numOfTests << " tests passed... Done." << endl; 
    //game->test_flipStack(player);
    //game->test_renderStacks();
    return 0;
}
