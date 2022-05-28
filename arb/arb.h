#pragma once

#include <string>
#include "node.h"

using namespace std;

class ARB : public Node {
 private:
  Node* root;
  Node* NULLNODE;

  void insert_fixup(Node*);
  void preorderPrint(Node*);
  void rb_transplant(Node*, Node*);
  void delete_Node_private(Node*, int);
  void delete_fixup(Node*);
  int search_node(Node*, int, int);

 public:
  ARB();

  void insert_rb(int, string);
  void insert_abr(Node*);
  void deleteNode(int);
  void print();
  void left_Rotate(Node*);
  void right_Rotate(Node*);
  Node* minimum(Node*);
  int hashfunction(int key);
  int countNode(Node* root);
  void search(int key);
};