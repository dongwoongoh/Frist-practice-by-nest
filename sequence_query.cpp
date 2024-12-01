#include <algorithm>
#include <bitset>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <queue>
#include <set>
#include <stack>
#include <string.h>
#include <string>
#include <vector>
#define all(v) v.begin(), v.end()
#define pii pair<int, int>
#define make_unique(v) v.erase(unique(v.begin(), v.end()), v.end())
typedef long long ll;
using namespace std;

int n, m;
vector<ll> arr, tree, mulLazy, addLazy;
int MOD = 1000000007;

ll init(int i, int l, int r) {
  if (l == r)
    return tree[i] = arr[l];
  int m = (l + r) / 2;
  return tree[i] = (init(2 * i, l, m) + init(2 * i + 1, m + 1, r)) % MOD;
}

void update_lazy(int i, int l, int r) {
  if (addLazy[i] == 0 && mulLazy[i] == 1)
    return;
  if (l != r) {
    for (int j = 2 * i; j <= 2 * i + 1; j++) {
      addLazy[j] = ((addLazy[j] * mulLazy[i]) % MOD + addLazy[i]) % MOD;
      mulLazy[j] = mulLazy[j] * mulLazy[i] % MOD;
    }
  }
  tree[i] =
      ((mulLazy[i] * tree[i]) % MOD + ((r - l + 1) * addLazy[i]) % MOD) % MOD;
  addLazy[i] = 0;
  mulLazy[i] = 1;
  return;
}

void update_range(int i, int l, int r, int L, int R, ll mul, ll add) {
  update_lazy(i, l, r);
  if (r < L || R < l)
    return;
  if (L <= l && r <= R) {
    addLazy[i] = ((addLazy[i] * mul % MOD) + add) % MOD;
    mulLazy[i] = mulLazy[i] * mul % MOD;
    update_lazy(i, l, r);
    return;
  }
  int m = (l + r) / 2;
  update_range(2 * i, l, m, L, R, mul, add);
  update_range(2 * i + 1, m + 1, r, L, R, mul, add);
  tree[i] = (tree[2 * i] + tree[2 * i + 1]) % MOD;
  return;
}

ll query(int i, int l, int r, int L, int R) {
  update_lazy(i, l, r);
  if (r < L || R < l)
    return 0;
  if (L <= l && r <= R)
    return tree[i] % MOD;
  int m = (l + r) / 2;
  return (query(2 * i, l, m, L, R) + query(2 * i + 1, m + 1, r, L, R)) % MOD;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  arr.resize(n);
  tree.resize(4 * n);
  mulLazy.resize(4 * n, 1);
  addLazy.resize(4 * n, 0);
  for (int i = 0; i < n; i++)
    cin >> arr[i];
  init(1, 0, n - 1);
  cin >> m;
  int order, L, R;
  ll val;
  for (int i = 0; i < m; i++) {
    cin >> order;
    if (order == 1) {
      cin >> L >> R >> val;
      update_range(1, 0, n - 1, L - 1, R - 1, 1, val);
    } else if (order == 2) {
      cin >> L >> R >> val;
      update_range(1, 0, n - 1, L - 1, R - 1, val, 0);
    } else if (order == 3) {
      cin >> L >> R >> val;
      update_range(1, 0, n - 1, L - 1, R - 1, 0, val);
    } else {
      cin >> L >> R;
      cout << query(1, 0, n - 1, L - 1, R - 1) << '\n';
    }
  }
  return 0;
}