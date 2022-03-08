#include <iostream>
#include <cstdint>
#include <map>
#include <queue>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::uint64_t;

//------------------------------
// A position in the grid
struct Pos {
  int row, col;
};

bool operator !=(const Pos& a, const Pos& b) {
  return a.row != b.row || a.col != b.col;
}

//------------------------------
// A direction to move
enum class Dir {
  Up,
  Down,
  Left,
  Right
};

Pos& operator+=(Pos& pos, Dir dir) {
  switch (dir) {
  case Dir::Up:    --pos.row; break;
  case Dir::Down:  ++pos.row; break;
  case Dir::Left:  --pos.col; break;
  case Dir::Right: ++pos.col; break;
  }
  return pos;
}

Pos operator +(Pos pos, Dir dir) {
  switch (dir) {
  case Dir::Up:    return { pos.row - 1, pos.col };
  case Dir::Down:  return { pos.row + 1, pos.col };
  case Dir::Left:  return { pos.row, pos.col - 1 };
  case Dir::Right: return { pos.row, pos.col + 1 };
  }
  return pos;
}

//------------------------------
// A 64-bit int as a 7x7 bit array
struct Grid {
  uint64_t data;

  Grid(uint64_t data = 0) : data{ data } {
  }

  bool operator[](Pos pos) const {
    return data & 1ull << (pos.row * 7ull + pos.col);
  }

  void set(Pos pos, bool val) {
    if (val) {
      data |= 1ull << (pos.row * 7ull + pos.col);
    }
    else {
      data &= ~(1ull << (pos.row * 7ull + pos.col));
    }
  }
};

ostream& operator<<(ostream& out, const Grid& grid) {
  for (int r = 0; r < 7; ++r) {
    for (int c = 0; c < 7; ++c) {
      out << (grid[{r, c}] ? 'X' : '.');
    }
    out << endl;
  }
  return out;
}

bool operator<(const Grid& lhs, const Grid& rhs) {
  return lhs.data < rhs.data;
}

bool inBounds(Pos pos) {
  return pos.row >= 0 && pos.row < 7 && pos.col >= 0 && pos.col < 7;
}

//------------------------------
// Shift bits over to the beginning of the row/col
Grid shift(Grid grid, Pos src_begin, Pos src_end, Pos dst_begin, Dir dir) {
  Pos dst = dst_begin;
  Pos src = src_begin;
  while (src != src_end) {
    grid.set(src, false);
    grid.set(dst, true);

    src += dir;
    dst += dir;
  }
  return grid;
}


std::queue<Grid> grids;
std::map<Grid, int> distances;

//------------------------------
// Try to find moves that would have started at pos moving in dir
// starting at grid with distance dist
void try_move(Grid grid, Pos pos, Dir dir, int dist) {
  if (grid[pos]) return;

  Pos start = pos + dir;
  while (inBounds(start) && !grid[start]) {
    start += dir;
  }

  Pos end = start + dir;
  while (inBounds(end) && grid[end]) {
    Grid next = shift(grid, start, end, pos, dir);
    //cerr << next << endl;
    auto& old_d = distances[next];
    if (old_d == 0 || old_d > dist + 1) {
      old_d = dist + 1;
      grids.push(next);
    }
    end += dir;
  }
}

// Try to find all possible moves that would result in grid
void search(Grid grid) {
  //cerr << grid << endl;
  grids.push(grid);
  while (!grids.empty()) {
    grid = grids.front();
    grids.pop();
    for (int i = 0; i < 7; ++i) {
      int dist = distances[grid];
      try_move(grid, { 0, i }, Dir::Down, dist);
      try_move(grid, { 6, i }, Dir::Up, dist);
      try_move(grid, { i, 0 }, Dir::Right, dist);
      try_move(grid, { i, 6 }, Dir::Left, dist);
    }
  }
  //cerr << distance.size() << endl;
}

// Find all solutions
void find_solutions() {
  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 5; ++c) {
      Grid grid;
      for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
          grid.set({r + i, c + j}, true);
        }
      }
      search(grid);
    }
  }
}

int main() {
  find_solutions();
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    Grid grid;
    for (int r = 0; r < 7; ++r) {
      for (int c = 0; c < 7; ++c) {
        char cell;
        cin >> cell;
        if (cell == 'X') {
          grid.set({ r, c }, true);
        }
      }
    }
    auto p = distances.find(grid);
    if (p == distances.end()) {
      cout << -1 << endl;
    }
    else {
      cout << p->second << endl;
    }
  }
}
