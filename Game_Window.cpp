#include "Game_Window.h"

#include <iostream>
#include <stdlib.h>
#include <ncurses.h>
#include <curses.h>
#include <menu.h>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string.h>
#include "Player.h"
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 40 

vector<WINDOW*> flipVec;

//exceptions

struct IncorrectInitials : public exception {
	const char* what() const throw() {
		return "Too few/too many initials, Please enter 1-3 letters.";
	}
};

struct IncorrectAnswer : public exception {
	const char* what() const throw() {
		return "Invalid Answer. Please enter Y or N.";
	}
};

Game_Window::Game_Window() {
	return;
}

void repetitiveWindowCommandsEcho() {
	 	initscr();
		clear();
		echo();	
}

//passes 24 line test
void Game_Window::displayStartScreen(){
	int rows, cols = 0, choice = 0;
        WINDOW *my_win;
        initscr();
        getmaxyx(stdscr,rows,cols);

        printPancakes(0,0);
        mvprintw(7, 0, "Team Teamwork (18)");
        mvprintw(rows-1, 0, "Jack Shirley, Jay Khatri, Zackary Ramirez, Timothy Nguyen");
        refresh();

        my_win = create_newwin(HEIGHT, WIDTH, (rows/2) - 3, (cols/2)-25);
        keypad(my_win,true);
        while(true){
                wattron(my_win, A_BLINK);
                mvwprintw(my_win, 1, 1, "Press ENTER to start");
				choice = wgetch(my_win);
                if(choice == 10){
                        break;
                }
                wrefresh(my_win);
        }
        endwin();
}

//passes 24 line test
void Game_Window::displayInstructions() {
	int rows, col;
	initscr();
	clear();
	getmaxyx(stdscr, rows, col);
	mvprintw(rows/2 - 3, (col/2) - 25, "INSTRUCTIONS:");
	mvprintw((rows/2),((col)/2) - 25, "The goal of the game is to get the pancakes");
    mvprintw((rows/2) + 1,((col)/2) - 25, "in an ordered stack with the largest on the bottom");
    mvprintw((rows/2) + 2,((col)/2) - 25, "and the smallest on top, and beat the AI by having");
    mvprintw((rows/2) + 3,((col)/2) - 25, "less moves. The catch is, you can only sort");
    mvprintw((rows/2) + 4,((col)/2) - 25, "pancakes by repeatedly flipping a partial top");
    mvprintw((rows/2) + 5,((col)/2) - 25, "of the stack.");
	refresh();
	getch();
	endwin();
}

//passes 24 line test 
GameOptions Game_Window::queryGameOptions(){
	GameOptions options = GameOptions();
	vector<int> pancakeChoices = {2,3,4,5,6,7,8,9};
	int pancakeChoice = chooseNumbers(pancakeChoices, "Please choose the number of pancakes");
	vector<int> difficultyChoices;
	for (int i = 1; i <= pancakeChoice; i++) {
		difficultyChoices.push_back(i);
	}
	int difficultyChoice = chooseNumbers(difficultyChoices, "Please choose the difficulty");
	options.numPancakes = pancakeChoice;
	options.difficultyLevel = difficultyChoice;
	return options;
}

// Function takes in a list of numbers and a message, and asks which number the user would like to use.
// Returns what the user chose.

//needs some mad revisions to get under 24 lines 
int Game_Window::chooseNumbers(std::vector<int> choices, std::string message) {
	vector<std::string> str_choices;
	int n_choices = choices.size();

	for (int i = 0; i < n_choices; i++) {
		str_choices.push_back(std::to_string(choices[i]));
	}

	int highlight = 1, choice = 0, rows, cols = 0, input_char;

	initscr();
	clear();
	noecho();
	cbreak();
    getmaxyx(stdscr,rows,cols);
	WINDOW* menu_win = create_newwin(choices.size()+4, WIDTH, (rows/2)-12, (cols/2)-3);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, message.c_str());
	refresh();
	printMenu(menu_win, highlight, str_choices);
	while(true){	
		input_char = wgetch(menu_win);
		switch(input_char)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", input_char, input_char);
				refresh();
				break;
		}
		printMenu(menu_win, highlight, str_choices);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	clrtoeol();
	refresh();
	endwin();
	return choices[choice-1];
}


