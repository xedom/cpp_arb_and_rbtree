#include "rbtree.h"

void RBtree::insert(int id, string value) {
  node *p, *q;
  node* t = new node;
  id = id % 100;

  t->setKey(id);
  t->left = NULL;
  t->right = NULL;
  t->setColor('r');  // default
  p = root;
  q = NULL;
  int found = 0;
  if (root == NULL)  // controllo se già esiste una radice, altrimenti
                     // l'elemento che inseriamo sarà la radice
  {
    root = t;
    t->parent = NULL;
  } else {
    while (p != NULL && found == 0) {
      q = p;
      if (id == p->getKey())  // controlliamo se esiste un nodo con lo stesso id
        found = 1;

      if (found == 0) {
        t->setValue(value);
        if (p->getKey() < t->getKey())
          p = p->right;
        else
          p = p->left;
      }
    }
    if (found == 0) {  // se non lo troviamo, inseriamo il nodo nell'albero
      cout << "Nodo con ID " << id << " inserito correttamente" << endl;
      t->parent = q;
      if (q->getKey() < t->getKey())
        q->right = t;
      else
        q->left = t;
    } else {
      // se esiste un nodo con lo stesso id, lo aggiungiamo nella lista
      // associata al nodo che ha generato la collisione
      p->collisioni.push_back(value);
      cout << "Esiste gia' un nodo con lo stesso id! Nodo inserito nella lista "
              "di collisioni del nodo con ID "
           << id << endl;
    }
  }
  insertfix(t);  // funzione per ripristinare le proprietà dell'albero RB
}
void RBtree::insertfix(node* z) {
  // controlliamo se il nodo inserito ha sia un padre che un nonno
  if (z->parent != NULL && z->parent->parent != NULL) {
    while (z != NULL && z->parent != NULL && z->parent->parent != NULL &&
           !(z->parent->getColor() == 'b'))

    {
      if (z->parent ==
          z->parent->parent
              ->left)  // controlliamo se il padre è figlio sinistro
      {
        node* y =
            z->parent->parent->right;  // se lo è allora y sarà lo zio di z
                                       // nonchè figlio destro del nonno di z
        if (y != NULL &&
            y->getColor() == 'r')  // se lo zio è rosso allora siamo nel caso 1
        {
          // padre e zio di z saranno di colore nero
          z->parent->setColor('b');
          y->setColor('b');
          // il nonno sarà rosso, così come lo stesso z
          z->parent->parent->setColor('r');
          z = z->parent->parent;           // z punterà al nonno
        } else if (z == z->parent->right)  // altrimenti se z è un figlio destro
                                           // lo faccio diventare figlio
                                           // sinistro per poi passare al caso 3
        {
          z = z->parent;
          leftrotate(z);
        }                                  // caso 3:
        z->parent->setColor('b');          // colore del padre sarà nero
        z->parent->parent->setColor('r');  // colore del nonno sarà rosso
        rightrotate(z->parent->parent);  // effettuo una rotazione verso destra
      } else  // zio è figlio sinistro, i passaggi sono gli stessi ma scambio le
              // rotazioni
      {
        node* y =
            z->parent->parent
                ->left;  // in questo caso y sarà figlio sinistro del padre
        if (y != NULL && y->getColor() == 'r')  // se lo zio di z è rosso
        {
          z->parent->setColor(
              'b');          // padre di z diventa nero, così come lo zio
          y->setColor('b');  //
          z->parent->parent->setColor('r');  // mentre il nonno diventa rosso
          z = z->parent->parent;
        } else {
          if (z ==
              z->parent->left)  // se z è un figlio sinistro siamo nel 3 caso
          {
            z = z->parent;
            rightrotate(z);
          }
          z->parent->setColor('b');          // padre di z avrà il colore nero
          z->parent->parent->setColor('r');  // nonno avrà il colore rosso
          leftrotate(z->parent->parent);  // verrà effettuata poi una rotazione
                                          // verso sinistra
        }
      }
    }
  }
}
void RBtree::del(int id, string value) {
  if (root == NULL) {
    cout << "\nAlbero vuoto.";
    return;
  }

  node* p;
  p = root;
  node* y = NULL;
  node* q = NULL;
  int found = 0;
  while (p != NULL && found == 0) {
    std::list<std::string>::iterator it;
    // vedo se l'elemento da eliminare è nella lista delle collisioni
    it = std::find(p->collisioni.begin(), p->collisioni.end(), value);

    if (it != p->collisioni.end()) {
      // se è presente lo elimino dalla lista
      p->collisioni.remove(value);
      cout << "Elemento rimosso con successo dalla lista di collisioni" << endl;
      return;
    }
    // ora controlliamo se troviamo l'elemento all'interno dell'albero
    if (p->getKey() == id)
      found = 1;
    if (found == 0) {
      if (p->getKey() < id)
        p = p->right;
      else
        p = p->left;
    }
  }
  if (found == 0) {  // caso in cui non lo troviamo
    cout << "\nElemento non trovato.";
    return;
  } else {
    // nel caso in cui troviamo ed eliminiamo il nodo stampiamo le sue
    // informazioni e fixiamo
    cout << "\nElemento rimosso: " << p->getKey() << endl;
    cout << "\nColore: ";
    if (p->getColor() == 'b')
      cout << "Nero\n";
    else
      cout << "Rosso\n";

    if (p->parent != NULL)
      cout << "\nPadre: " << p->parent->getKey();
    else
      cout << "\nIl nodo non ha un padre.  ";
    if (p->right != NULL)
      cout << "\nFiglio Destro: " << p->right->getKey();
    else
      cout << "\nIl nodo non ha un figlio destro  ";
    if (p->left != NULL)
      cout << "\nFiglio sinistro: " << p->left->getKey();
    else
      cout << "\nIl nodo non ha un figlio sinistro.  ";
    cout << "\nNodo rimosso." << endl;
    if (p->left == NULL || p->right == NULL)
      y = p;
    else
      y = successor(p);
    if (y->left != NULL)
      q = y->left;
    else {
      if (y->right != NULL)
        q = y->right;
      else
        q = NULL;
    }
    if (q != NULL)
      q->parent = y->parent;
    if (y->parent == NULL)
      root = q;
    else {
      if (y == y->parent->left)
        y->parent->left = q;
      else
        y->parent->right = q;
    }
    if (y != p) {
      p->setColor(y->getColor());
      p->setKey(y->getKey());
    }
    if (y->getColor() == 'b')
      delfix(q);
  }
}

