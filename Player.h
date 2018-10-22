#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector> 

using namespace std;

class Player {
    private:
        vector<int> stack;
        string intials;
    public:
        Player();
        Player(string intit);  
        Player(string intit, vector<int> stac);

        string getInitials();
        vector<int> getStack();
        void askForNewStack();
};

#endif