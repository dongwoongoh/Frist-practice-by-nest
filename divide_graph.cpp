#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> graph;
int visited[200001] = {};
int bipartite = 0;
int V, E;

void DFS(int node, int color) {
  visited[node] = color;

  for (int i = 0; i < graph[node].size(); i++) {
    int next = graph[node][i];

    if (visited[next] == 0) {
      int c = 0;
      if (color == 1)
        c = 2;
      else if (color == 2)
        c = 1;
      DFS(next, c);
    } else if (visited[next] == color) {
      bipartite = 1;
      return;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int K;
  cin >> K;

  for (int i = 0; i < K; i++) {
    cin >> V >> E;

    fill(visited, visited + 200001, 0);
    graph.assign(V + 1, vector<int>(0, 0));
    bipartite = 0;

    int e1 = 1, e2 = 1;
    for (int j = 0; j < E; j++) {
      cin >> e1 >> e2;
      graph[e1].push_back(e2);
      graph[e2].push_back(e1);
    }
    for (int i = 1; i <= V; i++) {
      if (visited[i] == 0) {
        DFS(i, 1);
      }
    }

    if (bipartite == 0)
      cout << "YES\n";
    else
      cout << "NO\n";
  }

  return 0;
}