//needs some mad revisions to get under 24 lines 
int Game_Window::chooseNumbersSetup(std::vector<int> choices, std::string message) {
	vector<std::string> str_choices;
	int n_choices = choices.size();

	for (int i = 0; i < n_choices; i++) {
		str_choices.push_back(std::to_string(choices[i]));
	}

	int highlight = 1, choice = 0, yMax, xMax, input_char;
	initscr();
	clear();
	noecho();
	cbreak();
    getmaxyx(stdscr,xMax,yMax);
	WINDOW* menu_win = newwin(choices.size()+4, 15, (xMax/2), (yMax/2));
	keypad(menu_win, TRUE);
	mvprintw(0, 0, message.c_str());
	refresh();
	printMenu(menu_win, highlight, str_choices);
	while(true)
	{	
		input_char = wgetch(menu_win);
		switch(input_char)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", input_char, input_char);
				refresh();
				break;
		}
		printMenu(menu_win, highlight, str_choices);
		if(choice != 0)	
			break;
	}	
	clrtoeol();
	refresh();
	endwin();
	return choice-1;
}


//passes 24 lines 
vector<int> Game_Window::displaySetupScreen(int size) {
	initscr();
	clear();
	noecho();
	cbreak();

	vector<int> initVec;
   	string msg= "Type in the next pancake 1-"+ to_string(size)+", enter 0 for a random list";		
	
	initVec = makeStartVec(size, msg);
//a	
	////pstack = initVec;
	//aistack = makeAiStack(size);	

	return initVec;
}


vector<int> Game_Window::makeAiStack(int size){
	vector<int> random;
	for(int x=0; x<size; x++)
		random.push_back(x);
	random_shuffle(random.begin(), random.end());
	return random;

}

int Game_Window::selectPancake(int size){
	int row,col;
	//repetitiveWindowCommandsEcho();
 	getmaxyx(stdscr,row,col);

	int inputChar;
	int currentChoice=1;
	int oldChoice;
	while(true)
	{	
		inputChar = getch();
		//cout << inputChar<<"XX";
		switch(inputChar)
		{	case 65:
				if(currentChoice != size-1)
				{
					oldChoice=currentChoice;
					currentChoice++;
				}
				break;
			case 66:
				if(currentChoice != 0)
				{
					oldChoice=currentChoice;
					currentChoice--;
				}
				break;
			case 10:{
				for(int x=currentChoice-1; x<flipVec.size(); x++)
					wattron(flipVec[x], A_BLINK);
				usleep(3000000);
				for(int x=currentChoice-1; x<flipVec.size(); x++)
					wattroff(flipVec[x], A_BLINK);
				return currentChoice-1;
				break;
			default:
				mvprintw(24, 0, "Invalid key entered, please use the up down error and enter");
				refresh();
				break;
			}
		}
	
		mvprintw(24, 0, "                                                           ");
		mvprintw(HEIGHT-3*oldChoice-1, 22, "                 ");
		mvprintw(HEIGHT-3*currentChoice-1,22 ,"<-------");

		//refresh();
		
		
		
	}	
	

	return 1;




}

//passes 24 lines
vector<int> Game_Window::makeStartVec(int size, string msg){

	vector<int> order, newOrder, random;
        for(int x=0; x<size+1; x++) {order.push_back(x);}

	while((int)newOrder.size()!=size) {
                int index=chooseNumbersSetup(order,msg);
                if(index==0) {
                        for(int x=0; x<size; x++)
                random.push_back(x);
                random_shuffle(random.begin(), random.end());
                        return random;
                } else {
                        newOrder.push_back(order[index]);
                        order.erase(order.begin()+index);
                }
        }
        return newOrder;
}


void Game_Window::renderStacks(vector<int> playerStack, vector<int> aiStack){
	
	int rows, cols = 0, choice = 0;

	WINDOW *my_win;

	initscr();
        clear();
        noecho();
        cbreak();
	
	//mvprintw(7, 0, "Team Teamwork (18)");
	
	refresh();	
	
	//cout << "PSTACK SIZE: " << playerStack.size() << endl;


	
	int playerStackSize = playerStack.size();
	int aiStackSize = aiStack.size();
	
	for(int x = 0; x < playerStackSize; x++){
		drawHumanPancake(x, playerStack.at(x)+1);	
	}

//	while(true){
//		choice = wgetch(my_win);
//		if(choice == 10){
//			break;
//		}
//		wrefresh(my_win);
//	}
//	endwin();

	/*
	for(int y = 0; y < aiStackSize; y++){
		drawAiPancake(y);
	}
	*/
	//getch();
	

//	refresh();
}


