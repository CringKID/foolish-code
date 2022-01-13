#include <bits/stdc++.h>

using namespace std;

const int kMaxN = 1e3 + 5;

int ans[kMaxN], cnt, Size[kMaxN], n, m;
struct node {
  int r, c;
  node *Up, *Down, *Left, *Right;
} dance[kMaxN * kMaxN], row[kMaxN], col[kMaxN], head;

inline void init(int r, int c) {
  cnt = 0, head.r = r, head.c = c;
  head.Left = head.Right = head.Up = head.Down = &head;
  for (register int i = 0; i < c; i++) {
    col[i].r = r, col[i].c = i, col[i].Left = &head;
    col[i].Right = head.Right;
    col[i].Left->Right = col[i].Right->Left = &col[i];
    col[i].Up = col[i].Down = &col[i], Size[i] = 0;
  }
  for (register int i = r - 1; ~i; i--) {
    row[i].r = i, row[i].c = c;
    row[i].Up = &head, row[i].Down = head.Down;
    row[i].Up->Down = row[i].Down->Up = &row[i];
    row[i].Left = row[i].Right = &row[i];
  }
}
inline void AddNode(int r, int c) {
  node *Node = &dance[cnt++];
  Node->r = r, Node->c = c;
  Node->Right = &row[r];
  Node->Left = row[r].Left;
  Node->Right->Left = Node->Left->Right = Node;
  Node->Up = &col[c];
  Node->Down = col[c].Down;
  Node->Up->Down = Node->Down->Up = Node;
  Size[c]++;
}
inline void deleteLR(node *Node) {
  Node->Left->Right = Node->Right, Node->Right->Left = Node->Left;
}
inline void deleteUD(node *Node) {
  Node->Up->Down = Node->Down, Node->Down->Up = Node->Up;
}
inline void revertLR(node *Node) {
  Node->Left->Right = Node->Right->Left = Node;
}
inline void revertUD(node *Node) {
  Node->Up->Down = Node->Down->Up = Node;
}

inline void Remove(int c) {
  if (c == n) {
    return ;
  }
  deleteLR(&col[c]);
  node *R, *C;
  for (C = col[c].Down; C != (&col[c]); C = C->Down) {
    if (C->c == n) {
      continue;
    }
    for (R = C->Left; R != C; R = R->Left) {
      if (R->c == n) {
        continue;
      }
      Size[R->c]--;
      deleteUD(R);
    }
    deleteLR(C);
  }
}
inline void Replace(int c) {
  if (c == n) {
    return ;
  }
  node *R, *C;
  for (C = col[c].Up; C != (&col[c]); C = C->Up) {
    if (C->c == n) {
      continue;
    }
    revertLR(C);
    for (R = C->Right; R != C; R = R->Right) {
      if (R->c == n) {
        continue;
      }
      Size[R->c]++, revertUD(R);
    }
  }
  revertLR(&col[c]);
}

bool Dance(int k) {
  if (head.Left == (&head)) {
    for (int i = 0; i < k; i++) {
      cout << ans[i] << ' ';
    }
    return true;
  }

  int inf = (1 << 30), Next = -1;
  for (node *Node = head.Left; Node != (&head); Node = Node->Left) {
    if (Size[Node->c] < inf) {
      inf = Size[Node->c];
      Next = Node->c;
    }
  }

  Remove(Next);
  node *Node;
  for (Node = col[Next].Down; Node != (&col[Next]); Node = Node->Down) {
    node *Tmp;
    Node->Right->Left = Node;

    for (Tmp = Node->Left; Tmp != Node; Tmp = Tmp->Left) {
      Remove(Tmp->c);
    }
    Node->Right->Left = Node->Left;
    ans[k] = Node->r + 1;
    if (Dance(k + 1)) {
      return true;
    }

    Node->Left->Right = Node;
    for (Tmp = Node->Right; Tmp != Node; Tmp = Tmp->Right) {
      Replace(Tmp->c);
    }
    Node->Left->Right = Node->Right;
  }

  Replace(Next);
  return false;
}

int main() {
  ios :: sync_with_stdio (false);
  cin.tie (0), cout.tie (0);

  cin >> m >> n;
  init(m, n);
  for (int i = 0, X; i < m; i++)
    for (int j = 0; j < n; j++) {
      scanf("%d", &X);
      if (X == 1) {
        AddNode(i, j);
      }
    }
  if (!Dance(0)) {
    puts("No Solution!");
  }
  return 0;
}