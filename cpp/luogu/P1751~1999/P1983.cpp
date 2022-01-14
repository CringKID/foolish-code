
scanf("%d %d", &n, &m);
for (int i = 0; i < m; i++) {
  memset(vis, false, sizeof(vis));
  scanf("%d", &s[i]);
  for (int j = 0; j < s[i]; j++) {
    scanf("%d", &road[i][j]);
    vis[road[i][j]] = true;
  }
  for (int j = road[i][0] + 1; j < road[i][s[i] - 1]; j++)
    if (vis[j] == false)
      for (int k = 0; k < s[i]; k++)
        if (!edge[j][road[i][k]]) {
          edge[j][road[i][k]] = true;
          indegree[road[i][k]]++;
        }
}
queue<int> q;
for (int i = 1; i <= n; i++)
  if (indegree[i] == 0) {
    q.push(i);
    level[i] = 1;
  }
while (!q.empty()) {
  int front = q.front();
  q.pop();
  for (int i = 1; i <= n; i++) {
    if (edge[front][i]) {
      indegree[i]--;
      level[i] = max(level[i], level[front] + 1);
      if (indegree[i] == 0) q.push(i);
    }
  }
}
int maax = -1;
for (int i = 1; i <= n; i++)
  if (level[i] > maax) maax = level[i];
printf("%d\n", maax);
return 0;
