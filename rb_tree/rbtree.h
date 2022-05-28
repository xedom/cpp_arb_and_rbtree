#pragma once

#include <string>
#include "node.h"

using namespace std;

class RBtree {
  node* root;
  node* q;

 public:
  RBtree() {
    q = NULL;
    root = NULL;
  }
  void insert(int id, string value);
  void insertfix(node*);
  void leftrotate(node*);
  void rightrotate(node*);
  void del(int id, string value);
  node* successor(node*);
  void delfix(node*);
  void disp();
  void display(node*);
  void search(int id, string value);
};