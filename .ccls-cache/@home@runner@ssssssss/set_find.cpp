#include <bits/stdc++.h>
using namespace std;

int parent[1000001];

int find(int a) {
  if (parent[a] == a)
    return a;
  else
    return parent[a] = find(parent[a]);
}

void uni(int a, int b) {
  int aRoot = find(a);
  int bRoot = find(b);
  if (aRoot == bRoot)
    return;
  parent[aRoot] = bRoot;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  int c, a, b;

  for (int i = 0; i <= n; i++) {
    parent[i] = i;
  }

  while (m--) {
    cin >> c >> a >> b;
    if (c == 0) {
      uni(a, b);
    } else {
      if (find(a) == find(b)) {
        cout << "YES" << '\n';
      } else {
        cout << "NO" << '\n';
      }
    }
  }

  return 0;
}