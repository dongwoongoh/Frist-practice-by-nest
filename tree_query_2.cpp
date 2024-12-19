#include <bits/stdc++.h>
using namespace std;
const int INF = 2e9;
const int inf = 1e9;

int parent[100001][18];
int depth[100001];
bool visited[100001];
long long dist[100001];
vector<pair<int, int>> adj[100001];

void go(int node) {
  visited[node] = true;
  for (int i = 0; i < adj[node].size(); i++) {
    int next = adj[node][i].first;
    if (visited[next])
      continue;
    parent[next][0] = node;
    depth[next] = depth[node] + 1;
    dist[next] = dist[node] + adj[node][i].second;
    go(next);
  }
}

int lca(int a, int b) {
  if (depth[a] < depth[b])
    swap(a, b);
  int diff = depth[a] - depth[b];
  for (int i = 0; i < 18; i++) {
    if (diff & 1 << i) {
      diff -= 1 << i;
      a = parent[a][i];
    }
  }
  if (a != b) {
    for (int i = 17; i >= 0; i--) {
      if (parent[a][i] != -1 && parent[a][i] != parent[b][i]) {
        a = parent[a][i];
        b = parent[b][i];
      }
    }
    a = parent[a][0];
  }
  return a;
}

int main(void) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    adj[a].push_back({b, c});
    adj[b].push_back({a, c});
  }
  go(1);
  for (int i = 1; i < 18; i++) {
    for (int j = 2; j <= n; j++) {
      parent[j][i] = parent[parent[j][i - 1]][i - 1];
    }
  }
  int m;
  cin >> m;
  while (m--) {
    int a, u, v, k;
    cin >> a;
    if (a == 1) {
      cin >> u >> v;
      int root = lca(u, v);
      cout << dist[u] + dist[v] - 2 * dist[root] << '\n';
    } else {
      cin >> u >> v >> k;
      int root = lca(u, v);
      int cnt = depth[u] - depth[root] + 1;
      if (cnt == k)
        cout << root << '\n';
      else if (cnt > k) {
        k--;
        int tmp = u;
        for (int i = 0; i < 18; i++) {
          if (k & 1 << i) {
            k -= 1 << i;
            tmp = parent[tmp][i];
          }
        }
        cout << tmp << '\n';
      } else {
        k = cnt + depth[v] - depth[root] - k + 1;
        k--;
        int tmp = v;
        for (int i = 0; i < 18; i++) {
          if (k & 1 << i) {
            k -= 1 << i;
            tmp = parent[tmp][i];
          }
        }
        cout << tmp << '\n';
      }
    }
  }
  return 0;
}