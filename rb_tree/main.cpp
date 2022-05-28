#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "rbtree.h"

using namespace std;

int main() {
  RBtree obj;

  int ch;
  int y = 0;

  vector<string> arr;
  int j = 0;
  string n;
  int count = 0;
  string line;
  string part1, part2;
  int num1;
  char char1, char2;
  ifstream File;
  File.open("input.txt");
  while (getline(File, line))
    count++;  // vedo il numero di coppie <key,value>
  File.close();

  int allKey[count];
  string allValue[count];
  File.open("input.txt");

  File >> char1 >> num1 >> char2 >> part1;
  allValue[j] = part1;  // metto in allValue tutti i valori
  allKey[j] = num1;     // e in allKey tutte le chiavi
  j++;

  while (getline(File, line) && File >> char1 >> num1 >> char2 >> part1)
  // scompongo ogni riga in char ('<'), numero (key), char (',') e stringa
  // (value)
  {
    allValue[j] = part1;
    allKey[j] = num1;
    j++;
  }

  File.close();
  string prova1;
  int i;
  for (i = 0; i < count; i++) {
    // elimino l'ultimo carattere ('>') dalla stringa
    allValue[i].erase(remove(allValue[i].begin(), allValue[i].end(), '>'),
                      allValue[i].end());
  }

  for (i = 0; i < count; i++) {
    obj.insert(allKey[i], allValue[i]);  // riempio l'albero
  }
  do {
    cout << "\n\t RED BLACK TREE ";
    cout << "\n 1. Inserisci nell'albero ";
    cout << "\n 2. Rimuovi un nodo dell'albero";
    cout << "\n 3. Cerca un elemento nell'albero";
    cout << "\n 4. Stampa l'albero ";
    cout << "\n 5. Esci ";
    cout << "\nEffettua una scelta: ";
    cin >> ch;
    int newKey;
    string newValue;

    switch (ch) {
      case 1:
        cout << "Inserisci la chiave del nuovo elemento: ";
        cin >> newKey;

        cout << "Inserisci la stringa del nuovo elemento: ";
        cin >> newValue;

        obj.insert(newKey, newValue);

        break;
      case 2:
        cout << "Inserisci la chiave dell'elemento da eliminare: ";
        cin >> newKey;
        cout << "Inserisci il valore dell'elemento da eliminare: ";
        cin >> newValue;

        obj.del(newKey, newValue);
        break;
      case 3:
        cout << "Inserisci la chiave dell'elemento da cercare: ";
        cin >> newKey;
        cout << "Inserisci il valore dell'elemento da cercare: ";
        cin >> newValue;
        obj.search(newKey, newValue);
        break;
      case 4:

        cout << "ALBERO RB" << endl;
        obj.disp();

        break;
      case 5:
        y = 1;
        break;
      default:
        cout << "\nInserisci una scelta valida!";
    }
    cout << endl;
  } while (y != 1);
  return 1;
}
