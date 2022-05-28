#pragma once

#include <string>
#include <list>

using namespace std;

class node {
 private:
  int key;
  char color;
  string value;

 public:
  node* parent;
  node* left;
  node* right;
  list<string>
      collisioni;  // lista che gestisce le collisioni inserendo al suo interno
                   // un elemento che vuole accedere ad una cella occupata
  void setKey(int Key) { key = Key; }
  int getKey() { return key; }

  void setColor(char Color) { color = Color; }
  char getColor() { return color; }

  void setValue(string Value) { value = Value; }
  string getValue() { return value; }
};