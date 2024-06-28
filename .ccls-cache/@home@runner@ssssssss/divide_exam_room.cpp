#include  <algorithm>
#include  <string>
#include  <vector>

#define  MAX 10010
using namespace std;

int Root, Divide_Cnt;
bool Can_Divide;
bool Is_Child[MAX];
int Left_Child[MAX];
int Right_Child[MAX];
vector<int> Num;

int Min(int A, int B) {
   return A < B ? A : B;
   
}

void Make_Binary_Tree(vector<vector<int>> Link) {
  fill(Left_Child, Left_Child + MAX, - 1);
  fill(Right_Child, Right_Child + MAX, - 1);
for
   (int i = 0; i < Link.size(); i++) {
    int Left = Link[i][0];
    int Right = Link[i][1];

    if
       (Left != - 1) {
        Left_Child[i] = Left;
        Is_Child[Left] = true;
      }
    if
       (Right != - 1) {
        Right_Child[i] = Right;
        Is_Child[Right] = true;
      }
  }

for
   (int i = 0; i < Num.size(); i++) {
    if
       (Is_Child[i] == false) {
        Root = i;
        break;
      }
  }
}

int Find_Case(int Cur, int L, int R, int Mid) {
  if
     (Cur + L + R <= Mid) return 1;
  if
     (Cur + L > Mid && Cur + R > Mid) return 2;
  if
     (Cur + L > Mid) return 3;
  if
     (Cur + R > Mid) return 4;
  return 5;
}

int DFS(int Cur, int Mid) {
  if
     (Cur == - 1) return 0;
  if
     (Num[Cur] > Mid) {
      Can_Divide = false;
      return - 1;
    }

  int LC = DFS(Left_Child[Cur], Mid);
  int RC = DFS(Right_Child[Cur], Mid);
  if
     (Can_Divide == false) return 0;

  int Case = Find_Case(Num[Cur], LC, RC, Mid);
  if
     (Case == 1) return Num[Cur] + LC + RC;
  else
     if  (Case == 2) {
      Divide_Cnt += 2;
      return Num[Cur];
    }
  else  if  (Case == 3) {
    Divide_Cnt += 1;
    return Num[Cur] + RC;
  }
  else  if  (Case == 4) {
    Divide_Cnt += 1;
    return Num[Cur] + LC;
  }
  else {
    Divide_Cnt += 1;
    return (Num[Cur] + Min(LC, RC));
  }
}

bool Search(int K, int Mid) {
  Divide_Cnt = 0;
  Can_Divide = true;
  DFS(Root, Mid);
  if
     (Divide_Cnt >= K) return false;
  if
     (Can_Divide == false) return false;
  return true;
}

int Binary_Search(int K) {
  int Result = 987654321;
  int Start = 1;
  int End = 10000 * 10000;

  while
     (Start <= End) {
      int Mid = (Start + End) / 2;
      if
         (Search(K, Mid) == true) {
          End = Mid - 1;
          Result = Min(Result, Mid);
        }
      else
         Start = Mid + 1;
    }
  return Result;
}

int solution(int k, vector<int> num, vector<vector<int>> links)  {
  int answer = 0;
  Num = num;
  Make_Binary_Tree(links);
  answer = Binary_Search(k);
  return answer;
}