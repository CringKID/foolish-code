#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

const int kMaxN = 100001;

struct V {
  int v;     // 值
  int t;     // 子树大小
  int w;     // 堆权
  int l, r;  // 左右儿子
} v[kMaxN];

int n, r, m, o, x, y;

void ReCalc(int x) {  // 重新计算节点
  if (x) {            // 只计算存在的及诶单
    v[x].t = v[v[x].l].t + v[v[x].r].t + 1;
  }
}

void LeftR(int &x) {
  int y = v[x].r;
  v[x].r = v[y].l;
  v[y].l = x;
  ReCalc(x);
  ReCalc(y);
  x = y;
}

void RightR(int &x) {
  int y = v[x].l;
  v[x].l = v[y].r;
  v[y].r = x;
  ReCalc(x);
  ReCalc(y);
  x = y;
}

void ReBalance(int &x) {
  if (v[x].l && v[v[x].l].w < v[x].w) {
    RightR(x);
  }
  if (v[x].r && v[v[x].r].w < v[x].w) {
    LeftR(x);
  }
}

void Insert(int &x) {  // 插入
  if (!x) {            // 遇到空节点
    x = ++m;           // 生成新节点
    v[x].v = y;        // 赋值
    v[x].w = rand();   // 随机化值
  } else {             // 根据大小插入到子树中
    int &c = y < v[x].v ? v[x].l : v[x].r;
    Insert(c);
  }
  ReCalc(x);
  ReBalance(x);
}

int Replace(int &x) {  // 左子树中寻找替换删除节点
  int t;
  if (!v[x].r) {          // 没有右儿子
    t = v[x].v;           // 记录值
    x = v[x].l + v[x].r;  // 删除当前节点
  } else {
    t = Replace(v[x].r);  // 到右子树中删除
  }
  ReCalc(x);
  return t;
}

void Delete(int &x) {  // 删除节点
  if (!x) {            // 没找到当前值
    return;
  }
  if (y == v[x].v) {           // 找到值
    if (!v[x].l || !v[x].r) {  // 最多有一个儿子
      x = v[x].l + v[x].r;     // 直接删除
    } else {
      v[x].v = Replace(v[x].l);  // 寻找替代节点
    }
  } else {
    int &c = y < v[x].v ? v[x].l : v[x].r;  // 到子树中删除
    Delete(c);
  }
  ReCalc(x);
}

int FindR(int x) {  // 查询比y小的数的个数
  if (!x) {         // 没有节点
    return 0;
  }
  if (v[x].v >= y) {  // 到左子树查
    return FindR(v[x].l);
  } else {  // 累加左子树与根，到右子树查
    return FindR(v[x].r) + v[v[x].l].t + 1;
  }
}

int FindV(int x, int y) {
  int t = v[v[x].l].t;
  if (y == t + 1) {  // 刚好等于根
    return v[x].v;
  } else if (y <= t) {  // 到左子树中查找
    return FindV(v[x].l, y);
  } else {  // 到右子树中 查找
    return FindV(v[x].r, y - t - 1);
  }
}

int FindP() {  // 寻找前驱
  int t = 1 << 31;
  for (int x = r; x;) {  // 从根开始寻找
    if (v[x].v < y) {    // 当前节点可以是前驱
      t = v[x].v;        // 记录
      x = v[x].r;        // 到右子树找
    } else {
      x = v[x].l;  // 到左子树找
    }
  }
  return t;
}

int FindS() {  // 寻找后继
  int t = ~(1 << 31);
  for (int x = r; x;) {  // 从根开始找
    if (v[x].v > y) {    // 当前节点可以是后继
      t = v[x].v;        // 记录
      x = v[x].l;        // 到左子树找
    } else {
      x = v[x].r;  // 到右子树找
    }
  }
  return t;
}

int main() {
  srand((unsigned)time(0));
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> o >> y;
    if (o == 1) {
      Insert(r);
    } else if (o == 2) { 
      Delete(r);
    } else if (o == 3) {
      cout << FindR(r) + 1 << endl;
    } else if (o == 4) {
      cout << FindV(r, y) << endl;
    } else if (o == 5) {
      cout << FindP() << endl;
    } else {
      cout << FindS() << endl;
    }
  }
  return 0;
}