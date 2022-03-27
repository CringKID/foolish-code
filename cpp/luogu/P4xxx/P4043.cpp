#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
const int kMaxN = 305, kMaxM = 55, kInf = 0x3f3f3f3f;
struct Edge {
	int x, val, to, nxt, op;
} edge[kMaxN * kMaxM * 2];
int n, m, s, t, le[kMaxN], tot, cnt, disum, ind[kMaxN], out[kMaxN], s1, s2, t1, t2, dis[kMaxN], lee[kMaxN], deg[kMaxN];
bool vis[kMaxN];
void add (int x, int y, int z, int w) {
	edge[++cnt] = {z, w, y, le[x], cnt + 1}; le[x] = cnt;
	edge[++cnt] = {0, -w, x, le[y], cnt - 1}; le[y] = cnt; 
}
bool SPFA () {
  fill (deg, deg + n + 1, 0x7f7f7f7f), fill (dis, dis + n + 1, 0x7f7f7f7f);
	memcpy (lee, le, sizeof (lee));
	deg[s] = 0; dis[s] = 0;
	queue <int> que; que.push (s); ind[s] = 1;
	while (!que.empty ()) {
		int now = que.front (); que.pop ();
		for (int i = le[now]; i; i = edge[i].nxt) {
			if (edge[i].x && dis[edge[i].to] > dis[now] + edge[i].val) {
				dis[edge[i].to] = dis[now] + edge[i].val; deg[edge[i].to] = deg[now] + 1;
				if (!ind[edge[i].to]) {
					ind[edge[i].to] = 1, que.push (edge[i].to);
				}
			}
    }
		ind[now] = 0;
	}
	return dis[t] != dis[0];
}
int DFS (int now, int sum) {
	if (now == t) {
    return sum;
  }
	int go = 0;
	for (int &i = lee[now]; i; i = edge[i].nxt) {
		if (edge[i].x && deg[edge[i].to] == deg[now] + 1 && dis[edge[i].to] == dis[now] + edge[i].val) {
			int this_go = DFS (edge[i].to, min (sum - go, edge[i].x));
			if (this_go) {
				edge[i].x -= this_go;
        edge[edge[i].op].x += this_go;
				go += this_go; 
        if (go == sum) {
          return go;
        }
			}
		}
  }
	if (go != sum) {
    dis[now] = -1;
  }
	return go;
}
int Dinic () {
	int re = 0;
	while (SPFA ()) {
		re += DFS (s, kInf) * dis[t];
  cout << "passed" << '\n';
  }
	return re;
}
int main () {
  cin >> n;
	tot = n; s1 = 1; t1 = ++tot; s2 = ++tot; t2 = ++tot;
	for (int i = 1, k, b, t; i <= n; i++) {
	  cin >> k;
		for (int j = 1; j <= k; j++) {
      cin >> b >> t;
			add (i, b, kInf, t);
			out[i]++; ind[b]++;
			disum += t;
		}
	}
	for (int i = 2; i <= n; i++) {
		add (i, t1, kInf, 0);
	}
	for (int i = 1; i <= n; i++) {
		if (ind[i] > out[i]) {
      add (s2, i, ind[i] - out[i], 0);
    }
		if (out[i] > ind[i]) {
      add (i, t2, out[i] - ind[i], 0);
    }
	}
	add (t1, s1, kInf, 0);
	s = s2; t = t2;
  cout << disum + Dinic () << '\n';
	return 0;
}