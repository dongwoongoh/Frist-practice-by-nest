#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct TREE {
  int Idx;
  int x;
  int y;
  TREE *Left;
  TREE *Right;
};

bool Cmp(TREE A, TREE B) {
  if (A.y >= B.y) {
    if (A.y == B.y) {
      if (A.x < B.x) {
        return true;
      }
      return false;
    }
    return true;
  }
  return false;
}

void Make_Binary_Tree(TREE *Root, TREE *Child) {
  if (Root->x > Child->x) {
    if (Root->Left == NULL) {
      Root->Left = Child;
      return;
    }
    Make_Binary_Tree(Root->Left, Child);
  } else {
    if (Root->Right == NULL) {
      Root->Right = Child;
      return;
    }
    Make_Binary_Tree(Root->Right, Child);
  }
}

void PreOrder(TREE *Root, vector<int> &answer) {
  if (Root == NULL)
    return;
  answer.push_back(Root->Idx);
  PreOrder(Root->Left, answer);
  PreOrder(Root->Right, answer);
}

void PostOrder(TREE *Root, vector<int> &answer) {
  if (Root == NULL)
    return;
  PostOrder(Root->Left, answer);
  PostOrder(Root->Right, answer);
  answer.push_back(Root->Idx);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
  vector<vector<int>> answer;
  vector<TREE> Tree;
  for (int i = 0; i < nodeinfo.size(); i++) {
    int x = nodeinfo[i][0];
    int y = nodeinfo[i][1];
    int Idx = i + 1;
    Tree.push_back({Idx, x, y, NULL, NULL});
  }
  sort(Tree.begin(), Tree.end(), Cmp);
  TREE *Root = &Tree[0];
  for (int i = 1; i < Tree.size(); i++)
    Make_Binary_Tree(Root, &Tree[i]);
  vector<int> Pre_V;
  PreOrder(Root, Pre_V);
  vector<int> Post_V;
  PostOrder(Root, Post_V);
  answer.push_back(Pre_V);
  answer.push_back(Post_V);
  return answer;
}
