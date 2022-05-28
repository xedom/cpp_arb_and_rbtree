#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <string>

#include "arb.h"

using namespace std;

int main() {
  ARB bst;

  string line;
  int num1;
  string part1;
  int j = 0;
  int count = 0;

  ifstream File;
  File.open("input.txt");
  while (getline(File, line)) {
    count++;
  }

  int allKey[count];
  string allValue[count];

  File.close();

  File.open("input.txt");

  while (getline(File, line, ',')) {
    line.erase(remove(line.begin(), line.end(), '<'), line.end());
    allKey[j] = stoi(line);
    num1 = allKey[j];

    getline(File, allValue[j], '\n');
    allValue[j].erase(remove(allValue[j].begin(), allValue[j].end(), '>'),
                      allValue[j].end());
    part1 = allValue[j];

    j++;

    bst.insert_rb(num1, part1);
  }
  File.close();

  bst.insert_rb(31, "fvj");
  bst.insert_rb(52, "sdf");
  bst.insert_rb(20, "ghg");
  bst.insert_rb(98, "dld");
  bst.insert_rb(75, "sgh");
  bst.insert_rb(68, "bnb");
  bst.insert_rb(54, "uvs");

  bst.search(31);
  bst.search(21);
  bst.search(68);

  bst.print();

  cout << endl << "After deleting" << endl;

  bst.deleteNode(98);
  bst.print();
}