void RBtree::delfix(node* p) {
  node* s;
  // la procedura avviene solo quando il nodo è di colore nero
  while (p != root &&
         p->getColor() ==
             'b')  // se il nodo non è la radice ed è di colore nero
  {
    if (p->parent->left == p)  // se p è un figlio sinistro
    {
      s = p->parent->right;  // s sarà suo fratello destro di colore nero
      if (s->getColor() == 'r') {
        s->setColor('b');
        p->parent->setColor('r');  // il padre deve essere rosso
        leftrotate(p->parent);     // ruoto così da passare al caso 2,3 o 4
        s = p->parent->right;
      }
      if (s->right->getColor() == 'b' &&
          s->left->getColor() ==
              'b')  // CASO 2 se i due fratelli hanno colore nero
                    // così come i figli di s (figlio destro)
      {
        s->setColor('r');  // s, il figlio destro, avrà colore rosso
        p = p->parent;
      } else {
        if (s->right->getColor() ==
            'b')  // nel caso 3 invece, s ha il figlio sinistro rosso ed il
                  // figlio destro nero
        {
          s->left->setColor('b');  // il figlio sinistro diventa nero
          s->setColor('r');        // mentre s diventa rosso
          rightrotate(s);  // ruoto così che passiamo dal caso 3 al caso 4
          s = p->parent->right;
        }
        // nel caso 4 s è nero ed ha il figlio destro rosso
        s->setColor(p->parent->getColor());
        p->parent->setColor('b');  // il padre di s,p sarà nero
        s->right->setColor('b');   // s sarà nero
        leftrotate(p->parent);
        p = root;
      }
    } else  // nel caso in cui s è un figlio sinitro il procedimento sarà lo
            // stesso ma vengono invertite le rotazioni
    {
      s = p->parent->left;
      if (s->getColor() == 'r') {
        s->setColor('b');
        p->parent->setColor('r');
        rightrotate(p->parent);
        s = p->parent->left;
      }
      if (s->left->getColor() == 'b' && s->right->getColor() == 'b') {
        s->setColor('r');
        p = p->parent;
      } else {
        if (s->left->getColor() == 'b') {
          s->right->setColor('b');
          s->setColor('r');
          leftrotate(s);
          s = p->parent->left;
        }
        s->setColor(p->parent->getColor());
        p->parent->setColor('b');
        s->left->setColor('b');
        rightrotate(p->parent);
        p = root;
      }
    }
    p->setColor('b');
    root->setColor('b');
  }
}

