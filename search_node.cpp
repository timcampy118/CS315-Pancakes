#include "search_node.h"

#include <queue>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int determineSortedness(vector<int> stack);

Node::Node(vector<int> stack): stack(stack) {
  // determine the sortedness of the stack and set it to sortedness;
  this->sortedness = this->determineSortedness();
  this->depth = 0;
  this->parent = nullptr;
}

std::string Node::toString(){
  std::string output;
  for(int i = 0; i < this->stack.size(); i++) {
    int val = this->stack[i];
    output.append(std::to_string(val));
  }
  return output;
}

// given a vector, generate all of its successors
vector<Node*> Node::successors() {
  vector<Node* > result;
  for(int i = 1; i < this->stack.size(); i++) {
    Node* resultNode = this->flipAndGenerateNewNode(i-1);
    resultNode->parent = this;
    resultNode->depth = this->depth + 1;
    result.push_back(resultNode);
  }
  return result;
}

Node* Node::flipAndGenerateNewNode(int index) {
  vector<int> newStack = this->stack;
	reverse(newStack.begin()+index, newStack.end());
  Node* returnNode = new Node(newStack);
  return returnNode;
}

int Node::determineSortedness() {
  int prev = 0;
  int sortedness = 0;
  for (int i = this->stack.size()-1; i >= 0; i--) {
    int curr = this->stack[i];
    if (prev > curr) {
      sortedness++;
    }
    prev = curr;
  }
  return sortedness;
}


