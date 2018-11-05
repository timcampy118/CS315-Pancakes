#ifndef SEARCH_NODE_H
#define SEARCH_NODE_H

#include <queue>
#include <string>
#include <vector>

using namespace std;

// This is a node that will perform logic at each 
class Node {
  public:
    Node(vector<int> stack);
    vector<int> stack;
    Node *parent;
    int depth;
    int sortedness;
    Node* flipAndGenerateNewNode(int index);
    std::vector<Node *> successors();
    int determineSortedness();
    std::string toString();
};

// helper functions

#endif
