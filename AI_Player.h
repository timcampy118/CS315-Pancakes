#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include "search_node.h"

using namespace std;

class AI_Player {
    private:
        std::vector<int> stack;
    public:
	std::vector<int> getStack();
	void setStack(std::vector<int> stac);

	std::vector<int> determineNextMove(Node* finalNode);
	vector<int> searchAndGenerateNewMove(int maxDepth);
	int test_searchAndGenerateNewMove();
};

#endif
