#include "AI_Player.h"

#include "search_node.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue> 

using namespace std;

void printVector(vector<int> output);

// temp main for testing...
//int main() {
//	// expected next move is 5,4,2,1,3
//	// expected next move is 5,4,3,1,2
//	AI_Player* my_player = new AI_Player();
//
//	vector<int> stack1 = {5, 4, 2, 3, 1};
//	my_player->setStack(stack1);
//	vector<int> output1 = my_player->searchAndGenerateNewMove(5);
//	cout << "result: ";
//	printVector(output1);
//
//	stack1 = {5, 4, 1, 3,2};
//	my_player->setStack(stack1);
//	output1 = my_player->searchAndGenerateNewMove(5);
//	cout << "result: ";
//	printVector(output1);
//
//	stack1 = {5, 4, 1, 2, 3};
//	my_player->setStack(stack1);
//	output1 = my_player->searchAndGenerateNewMove(5);
//	cout << "result: ";
//	printVector(output1);
//
//	stack1 = {5, 4, 3, 2, 1};
//	my_player->setStack(stack1);
//	output1 = my_player->searchAndGenerateNewMove(5);
//	cout << "result: ";
//	printVector(output1);
//
//	cout << endl << endl << endl;
//	vector<int> stack2 = {5, 4, 2, 1, 3};
//	my_player->setStack(stack2);
//	vector<int> output2 = my_player->searchAndGenerateNewMove(5);
//	cout << "result: ";
//	printVector(output2);
//
//	stack2 = {5, 4, 3, 1, 2};
//	my_player->setStack(stack2);
//	output2 = my_player->searchAndGenerateNewMove(5);
//	cout << "result: ";
//	printVector(output2);
//
//	stack2 = {5, 4, 3, 2,1};
//	my_player->setStack(stack2);
//	output2 = my_player->searchAndGenerateNewMove(5);
//	cout << "result: ";
//	printVector(output2);
//}

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
    printVector(current->stack);
    current = current->parent;
  }
  printVector(current->stack);
  cout << "current stack ";
  printVector(this->stack);
  //printVector(prev->stack);
  //cout << prev->sortedness << endl;
  return current->stack;
}