void Game_Window::drawHumanPancake(int x, int pancakeSize){
	WINDOW* my_win;
	my_win = newwin(3, pancakeSize * 2+1, HEIGHT - (x * 3) - 4, 0);
	wborder(my_win, '|', '|', '-', '-', '+', '+', '+', '+');
	string str = to_string(pancakeSize);
	mvwprintw(my_win, 1, pancakeSize, str.c_str());
	wrefresh(my_win);
	
	flipVec.push_back(my_win);	
}


void Game_Window::drawAiPancake(int size){

}


WINDOW* Game_Window::create_newwin(int height, int width, int starty, int startx)
{       
	WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0 , 0);
    wrefresh(local_win);
	return local_win;
}

void Game_Window::printMenu(WINDOW *menu_win, int highlight, vector<std::string> choices)
{
	int n_choices = choices.size();
	int x = 2, y = 2, i;	
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
		++y;
	}
	wrefresh(menu_win);
}


void Game_Window::printPancakes(int y, int x){
        mvprintw(y, x, "__________                              __                  ");
        mvprintw(y+1, x, "|______   |_____    ____   ____ _____ |  | __ ____   ______");
        mvprintw(y+2, x, " |     ___||__  |  /    \\_/ ___\\__ \\  |  |/ // __ \\/  ___/");
        mvprintw(y+3, x, " |    |    / __ | |   |  \\  \\___ / __\\|    <\\ ___/\\___\\ ");
        mvprintw(y+4, x, " |____|    (____  /___|  /\\___  >____ |__|_ \\___  >____  >");
        mvprintw(y+5, x, "                \\/     \\/     \\/     \\/    \\/   \\/     \\/ ");
}

void Game_Window::getInitials(Player& player) {
		char printMessage[]="Please enter your initials: ";	
		char init[80];
 		int row,col;
		repetitiveWindowCommandsEcho();
 		getmaxyx(stdscr,row,col);
	try {
 		mvprintw(row/2,(col-strlen(printMessage))/2,"%s",printMessage);
 		getstr(init);
		string playerInitials(init);
		if (playerInitials.size() < 1 || playerInitials.size() > 3) {
			throw IncorrectInitials();
		}
		player.setName(playerInitials);
 		endwin();
	}
	catch (IncorrectInitials& e) {
		mvprintw((row/2) + 3,(col-strlen(printMessage))/2 - 10, e.what());
		refresh();
		getch();
		endwin();
		getInitials(player);
	}
}

void Game_Window::printHighScores(vector<string> entry, Player player) {
	int row, col;
	string line = "\n", space = " ", currentPlayer = "";
	char title[] = "Top 5 High Scores";
	initscr();
	clear();
	getmaxyx(stdscr, row, col);
	int entrySize = entry.size();
	mvprintw((row/2) - 4, (col/2) - 7, "%s", title);
	for (int index = 0; index < entrySize; index++) {
		entry[index] += '\n';
		string s = entry[index];
		mvprintw((row/2) + index, (col/2), "%s", s.c_str());
	}
	currentPlayer += player.getInitials();
	currentPlayer += " ";
	currentPlayer += to_string(player.getScore());
	mvprintw((row/2) + 6, (col/2), "%s", currentPlayer.c_str());
	refresh();
	getch();
	endwin();
}

void Game_Window::printEndMessage(int winner, Player& playr) {
	int row, col;
	string message;
	string playerScore = "Score: ";
	playerScore  += to_string(playr.getScore());
	initscr();
	echo();
	clear();
	getmaxyx(stdscr, row, col);
	if (winner == 1) {
		message = "CONGRATS, you have beaten the computer!!";
	}
	else if (winner == 2) {
		message = "Do better ;/, the computer has defeated you!";
	}
	else if (winner == 3) {
		message = "You and the computer tied, better luck next time!";
	}
	mvprintw((row/2), (col/2), "%s", message.c_str());
	mvprintw((row/2) + 5, (col/2), "%s", playerScore.c_str());
	mvprintw((row/2) + 7, (col/2), "%s", "Press ENTER to continue...");
	refresh();
	getch();
	endwin();
}

void Game_Window::playAgain(Player& playr) {
	int row, col, num = 0;
	bool value;
	initscr();
	echo();
	clear();
	getmaxyx(stdscr, row, col);

	vector<int> choices = {1, 2};
	string message = "Choose 1 to play again or 2 to quit. (1/2): ";
	value = chooseNumbersSetup(choices, message);
	if (num == 1) {
		value = true;
	}
	else if (num == 2) {
		value = false;
	}
	playr.setPlayAgain(value);
	endwin();
}



/* ---------------------------------------------------------------------------------------
						TESTING FUNCTIONS

	--------------------------------------------------------------------------------------*/
