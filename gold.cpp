using ll = long long;

template <typename T, size_t _H> class SegmentTree {
public:
  struct Node {
    Node() {}
    Node(T v) : acc(v), total_m(v), lm(v), rm(v) {}
    Node operator+(const Node &in) {
      Node res;

      res.acc = acc + in.acc;
      res.lm = max(lm, acc + in.lm);
      res.rm = max(in.rm, in.acc + rm);
      res.total_m = max(rm + in.lm, max(total_m, in.total_m));

      return res;
    }

    T total_m = -1e15, lm = -1e15, rm = -1e15, acc = 0;
  };

  void Update(int i, const T &v) {
    for (i += INDEX_MAX - 1, nodes[i] = v, i >>= 1; i >= 1; i >>= 1)
      nodes[i] = nodes[i << 1] + nodes[(i << 1) + 1];
  }

  Node nodes[1 << _H];
  int INDEX_MAX = 1 << _H - 1;
};

vector<int> xs, ys;
inline int GetXI(int x) {
  return upper_bound(xs.begin(), xs.end(), x) - xs.begin();
}
inline int GetYI(int y) {
  return upper_bound(ys.begin(), ys.end(), y) - ys.begin();
}

struct P {
  int x, y, w;
} inputs[3001];
struct II {
  int x, w;
};
vector<II> board[3001];

SegmentTree<ll, 13> seg;

int main() {
  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    xs.push_back(x);
    ys.push_back(y);
    inputs[i] = {x, y, w};
  }

  sort(xs.begin(), xs.end());
  sort(ys.begin(), ys.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());
  for (int i = 1; i <= n; i++)
    board[GetYI(inputs[i].y)].push_back({GetXI(inputs[i].x), inputs[i].w});

  ll ans = -1e15;

  for (int i = 1; i <= ys.size(); i++) {
    fill(seg.nodes, seg.nodes + (1 << 13), SegmentTree<ll, 13>::Node());

    for (int j = i; j <= ys.size(); j++) {
      for (auto p : board[j])
        seg.Update(p.x, seg.nodes[p.x + seg.INDEX_MAX - 1].acc + p.w);

      ans = max(ans, seg.nodes[1].total_m);
    }
  }
  cout << ans;
}