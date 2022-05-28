#include "arb.h"

using namespace std;

ARB::ARB() {
  NULLNODE = new Node;
  NULLNODE->left = nullptr;
  NULLNODE->right = nullptr;
  NULLNODE->color = 'b';
  root = NULLNODE;
}

void ARB::insert_rb(int key, string value) {
  int id = hashfunction(key);

  Node* n = new Node;
  n->parent = nullptr;
  n->data = id;

  n->chiave = key;
  n->val = value;

  n->left = NULLNODE;
  n->right = NULLNODE;
  n->color = 'r';

  insert_abr(n);
  cout << id << endl;
}

int ARB::hashfunction(int key) {
  int m = 800;

  float sez_aurea = 0.618;

  float val = key * sez_aurea;

  int intero = (int)val;

  float decimale = val - intero;

  float val2 = m * decimale;

  int val3 = (int)val2;

  return val3;
}

void ARB::insert_abr(Node* n) {
  Node* Y = nullptr;
  Node* X = this->root;

  while (X != NULLNODE) {
    Y = X;
    if (n->data == X->data) {
      X->lista.push_back(n);
    }
    if (n->data < X->data) {
      X = X->left;
    } else {
      X = X->right;
    }
  }
  n->parent = Y;
  if (Y == nullptr) {
    root = n;
  } else if (n->data == Y->data) {
    Y->lista.push_back(n);
  } else if (n->data < Y->data) {
    Y->left = n;
  } else {
    Y->right = n;
  }

  if (n->parent == nullptr)  // approfondire questo if
  {
    n->color = 'b';
    return;
  }

  if (n->parent->parent == nullptr)  // approfondire questo if
  {
    return;
  }

  if (n->data != Y->data) {
    insert_fixup(n);
  }
}

void ARB::insert_fixup(Node* n) {
  Node* Y;

  while (!(n->parent->color == 'b')) {
    if (n->parent == n->parent->parent->left) {
      Y = n->parent->parent->right;
      if (Y->color == 'r') {
        n->parent->color = 'b';
        Y->color = 'b';
        n->parent->parent->color = 'r';
        n = n->parent->parent;
      } else {
        if (n == n->parent->right) {
          n = n->parent;
          left_Rotate(n->parent->parent);
        }
        n->parent->color = 'b';
        n->parent->parent->color = 'r';
        right_Rotate(n->parent->parent);
      }
    } else {
      Y = n->parent->parent->left;
      if (Y->color == 'r') {
        n->parent->color = 'b';
        Y->color = 'b';
        n->parent->parent->color = 'r';
        n = n->parent->parent;
      } else {
        if (n == n->parent->left) {
          n = n->parent;
          right_Rotate(n->parent->parent);
        }
        n->parent->color = 'b';
        n->parent->parent->color = 'r';
        left_Rotate(n->parent->parent);
      }
    }

    if (n == root) {
      break;
    }
  }
  root->color = 'b';
}

void ARB::left_Rotate(Node* X) {
  Node* Y = X->right;
  X->right = Y->left;

  if (Y->left != NULLNODE) {
    Y->left->parent = X;
  }

  Y->parent = X->parent;

  if (X->parent == nullptr) {
    this->root = Y;
  } else if (X == X->parent->left) {
    X->parent->left = Y;
  } else {
    X->parent->right = Y;
  }

  Y->left = X;
  X->parent = Y;
}

void ARB::right_Rotate(Node* X) {
  Node* Y = X->left;
  X->left = Y->right;

  if (Y->right != NULLNODE) {
    Y->right->parent = X;
  }

  Y->parent = X->parent;

  if (X->parent == nullptr) {
    this->root = Y;
  } else if (X == X->parent->right) {
    X->parent->right = Y;
  } else {
    X->parent->left = Y;
  }

  Y->right = X;
  X->parent = Y;
}

void ARB::deleteNode(int key) {
  int id = hashfunction(key);
  delete_Node_private(this->root, id);
}

