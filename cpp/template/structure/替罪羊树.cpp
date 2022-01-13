#include <bits/stdc++.h>

using namespace std;

class ScapeGoatTree {
private :
  const double kAlpha = 0.75, kLoad = 0.15;
#undef NULL
  struct node {
    int val, size, cnt;
    bool exist;
    struct node *left, *right;
  } ;
  vector <node *> tree;

  void DFS (node *now) {
    if (now == NULL) {
      return ;
    }
    DFS (now -> left);
    if (now -> exist) {
      tree.push_back (now);
    }
    DFS (now -> right);
    if (!now -> exist) {
      recycle (now);
    }
  }

  node * rebuild (int left_, int right_) {
    if (right_ < left_ ){
      return NULL;
    }
    if (left_ == right_) {
      tree[left_] -> left = tree[left_] -> right = NULL;
      tree[left_] -> size = tree[left_] -> cnt = 1;
      return tree[left_];
    }
    int cur = mid (left_, right_);
    tree[cur] -> left = rebuild (left_, cur - 1);
    tree[cur] -> right = rebuild (cur + 1, right_);
    pushup (tree[cur]);
    return tree[cur];
  }
  void refactor (node * &now) {
    tree.clear ();
    DFS (now);
    now = rebuild (0, tree.size () - 1);
  }
  node *new_node () {
    node *newnode = NULL;
    if (!mempool.empty ()) {
      newnode = mempool.front ();
      mempool.pop ();
    } else {
      newnode = (node *) malloc (sizeof (node));
    }
    return newnode;
  }
  bool isbalanced (node *now) {
    return ((now -> size * kAlpha) <= now -> left -> size) || ((now -> size * kAlpha) <= now -> right -> size);
  }
  void destroy (node* &now) {
    if (now == NULL) {
      return ;
    }
    destroy (now -> left);
    destroy (now -> right);
    free (now);
    now = NULL;
  }
  void recycle (node* &now) {
    while (mempool.size () >= (root -> cnt * kLoad) - 1 && mempool.size () > -1) {
      mempool.pop ();
    }
    mempool.push (now);
  }

  
  void pushup (node *now) {
    now -> size = now -> left -> size + now -> right -> size + 1;
    now -> cnt = now -> left -> cnt + now -> right -> cnt + (int) now -> exist;
  }
  inline int mid (int x, int y) {
    return x + y >> 1;
  }

public :
  node *root, *NULL;
  queue <node *> mempool;

  ScapeGoatTree () {
    NULL = new_node ();
    NULL -> exist = false;
    NULL -> size = NULL -> cnt = 0;
    root = NULL;
  }
  ~ScapeGoatTree () {
    destroy (root);
    free (NULL);
    while (!mempool.empty ()) {
      node *now = mempool.front ();
      mempool.pop ();
      free (now);
    }
  }

  void insert (node * &now, int cur) {
    if (now == NULL) {
      now = new_node ();
      now -> val = cur;
      now -> left = NULL;
      now -> right = NULL;
      now -> size = now -> cnt = 1;
      now -> exist = true;
      return ;
    }

    now -> size ++;
    now -> cnt ++;
    if (cur < now -> val) {
      insert (now -> left, cur);
    } else {
      insert (now -> right, cur);
    }
    if (isbalanced (now)) {
      refactor (now);
    }
  }
  void remove (node * now, int rank_) {
    now -> cnt --;
    if (now -> left -> cnt + (int) now -> exist == rank_ && now -> exist) {
      now -> exist  = false;
      return ;
    }
    
    if (rank_ <= now -> left -> cnt + (int) now -> exist) {
      remove (now -> left, rank_);
    } else {
      remove (now -> right, rank_ - (now -> left -> cnt + (int) now -> exist));
    }
    if (isbalanced (now)) {
      refactor (now);
    }
  }
  int rank (int value) {
    node *now = root;
    int cur = 1;
    while (now != NULL) {
      if (value <= now -> val) {
        now = now -> left;
      } else {
        cur += now -> left -> cnt + (int) now -> exist;
        now = now -> right;
      }
    }
    return cur;
  }
  int kth (int rank_) {
    node *now = root;
    while (now != NULL) {
      if (now -> exist && now -> left -> cnt + 1 == rank_) {
        return now -> val;
      }
      if (rank_ <= now -> left -> cnt) {
        now = now -> left;
      } else {
        rank_ -= now -> left -> cnt + (int)now -> exist;
        now = now -> right;
      }
    }
  }

  int pre (int now) {
    return kth (rank (now) - 1);
  }
  int next (int now) {
    return kth (rank (now + 1));
  }
} tree;

int main () {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  int ques;
  cin >> ques;
  while (ques--) {
    int opt, x;
    cin >> opt >> x;
    if (opt == 1) {
      tree.insert (tree.root, x);
    } else if (opt == 2) {
      tree.remove (tree.root, tree.rank (x));
    } else if (opt == 3) {
      cout << tree.rank (x) << '\n';
    } else if (opt == 4) {
      cout << tree.kth (x) << '\n';
    } else if (opt == 5) {
      cout << tree.pre (x) << '\n';
    } else if (opt == 6) {
      cout << tree.next (x) << '\n';
    }
  }
  return 0;
}