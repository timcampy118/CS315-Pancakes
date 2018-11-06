#include "search_node.h"
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// helper functions for printing
void printNestedVector(vector<vector<int> > input);
void printVector(vector<int> input);

vector<int> flipAndGenerateNewStack(vector<int> playerStack, int index);
vector<vector<int> > generateSuccessors(vector<int> stack);
vector<int> determineNextMove(Node* finalNode);
vector<int> searchAndGenerateNewMove(vector<int> stack, int maxDepth);

int main() {
  static const int arr2[] = { 4,3,2,1 };
  vector<int> vec2 (arr2, arr2 + sizeof(arr2) / sizeof(arr2[0]) );
  vector<int> nextMove = searchAndGenerateNewMove(vec2, 2);
  printVector(nextMove);
}

void printVector(vector<int> input) {
  int size = input.size();
  for(int i=0; i< size; ++i) {
    std::cout << input[i] << ' ';
  }
  std::cout << "\n";
}

void printNestedVector(vector<vector<int> > input) {
  int size = input.size();
  for(int i=0; i < size; ++i) {
    printVector(input[i]);
  }
}

vector<int> searchAndGenerateNewMove(vector<int> stack, int maxDepth) {
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
    int size = successors.size();
    for (int j = 0; j < size; j++) {
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
  return determineNextMove(bestNode);
}

vector<int> determineNextMove(Node* finalNode) {
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