void ARB::delete_Node_private(Node* n, int key) {
  Node* Z = NULLNODE;
  Node* X;
  Node* Y;

  while (n != NULLNODE) {
    if (n->data == key) {
      Z = n;
    }

    if (n->data <= key) {
      n = n->right;
    } else {
      n = n->left;
    }
  }

  if (Z == NULLNODE) {
    cout << "LA CHIAVE INSERITA NON E' STATA TROVATA" << endl;
    return;
  }

  if (Z->lista.size() != 0) {
    Node* first = Z->lista.front();
    Z->lista.pop_front();
    first->lista = Z->lista;
    insert_rb(first->chiave, first->val);
  }

  Y = Z;
  int Y_orig_color = Y->color;

  if (Z->left == NULLNODE) {
    X = Z->right;
    rb_transplant(Z, Z->right);
  } else if (Z->right == NULLNODE) {
    X = Z->left;
    rb_transplant(Z, Z->left);
  } else {
    Y = minimum(Z->right);
    Y_orig_color = Y->color;
    X = Y->right;

    if (Y->parent == Z) {
      X->parent = Y;
    } else {
      rb_transplant(Y, Y->right);
      Y->right = Z->right;
      Y->right->parent = Y;
    }

    rb_transplant(Z, Y);
    Y->left = Z->left;
    Y->left->parent = Y;
    Y->color = Z->color;
  }

  if (Y_orig_color == 'b') {
    delete_fixup(X);
  }
}

void ARB::delete_fixup(Node* X) {
  Node* W;
  while (X != root && X->color == 'b') {
    if (X == X->parent->left) {
      W = X->parent->right;
      if (W->color == 'r') {
        W->color = 'b';
        X->parent->color = 'r';
        left_Rotate(X->parent);
        W = X->parent->right;
      }

      if (W->left->color == 'b' && W->right->color == 'b') {
        W->color = 'r';
        X = X->parent;
      } else {
        if (W->right->color == 'b') {
          W->left->color = 'b';
          W->color = 'r';
          right_Rotate(W);
          W = X->parent->right;
        }

        W->color = X->parent->color;
        X->parent->color = 'b';
        W->right->color = 'b';
        left_Rotate(X->parent);
        X = root;
      }
    } else {
      W = X->parent->left;
      if (W->color == 'r') {
        W->color = 'b';
        X->parent->color = 'r';
        right_Rotate(X->parent);
        W = X->parent->left;
      }

      if (W->right->color == 'b' && W->right->color == 'b') {
        W->color = 'r';
        X = X->parent;
      } else {
        if (W->left->color == 'b') {
          W->right->color = 'b';
          W->color = 'r';
          left_Rotate(W);
          W = X->parent->left;
        }

        W->color = X->parent->color;
        X->parent->color = 'b';
        W->left->color = 'b';
        right_Rotate(X->parent);
        X = root;
      }
    }
  }

  X->color = 'b';
}

void ARB::rb_transplant(Node* u, Node* v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }

  v->parent = u->parent;
}

ARB::Node* ARB::minimum(Node* n) {
  while (n->left != NULLNODE) {
    n = n->left;
  }

  return n;
}

void ARB::print() {
  if (root) {
    preorderPrint(this->root);
  }
}

void ARB::preorderPrint(Node* node) {
  if (node != NULLNODE) {
    char Color;
    if (node->color == 'b') {
      Color = 'B';
    } else {
      Color = 'R';
    }

    cout << node->val << ' ' << Color << endl;

    if (node->left != NULLNODE) {
      cout << "il figlio sx di " << node->val << " e' " << node->left->val
           << endl;
    } else {
      cout << "non ci sono figli sx" << endl;
    }
    if (node->right != NULLNODE) {
      cout << "il figlio dx di " << node->val << " e' " << node->right->val
           << endl;
    } else {
      cout << "non ci sono figli dx" << endl;
    }

    cout << endl;

    preorderPrint(node->left);

    preorderPrint(node->right);
  }
}

void ARB::search(int key) {
  int id = hashfunction(key);
  if (search_node(this->root, id, key) == key) {
    cout << "chiave " << key << " trovata" << endl;
  } else {
    cout << "chiave " << key << " non trovata" << endl;
  }
}

int ARB::search_node(Node* node, int id, int key) {
  if (node == NULLNODE || id == node->data) {
    if (node->lista.size() != 0) {
      list<Node*>::iterator it;
      for (it = node->lista.begin(); it != node->lista.end(); it++) {
        if ((*it)->chiave == key) {
          // cout<<(*it)->chiave<<endl;
          return (*it)->chiave;
        }
      }
    }
    // cout<<node->chiave<<endl;
    return node->chiave;
  }

  if (id < node->data) {
    return search_node(node->left, id, key);
  } else {
    return search_node(node->right, id, key);
  }
}
