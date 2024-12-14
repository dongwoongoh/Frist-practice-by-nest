#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
int map[201][201];
vector<int> uni;

int Find(int parent) {
  if (parent == uni[parent])
    return parent;
  uni[parent] = Find(uni[parent]);
  return uni[parent];
}

void Union(int a, int b) {
  a = Find(a);
  b = Find(b);
  if (a < b)
    uni[b] = a;
  else
    uni[a] = b;
}

int main() {
  int n;
  cin >> n;
  int m;
  cin >> m;
  uni.resize(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    uni[i] = i;
    for (int j = 1; j <= n; j++) {
      cin >> map[i][j];
    }
  }

  vector<int> order;
  for (int i = 0; i < m; i++) {
    int x;
    cin >> x;
    order.push_back(x);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (map[i][j] && uni[i] != uni[j])
        Union(i, j);
    }
  }

  bool check = true;
  int cur = uni[order[0]];
  for (int i = 1; i < m; i++) {
    if (cur == uni[order[i]]) {
      if (i == m)
        check = true;
    } else {
      check = false;
      break;
    }
  }

  if (check)
    cout << "YES\n";
  else
    cout << "NO\n";
}