#include "Game.h"
#include "Game_Window.h"
#include "Player.h"
#include "AI_Player.h"
#include "assert.h"

using namespace std;


int main() {
    Game* game;
    Player player = Player();
    Game_Window window = Game_Window();
    int testsPassed = 0;
    int numOfTests = 3;

    //Game class tests
    testsPassed += game->test_readHighScores();
    testsPassed += game->test_getWinner();
    testsPassed += game->test_isWinner();

    cout << endl;
    cout << testsPassed << " of " << numOfTests << " tests passed... Done." << endl; 
    game->test_flipStack(Player player);
    game->test_renderStacks();
    return 0;
}
