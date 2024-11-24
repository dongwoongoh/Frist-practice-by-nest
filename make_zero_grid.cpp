#include <bits/stdc++.h>

using namespace std;

const int MAX = 60;

const int NODE_MAX = 3001;
const int INF = 1e9;
int n, m, sum, res;
pair<int, int> arr[MAX][MAX];

int c[NODE_MAX][NODE_MAX], f[NODE_MAX][NODE_MAX], d[NODE_MAX];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
vector<int> adj[NODE_MAX];

void maxFlow(int start, int end) {
  while (1) {
    memset(d, -1, sizeof(d));
    queue<int> Q;
    Q.push(start);

    while (!Q.empty() && d[end] == -1) {
      int x = Q.front();
      Q.pop();

      for (auto nx : adj[x]) {
        if (d[nx] == -1 && c[x][nx] - f[x][nx] > 0) {
          Q.push(nx);
          d[nx] = x;
          if (nx == end)
            break;
        }
      }
    }

    if (d[end] == -1)
      break;
    int flow = INT_MAX;
    for (int i = end; i != start; i = d[i]) {
      flow = min(flow, c[d[i]][i] - f[d[i]][i]);
    }

    for (int i = end; i != start; i = d[i]) {
      f[d[i]][i] += flow;
      f[i][d[i]] -= flow;
    }

    res += flow;
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t;
  cin >> t;
  for (int T = 0; T < t; T++) {
    memset(c, 0, sizeof(c));
    memset(f, 0, sizeof(f));

    sum = 0, res = 0;
    for (int i = 0; i < NODE_MAX; i++)
      adj[i].clear();

    cin >> n >> m;

    int Node_num = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        int tmp;
        cin >> tmp;
        sum += tmp;

        arr[i][j].first = Node_num;
        arr[i][j].second = tmp;

        if ((i + j) % 2 == 0) {
          adj[0].push_back(Node_num);
          adj[Node_num].push_back(0);
          c[0][Node_num] = tmp;
        } else {
          adj[3000].push_back(Node_num);
          adj[Node_num].push_back(3000);
          c[Node_num][3000] = tmp;
        }

        Node_num++;
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {

        if ((i + j) % 2 == 0) {
          int now = arr[i][j].first;

          for (int k = 0; k < 4; k++) {

            int nx = i + dx[k];
            int ny = j + dy[k];

            if (nx <= 0 || nx > n || ny <= 0 || ny > m)
              continue;

            int next_node = arr[nx][ny].first;

            adj[now].push_back(next_node);
            adj[next_node].push_back(now);
            c[now][next_node] = INF;
          }
        }
      }
    }

    maxFlow(0, 3000);

    cout << sum - res << '\n';
  }

  return 0;
}