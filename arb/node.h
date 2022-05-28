#pragma once

#include <string>
#include <list>

using namespace std;

class Node {
 public:
  int data;
  Node* left;
  Node* right;
  Node* parent;
  char color;
  string val;
  int chiave;
  list<Node*> lista;
};