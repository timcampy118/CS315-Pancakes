#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector> 

using namespace std;

class Player {
    private:
        vector<int> stack;
        string initials;
        int score;
    public:
        Player() {
            initials = "NA";
            score = 10;
        }
        Player(int scor) {
            score = scor;
            initials = "NA";
        }
        Player(string init, int scor) {
            initials = init;
            score = scor;
        }
        Player(string init, vector<int> stac) {
            initials = init;
            stack = stac;
        }
        Player(string init, vector<int> stac, int scor) {
            initials = init;
            stack = stac;
            score = scor;
        }
        string getInitials();
        int getScore();
        vector<int> getStack();
        void askForNewStack();
        void setStack(vector<int> stac) {
            stack = stac;
        }
        bool operator < (const Player& play) {
            return (score > play.score);
        }
};

#endif
