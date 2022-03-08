#include <array>
#include <iostream>
#include <map>
using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::ostream;

enum class Op {
  Plus, Minus, Times, Divide
};

array<char, 4> optok = { '+', '-', '*', '/' };

ostream& operator <<(ostream& out, Op op) {
  return out << optok[(int)op];
}

struct Equation {
  array<int, 4> nums;
  array<Op, 3> ops;
  int size;
};

ostream& operator <<(ostream& out, const Equation& eq) {
  out << eq.nums[0];
  for (int i = 0; i < eq.size; ++i) {
    out << ' ' << eq.ops[i] << ' ' << eq.nums[i + 1];
  }
  return out;
}

int evalop(int lhs, Op op, int rhs) {
  switch (op) {
  case Op::Plus:   return lhs + rhs;
  case Op::Minus:  return lhs - rhs;
  case Op::Times:  return lhs * rhs;
  case Op::Divide: return lhs / rhs;
  }
  return 0;
}

void reduce(Equation& eq, int i) {
  eq.nums[i] = evalop(eq.nums[i], eq.ops[i], eq.nums[i + 1]);
  for (int j = i + 1; j < eq.size; ++j) {
    eq.nums[j] = eq.nums[j + 1];
    eq.ops[j - 1] = eq.ops[j];
  }
  --eq.size;
}

int eval(Equation eq) {
  for (int i = 0; i < eq.size;) {
    if (eq.ops[i] == Op::Times || eq.ops[i] == Op::Divide) {
      reduce(eq, i);
    }
    else {
      ++i;
    }
  }

  while (eq.size > 0) {
    reduce(eq, 0);
  }

  return eq.nums[0];
}

map<int, Equation> solutions;
void solve() {
  Equation eq;
  eq.nums = { 4, 4, 4, 4 };
  eq.size = 3;
  for (int i = 0; i < 64; ++i) {
    eq.ops[0] = Op(i / 16);
    eq.ops[1] = Op(i % 16 / 4);
    eq.ops[2] = Op(i % 4);
    solutions[eval(eq)] = eq;
  }
}

int main() {
  solve();
  int m;
  cin >> m;
  for (int i = 0; i < m; ++i) {
    int n;
    cin >> n;
    auto p = solutions.find(n);
    if (p == solutions.end()) {
      cout << "no solution" << endl;
    }
    else {
      cout << p->second << " = " << p->first << endl;
    }
  }
}