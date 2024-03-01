#include <algorithm>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
unordered_map<string, vector<int>> um;

void addCases(string *s, int score) {
  for (int i = 0; i < 16; i++) {
    string str = "";
    int num = i;
    for (int j = 3; j >= 0; j--) {
      if (num <= 0 || num % 2 == 0) {
        str = "-" + str;
      } else
        str = s[j] + str;
      num /= 2;
    }
    um[str].push_back(score);
  }
}
vector<int> solution(vector<string> info, vector<string> query) {
  vector<int> answer;
  string s[4], str = "";

  for (int i = 0; i < info.size(); i++) {
    istringstream stt(info[i]);
    stt >> s[0] >> s[1] >> s[2] >> s[3] >> str;
    addCases(s, (int)stoi(str));
  }

  for (auto itr = um.begin(); itr != um.end(); itr++) {
    sort(itr->second.begin(), itr->second.end());
  }

  for (int i = 0; i < query.size(); i++) {
    istringstream stt(query[i]);
    stt >> s[0] >> str >> s[1] >> str >> s[2] >> str >> s[3] >> str;
    int score = (int)stoi(str);

    vector<int> v = um[s[0] + s[1] + s[2] + s[3]];
    if (v.size() != 0) {
      int idx = lower_bound(v.begin(), v.end(), score) - v.begin();
      answer.push_back(v.size() - idx);
    } else
      answer.push_back(0);
  }
  return answer;
}