// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <algorithm>

class Tree {
 public:
  explicit Tree(std::vector<char> init) :rootNode(nullptr) {
    createPermutations(init);
  }
  std::vector<std::vector<char>> getPerm() const {
    return permutations;
  }

 private:
  struct Node {
    char character;
    std::vector<Node*> childs;
    explicit Node(char character_ = '\0') :character(character_) {}
  };
  Node* rootNode;
  std::vector<std::vector<char>> permutations;

  void addNode(Node* newRootNode, std::vector<char> row) {
    if (!newRootNode) {
      rootNode = newRootNode = new Node;
    }
    for (char character : row) {
      Node* temp = new Node(character);
      newRootNode->childs.push_back(temp);
      std::vector<char> newRow(row);
      newRow.erase(std::find(newRow.begin(), \
        newRow.end(), character));
      addNode(temp, newRow);
    }
  }

  void evadeTree(Node* newRootNode, std::vector<char> row) {
    if (newRootNode != nullptr && newRootNode->character != '\0')
      row.push_back(newRootNode->character);
    if (newRootNode->childs.empty())
      permutations.push_back(row);
    for (Node* childs : newRootNode->childs) {
      evadeTree(childs, row);
    }
  }

  void createPermutations(std::vector<char> row) {
    addNode(rootNode, row);
    evadeTree(rootNode, {});
  }
};
#endif  // INCLUDE_TREE_H_
