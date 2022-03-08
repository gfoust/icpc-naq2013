#include <algorithm>
#include <iostream>
#include <map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::set;

struct Pos {
  int row, col;
};

bool operator <(Pos a, Pos b) {
  return a.row < b.row || a.row == b.row && a.col < b.col;
}

int shortest() {
  map<Pos, int> distances;
  map<Pos, set<Pos>> paths;
  int s;
  cin >> s;
  Pos pos = { 0, 0 };
  distances[pos] = 0;
  for (int i = 0; i < s; ++i) {
    Pos next = pos;
    char step;
    cin >> step;
    switch (step) {
    case 'N': --next.row; break;
    case 'S': ++next.row; break;
    case 'E': ++next.col; break;
    case 'W': --next.col; break;
    }
    paths[pos].insert(next);
    paths[next].insert(pos);

    pos = next;
    auto [p, inserted] = distances.insert({ pos, 1000 });
    int& best = p->second;
    for (auto next : paths[pos]) {
      best = std::min(best, distances[next] + 1);
    }
  }
  return distances[pos];
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cout << shortest() << endl;
  }
}