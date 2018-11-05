#include <ncurses.h> 
#include <vector>
#include <iostream>
#include "string.h"
#include <fstream>
#include <algorithm>
#include "Player.h"
#include "Game_Window.h"
#include "Game.h"
#include "assert.h"
#include "AI_Player.h"

using namespace std;

// constructor
Game::Game(){
	player = Player();
	computer = AI_Player();
	window = Game_Window();

	highscoreRows = readHighScores("high_scores.txt");
	window.displayStartScreen();
	window.displayInstructions();
}

void Game::pregameProcedures() {
		options = window.queryGameOptions();
		vector<int> init = window.displaySetupScreen(options.numPancakes);
		player.setStack(init);
		computer.setStack(init);
		numOfPancakes = options.numPancakes;
		diff = options.difficultyLevel;
		window.getInitials(player);
		window.printHighScores(highscoreRows, player);
}

void Game::play(){
	bool keepPlaying = true;
	bool anyWinners = false;
	while(keepPlaying){
		pregameProcedures();
		int indexInput;
		window.renderStacks(player.getStack(), computer.getStack());
		window.selectPancake(player.getStack().size());
		//indexInput = window.getUserInput(player.getStack().size()) //new function
		//flipStack(player,indexInput);
		anyWinners = isWinner();
		if (anyWinners) {
			determineWinnerInfo(keepPlaying);
		}
		
		//break;	
	}
	// window.getInitials(player);
    // window.printHighScores(highscoreRows, player);
}

//determines the score and prints the appropriate information 
void Game::determineWinnerInfo(bool &shouldPlay) {
	int winner = 0;
	winner = getWinner();
	calculatePlayerScore(winner);
	window.printEndMessage(winner, player);
	window.printHighScores(highscoreRows, player);
	printHighScores(player);
	window.playAgain(player);
	shouldPlay = !(player.getPlayAgainAns()); //idek but let it be lol
}

//calculates the palyers score based on the difficulty
void Game::calculatePlayerScore(int winner) {
	int scor = 0;
	switch(winner) {
		case 1:		//player has sorted stack and computer does not 
			scor = 2 * numOfPancakes * (diff + 1);
			player.setScore(scor);
			break;	
		case 2:		//computer is sorted, but the player is not 
			scor = numOfPancakes;
			player.setScore(scor);
			break;
		case 3:		//both stacks are sorted
			scor = numOfPancakes * (diff + 1);
			player.setScore(scor);
			break;
		default:	//shouldn't ever get to here but prep
			scor = 1;
			player.setScore(scor);
			break;
	}
}

//determines if either player has won
// can write a test for this 
bool Game::isWinner() {
	bool playerSorted = false, computerSorted = false;
	vector<int> playerStac = player.getStack(), compStac = computer.getStack();
	playerSorted = true;
	computerSorted = true;
	// playerSorted = is_sorted(playerStac.begin(), playerStac.end());
	// computerSorted = is_sorted(compStac.begin(), compStac.end());
	if (playerSorted == true || computerSorted == true) {
		return true;
	}
	else {
		return false;
	}
}

//returns the winner 
int Game::getWinner() {
	bool playerSorted = false, computerSorted = false;
	vector<int> playerStac = player.getStack(), compStac = computer.getStack();
	playerSorted = true;
	computerSorted = true;
	// playerSorted = is_sorted(playerStac.begin(), playerStac.end());
	// computerSorted = is_sorted(compStac.begin(), compStac.end());
	if (playerSorted == true && computerSorted == false) {
		return 1;
	}
	else if (playerSorted == false && computerSorted == true) {
		return 2;
	}
	else if (playerSorted == true && computerSorted == true) {
		return 3;
	}
	return -20;
}




void Game::flipStack(Player player, int index) {
	reverse(player.getStack().begin(),player.getStack().begin()+index);
}

//reads in the highscores.txt
//helper function to printHighScores
vector<string> Game::readHighScores(string file) {
	string filename = file;
	ifstream ist{filename}; // ist reads from the file named iname
	string entry;
	vector<string> entries;
	while (getline(ist, entry))
		entries.push_back(entry);
	ist.close();	
	return entries;
}
//helper function to printHighScores
vector<Player> Game::fillPlayerVector() {
	vector<string> entries = readHighScores("high_scores.txt");
	vector<Player> dummyPlayers;
	int entriesSize = entries.size();
	try {
		if (entriesSize == 0) {
			dummyPlayers = vector<Player>();
			return dummyPlayers;
		}
		for (int index = 0; index < entriesSize; index++) {
			string s = entries[index];
			string tempInitials;
			string tempScoreString = s.substr(s.find(" ") + 1);
			//cout << "TEMPSCORESTRING: " << tempScoreString << endl;
			int tempScore = stoi(tempScoreString);
			
			//grabs the intials by delimiting a space character
			int entriesIndex = entries[index].size();
			for (int j = 0; j < entriesIndex; j++) {
				if (entries[index][j] != ' ') {
					tempInitials.push_back(entries[index][j]);
				}
				else if (entries[index][j] == ' ') {
					break;
				}
			}
			Player highScorePlayer(tempInitials, tempScore);
			dummyPlayers.push_back(highScorePlayer);
		}
		return dummyPlayers;
	}
	catch(exception& e) {
		cerr << "Exception: " << e.what() << endl;
		return vector<Player>();
	}
}


void Game::printHighScores(Player player) {
	string filename = "high_scores.txt";
	vector<string> entries = readHighScores(filename);
	vector<Player> dummyPlayers;
	dummyPlayers = fillPlayerVector();
	int dummyPlayersSize = dummyPlayers.size();
	if (dummyPlayersSize == 0 || dummyPlayersSize < 5) {
		dummyPlayers.push_back(player);
	} else { //will eventually need to sort these high scores
		for (int index = 0; index < dummyPlayersSize; index++) {
			if (player.getScore() > dummyPlayers[index].getScore()) {
				dummyPlayers[index] = player;
				break;
			}
		}
	}
	sort(dummyPlayers.begin(), dummyPlayers.end());
	ofstream ofs(filename);
	for (Player p : dummyPlayers) {
		ofs << p.getInitials() << " " << p.getScore() << endl;
	}
}



/* ---------------------------------------------------------------------------------------
						TESTING FUNCTIONS

	--------------------------------------------------------------------------------------*/


void Game::test_readHighScores() {
	vector<string> expected = {"ZR 100", "LG 80", "NC 75", "CD 25", "TD 15"};
	vector<string> input = readHighScores("test_high_scores.txt");
	if (expected == input) {
		cout << "test_readHighScores == PASSED" << endl;
	}
	else {
		cout << "test_readHighScores == FAILED" <<endl;
	}
}
