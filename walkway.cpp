#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <vector>
#include <utility>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::move;
using std::priority_queue;
using std::vector;

struct Stone {
  double a, b;
  double area;
};

struct State {
  double end;
  double area;
};

bool operator <(State a, State b) {
  return a.area > b.area;
}

struct Problem {
  vector<Stone> stones;
  double start;
  double finish;
  map<double, double> minArea;
  priority_queue<State> states;

  Problem(vector<Stone> stones, double start, double finish)
    : stones{ move(stones) }, start{ start }, finish{ finish } {
  }

  void visit(double end, double area) {
    auto [p, inserted] = minArea.insert({ end, area });
    if (inserted) {
      states.push({ end, area });
    }
    else if (p->second > area) {
      p->second = area;
      states.push({ end, area });
    }
  }

  bool search() {
    minArea[start] = 0;
    states.push({ start, 0 });
    while (!states.empty()) {
      State current = states.top();
      states.pop();
      if (current.end == finish) {
        return true;
      }
      if (current.area != minArea[current.end]) {
        continue;
      }
      for (Stone stone : stones) {
        if (stone.a == current.end) {
          visit(stone.b, current.area + stone.area);
        }
        if (stone.b == current.end) {
          visit(stone.a, current.area + stone.area);
        }
      }
    }
    return false;
  }
};


int main() {
  cout << std::fixed << std::setprecision(2);
  int numstones;
  while (cin >> numstones && numstones > 0) {
    vector<Stone> stones;
    Stone stone;
    double h, start, finish;
    for (int i = 0; i < numstones; ++i) {
      cin >> stone.a >> stone.b >> h;
      stone.area = (stone.a + stone.b) / 2 * h;
      stones.push_back(stone);
    }
    cin >> start >> finish;

    Problem problem(move(stones), start, finish);
    if (problem.search()) {
      cout << problem.minArea[finish] * 0.02 << endl;
    }
    else {
      cout << "ERROR - No solution found" << endl;
    }
  }
}
