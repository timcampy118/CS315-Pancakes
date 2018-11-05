#include "AI_Player.h"

#include "search_node.h"
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

std::vector<int> AI_Player::getStack() {
    return this->stack;
}

void AI_Player::setStack(std::vector<int> stac) {
    this->stack = stac;
}

vector<int> AI_Player::searchAndGenerateNewMove(int maxDepth) {
  std::priority_queue<Node *> queue;
  queue.push(new Node(stack));
  Node *bestNode = queue.top();
  std::unordered_set<std::string> visited;
  while (!queue.empty()) {
    // Get the top() element from the queue and remove it.
    Node* currentNode = queue.top();
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
  Node *current = finalNode->parent;
  Node *prev = finalNode;
  while (current->parent) {
    prev = current;
    current = current->parent;
  }
  return prev->stack;
}

