#include "AI_Player.h"

#include "search_node.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue> 

using namespace std;

void printVector(vector<int> output);

void printVector(vector<int> output) {
	for(int i = 0; i < output.size(); i++) {
		cout << output[i] << " ";
	}
	cout << endl;
}

std::vector<int> AI_Player::getStack() {
    return this->stack;
}

void AI_Player::setStack(std::vector<int> stac) {
    this->stack = stac;
}

vector<int> AI_Player::searchAndGenerateNewMove(int maxDepth) {
  std::queue<Node *> queue;
  queue.push(new Node(stack));
  Node *bestNode = queue.front();
  std::unordered_set<std::string> visited;
  bool best_sort_possible = false;
  while (!queue.empty() && !best_sort_possible) {
    // Get the top() element from the queue and remove it.
    Node* currentNode = queue.front();
    queue.pop();
    // If we've seen the node already, forget about it.
    if (visited.find(currentNode->toString()) != visited.end() || currentNode->depth > maxDepth) {
      continue;
    } else {
      visited.insert(currentNode->toString());
    }

    // generate successors
    vector<Node *> successors = currentNode->successors();
    for (int j = 0; j < successors.size(); j++) {
      Node *successor = successors[j];
      if (successor->sortedness < bestNode->sortedness) {
        bestNode = successor;
      }
      if (successor->sortedness == 0) {
	best_sort_possible = true;
        break;
      }
      queue.push(successor);
    }
  }
  std::vector<int> result = determineNextMove(bestNode);
  this->stack = result;
  return result;
}

vector<int> AI_Player::determineNextMove(Node* finalNode) {
  if (finalNode->depth <= 1) {
    return finalNode->stack;
  }
  Node *current = finalNode;
  while (current->parent->stack != this->stack) {
    current = current->parent;
  }
  return current->stack;
}

int AI_Player::test_searchAndGenerateNewMove() {
	int numPassed = 0;

	vector<int> stack = {5, 4, 2, 3, 1};
	vector<int> expected = {5, 4, 1, 3, 2};
	this->setStack(stack);
	vector<int> output = this->searchAndGenerateNewMove(5);
	if (output == expected) {
		cout << "Test (1) of test_searchAndGenerateNewMove == PASSED" << endl;
		numPassed += 1;
	} else {
		cout << "Test (1) of test_searchAndGenerateNewMove == FAILED" << endl;
	}

	stack = {5, 4, 1, 3, 2};
	expected = {5, 4, 1, 2, 3};
	this->setStack(stack);
	output = this->searchAndGenerateNewMove(5);
	if (output == expected) {
		cout << "Test (2) of test_searchAndGenerateNewMove == PASSED" << endl;
		numPassed += 1;
	} else {
		cout << "Test (2) of test_searchAndGenerateNewMove == FAILED" << endl;
	}

	stack = {5, 4, 2, 1, 3};
	expected = {5, 4, 3, 1, 2};
	this->setStack(stack);
	output = this->searchAndGenerateNewMove(5);
	if (output == expected) {
		cout << "Test (3) of test_searchAndGenerateNewMove == PASSED" << endl;
		numPassed += 1;
	} else {
		cout << "Test (3) of test_searchAndGenerateNewMove == FAILED" << endl;
	}

	return numPassed;
}


