// 湖南师范大学附属中学 | 狂狼电竞俱乐部
#include <iostream>
#include <vector>

using namespace std;

const int kMaxL = 20, kMaxN = 1e5 + 1;

struct V {          // 点
  int f[kMaxL], d;  // 二次祖先、深度
  vector<int> e;    // 邻点
} v[kMaxN];

int n, m, s, x1, y1, z1, x2, y2, z2;

void Walk(int f, int x) {                // 当前点x，父亲f
  v[x].f[0] = f, v[x].d = v[f].d + 1;    // 记录父亲与深度
  for (int i = 0; i < kMaxL - 1; i++) {  // 计算节点的所有2次祖先
    v[x].f[i + 1] = v[v[x].f[i]].f[i];   // 2^i次祖先的2^i次祖先
  }
  for (int i : v[x].e) {  // 遍历邻点
    if (i != f) {         // 不重复访问父亲
      Walk(x, i);         // 遍历子树
    }
  }
}

int Lca(int x, int y) {
  if (v[x].d > v[y].d) {  // 令x为较浅的节点
    swap(x, y);
  }
  for (int i = 0; i < kMaxL; i++) {    // 将两点移动到同一高度
    if ((v[y].d - v[x].d) >> i & 1) {  // 当前距离应该移动
      y = v[y].f[i];                   // 移动到父亲
    }
  }
  for (int i = kMaxL - 1; i >= 0; i--) {  // 将两点移动到最远的非公共祖先
    if (v[y].f[i] != v[x].f[i]) {         // 不会移动到公共祖先
      x = v[x].f[i], y = v[y].f[i];
    }
  }
  return x == y ? x : v[x].f[0];
}

int main() {
  scanf("%d %d", &n, &m);
  for (int i = 1; i < n; i++) {  // 构造边
    cin >> x1 >> y1;
    v[x1].e.push_back(y1), v[y1].e.push_back(x1);
  }

  Walk(0, 1);

  for (int i = 1; i <= m; i++) {  // 读入查询
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    z1 = Lca(x1, y1), z2 = Lca(x2, y2);
    cout << ((Lca(x2, z1) == z1 || Lca(y2, z1) == z1) && (Lca(x1, z2) == z2 || Lca(y1, z2) == z2) ? 'Y' : 'N') << '\n';
  }
  return 0;
}