void RBtree::leftrotate(node* p) {
  if (p->right == NULL)
    return;
  else {
    node* y = p->right;  // calcoliamo il figlio destro di p
    if (y->left != NULL) {
      p->right = y->left;  // il figlio destro di p sarà il figlio sinistro del
                           // figlio di p ovvero di y
      y->left->parent = p;  // il padre del figlio sinistro di y sarà proprio p
    } else
      p->right = NULL;
    if (p->parent != NULL)    // se il padre di p non è nullo
      y->parent = p->parent;  // il padre di y sarà il padre di p
    if (p->parent ==
        NULL)  // se invece il padre di p è nullo y sarà la nuova radice
      root = y;
    else {
      if (p == p->parent->left)  // se p è un figlio sinistro
        p->parent->left = y;     // y diventerà il figlio sinistro
      else
        p->parent->right = y;  // se p è un figlio destro invece y lo sarà
    }
    y->left = p;    // il figlio sinistro di y sarà p
    p->parent = y;  // quindi il padre di p sarà y
  }
}
void RBtree::rightrotate(node* p) {
  if (p->left == NULL)
    return;
  else {
    node* y = p->left;
    if (y->right != NULL) {
      p->left = y->right;
      y->right->parent = p;
    } else
      p->left = NULL;
    if (p->parent != NULL)
      y->parent = p->parent;
    if (p->parent == NULL)
      root = y;
    else {
      if (p == p->parent->left)
        p->parent->left = y;
      else
        p->parent->right = y;
    }
    y->right = p;
    p->parent = y;
  }
}

node* RBtree::successor(node* p) {
  node* y = NULL;
  if (p->left != NULL) {
    y = p->left;
    while (y->right != NULL)
      y = y->right;
  } else {
    y = p->right;
    while (y->left != NULL)
      y = y->left;
  }
  return y;
}

void RBtree::disp() {
  display(root);
}
void RBtree::display(node* p) {
  if (root == NULL)  // se non c'è la radice significa che l'albero è vuoto
  {
    cout << "\nL'albero è vuoto.";
    return;
  }
  if (p != NULL) {
    cout << "\n\t NODO: ";
    cout << "\n Chiave: " << p->getKey();
    cout << "\n Valore: " << p->getValue();

    cout << "\n Colore: ";
    if (p->getColor() == 'b')
      cout << "Black";
    else
      cout << "Red";
    if (p->parent != NULL)
      cout << "\nPadre: " << p->parent->getKey();
    else
      cout << "\nIl nodo non ha un padre.  ";
    if (p->right != NULL)
      cout << "\nFiglio Destro: " << p->right->getKey();
    else
      cout << "\nIl nodo non ha un figlio destro  ";
    if (p->left != NULL)
      cout << "\nFiglio sinistro: " << p->left->getKey();
    else
      cout << "\nIl nodo non ha un figlio sinistro.  ";

    cout << "\n Lista collisioni: " << endl;

    for (auto const& i : p->collisioni) {
      std::cout << i << std::endl;
    }
    cout << endl;
    if (p->left) {
      display(p->left);
    }

    if (p->right) {
      display(p->right);
    }
  }
}
void RBtree::search(int id, string value) {
  if (root == NULL) {
    cout << "\nAlbero vuoto\n";
    return;
  }

  node* p = root;
  int found = 0;
  id = id % 100;
  while (p != NULL && found == 0)  // cerchiamo l'elemento non nullo
  {
    std::list<std::string>::iterator it;

    it = std::find(p->collisioni.begin(), p->collisioni.end(), value);
    // verifichiamo se l'elemento si trova nella lista di collisioni
    if (it != p->collisioni.end()) {
      cout << "\nL'elemento si trova nella lista di collisione dell'ID "
           << p->getKey() << endl;
      return;
    }
    if (p->getKey() == id)  // se troviamo l'elemento allora found=1
      found = 1;
    if (found == 0) {
      if (p->getKey() < id)
        p = p->right;
      else
        p = p->left;
    }
  }
  if (found == 0)
    cout << "\nElemento non trovato";
  else  // quindi se found=0 stampiamo le informazioni dell'elemento
  {
    cout << "\n\tNODO TROVATO: ";
    cout << "\n Chiave: " << p->getKey();
    cout << "\n Valore: " << p->getValue();
    cout << "\n Colore: ";
    if (p->getColor() == 'b')
      cout << "Nero";
    else
      cout << "Rosso";
    if (p->parent != NULL)
      cout << "\nPadre: " << p->parent->getKey();
    else
      cout << "\nIl nodo non ha un padre.  ";
    if (p->right != NULL)
      cout << "\nFiglio Destro: " << p->right->getKey();
    else
      cout << "\nIl nodo non ha un figlio destro  ";
    if (p->left != NULL)
      cout << "\nFiglio sinistro: " << p->left->getKey();
    else
      cout << "\nIl nodo non ha un figlio sinistro.  ";
    cout << endl;
  }
}