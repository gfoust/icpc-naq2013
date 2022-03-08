#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <stdexcept>
#include <utility>
#include <set>
using namespace std;

struct DisjointSets {
  vector<int> heads;
  vector<int> ranks;

  void init(int size) {
    heads.resize(size);
    ranks.resize(size);
    for (int i = 0; i < size; ++i) {
      heads[i] = i;
      ranks[i] = 0;
    }
  }

  int head(int i) {
    if (heads[i] == i) {
      return i;
    }
    else {
      return heads[i] = head(heads[i]);
    }
  }

  void join(int i, int j) {
    i = head(i);
    j = head(j);
    if (ranks[i] > ranks[j]) {
      heads[j] = i;
    }
    else {
      heads[j] = i;
      if (ranks[i] == ranks[j]) {
        ++ranks[j];
      }
    }
  }

  set<int> sets() {
    set<int> results;
    for (int i = 0; i < heads.size(); ++i) {
      results.insert(head(i));
    }
    return results;
  }
};

struct Problem {
  int width = 0, height = 0, islandCount = 0, bridgeCount = 0;
  vector<string> map;
  vector<vector<int>> islands;
  DisjointSets bridges;

  void readMap() {
    string line;
    while (getline(cin, line) && line != "") {
      if (width == 0) {
        width = line.size();
      }
      else if (width != line.size()) {
        throw std::runtime_error("Line did not match line width");
      }
      map.push_back(move(line));
      line.clear();
    }
    height = map.size();
  }

  void countIslands() {
    islandCount = 0;
    for (int r = 0; r < height; ++r) {
      islands.push_back(vector<int>(width, -1));
      for (int c = 0; c < width; ++c) {
        if (map[r][c] == '#' || map[r][c] == 'X') {
          if (r > 0 && islands[r - 1][c] >= 0) {
            islands[r][c] = islands[r - 1][c];
          }
          else if (c > 0 && islands[r][c - 1] >= 0) {
            islands[r][c] = islands[r][c - 1];
          }
          else {
            islands[r][c] = islandCount++;
          }
        }
      }
    }
  }

  void countBridges() {
    bridgeCount = 0;
    bridges.init(islandCount);
    for (int r = 0; r < height; ++r) {
      for (int c = 0; c < width; ++c) {
        if (map[r][c] == 'X') {
          if (r < height - 1 && map[r + 1][c] == 'B') {
            traceBridge(r, c, true);
            ++bridgeCount;
          }
          if (c < width - 1 && map[r][c + 1] == 'B') {
            traceBridge(r, c, false);
            ++bridgeCount;
          }
        }
      }
    }
  }

  void traceBridge(int r, int c, bool vert) {
    int src = islands[r][c];
    if (vert) {
      do ++r; while (map[r][c] != 'X');
    }
    else {
      do ++c; while (map[r][c] != 'X');
    }
    bridges.join(src, islands[r][c]);
  }
};

int main() {
  int count = 1;
  while (!cin.eof()) {
    Problem prob;
    prob.readMap();
    prob.countIslands();
    prob.countBridges();
    if (count > 1) { cout << endl; }
    cout << "Map " << count++ << endl;
    cout << "islands: " << prob.islandCount << endl;
    cout << "bridges: " << prob.bridgeCount << endl;
    cout << "buses needed: " << prob.bridges.sets().size() << endl;
  }
}
