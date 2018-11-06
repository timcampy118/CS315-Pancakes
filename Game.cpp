#include <ncurses.h> 
#include <vector>
#include <iostream>
#include "string.h"
#include <fstream>
#include <algorithm>
#include <unistd.h>
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
	bool toPlayAgain = false;
	pregameProcedures();
	while(keepPlaying){
		if(toPlayAgain){
			pregameProcedures();
		}
		int indexInput;
		window.renderStacks(player.getStack(), computer.getStack());
		indexInput = window.selectPancake(player.getStack().size());
		flipStack(player,indexInput);
		anyWinners = isWinner();
		if (anyWinners) {
			determineWinnerInfo(keepPlaying);
			toPlayAgain = player.getPlayAgainAns();
		}
		
		//break;	

	}
	// window.getInitials(player);
    // window.printHighScores(highscoreRows, player);
    
}

//determines the score and prints the appropriate information 
void Game::determineWinnerInfo(bool &shouldPlay) {
	int winner = 0;
	winner = getWinner(player, computer);
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
	playerSorted = is_sorted(playerStac.begin(), playerStac.end());
	computerSorted = is_sorted(compStac.begin(), compStac.end());
	if (playerSorted == true || computerSorted == true) {
		return true;
	}
	else {
		return false;
	}
}

//returns the winner 
int Game::getWinner(Player playr, AI_Player comp) {
	bool playerSorted = false, computerSorted = false;
	vector<int> playerStac = playr.getStack(), compStac = comp.getStack();
	playerSorted = is_sorted(playerStac.begin(), playerStac.end());
	computerSorted = is_sorted(compStac.begin(), compStac.end());
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



void Game::renderStacksTest(){
	vector<int> v{1,2,3,4};
	player.setStack(v);
	window.renderStacks(player.getStack(), computer.getStack());
	usleep(1500000);
	vector<int> u{5,6,7,8,9,4};
	player.setStack(u);
	window.renderStacks(player.getStack(), computer.getStack());
	usleep(1500000);
	vector<int> x{1,2,3,4,5,6};
	player.setStack(x);
	window.renderStacks(player.getStack(), computer.getStack());
	usleep(1500000);
	vector<int> a{2,3,4,5,6,7};
	player.setStack(a);
	window.renderStacks(player.getStack(), computer.getStack());
	usleep(1500000);
	vector<int> b{1,2,3,4,5};
	player.setStack(b);
	window.renderStacks(player.getStack(), computer.getStack());
	usleep(1500000);
}

void Game::flipStackTest(Player player){
	vector<int> v{1,2,3,4};
	player.setStack(v);
	flipStack(player,2);
	cout<<"expected output 1 2 4 3"<<endl;

	vector<int> u{5,6,7,8,9,4};
	player.setStack(u);
	flipStack(player,4);
	cout<<"expected output 5 6 7 8 4 9"<<endl;

	vector<int> x{1,2,3,4,5,6};
	player.setStack(x);
	flipStack(player,0);
	cout<<"expected output 6 5 4 3 2 1"<<endl;

	vector<int> a{2,3,4,5,6,7};
	player.setStack(a);
	flipStack(player,1);
	cout<<"expected output 2 7 6 5 4 3"<<endl;

	vector<int> b{1,2,3,4,5};
	player.setStack(b);
	flipStack(player,4);
	cout<<"expected output 1 2 3 4 5"<<endl;
}


void Game::flipStack(Player player, int index) {
	
	vector<int> tmpStack;
	for(int x=0; x<index;x++)
		tmpStack.push_back(player.getStack()[x]);	
	
	for(int x=player.getStack().size()-1; x>=index; x--)
		tmpStack.push_back(player.getStack()[x]);

	player.setStack(tmpStack);


	for(int x=0; x<player.getStack().size(); x++)
		cout<<player.getStack()[x]<<" ";
	cout<<endl;	
	
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

void Game::test_getWinner() {
	Player play;
	AI_Player comp;
	int expected = 1, actual = 0;
	vector<int> playerStack = {1, 2, 3, 4, 5}, compStack = {1, 3, 2, 4, 5};
	play.setStack(playerStack);
	comp.setStack(compStack);
	actual = getWinner(play, comp);
	if (expected == actual) {
		cout << "test_getWinner == PASSED" << endl;
	}
	else {
		cout << "test_getWinner == FAILED" << endl;
	}
	
}

