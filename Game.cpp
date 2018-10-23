#include <ncurses.h> 
#include <vector>
#include <iostream>
#include "string.h"
#include <fstream>
#include <algorithm>
#include "Player.h"
#include "Game_Window.h"
#include "Game.h"

using namespace std;

// constructor
Game::Game(){
    player = Player();
    computer = AI_Player();
    window = Game_Window();
    window.displayStartScreen();
    numOfPancakes = 8;
    diff = 1;
}

//reads in the highscores.txt
//helper function to printHighScores
vector<string> Game::readHighScores() {
	string filename = "high_scores.txt";
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
	vector<string> entries = readHighScores();
	vector<Player> dummyPlayers;
	int entriesSize = entries.size();
	for (int index = 0; index < entriesSize; index++) {
		string s = entries[index];
		string tempInitials;
		string tempScoreString = s.substr(s.find(" ") + 1);
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


void Game::printHighScores(Player player) {
	string filename = "high_scores.txt";
	vector<string> entries = readHighScores();
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



int main()
{
	Game game = Game();
	// vector<string> test;
	
	// test = game.readHighScores();
	// Player yo = Player(75);

	// game.printHighScores(yo);
	// test = game.readHighScores();
	// for (int index = 0; index < test.size(); index++) {
	// 	cout << test[index] << endl;
	// }

	return 0;
}
