#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>

#include "solver.h"

int main(int argc, char **argv) {
  Heuristic h = Heuristic::MANHATTAN;
  bool print_stat = false;

  for (int i = 1; i < argc; i++) {
    if (std::strcmp(argv[i], "-ham") == 0) {
      h = Heuristic::HAMMING;
    } else if (std::strcmp(argv[i], "-man") == 0) {
      h = Heuristic::MANHATTAN;
    } else if ((std::strcmp(argv[i], "-i") == 0) && i < (argc - 1)) {
      std::freopen(argv[i + 1], "r", stdin);
    } else if ((std::strcmp(argv[i], "-o") == 0) && i < (argc - 1)) {
      std::freopen(argv[i + 1], "w", stdout);
    } else if (std::strcmp(argv[i], "-stat") == 0) {
      print_stat = true;
    }
  }

  int n;
  std::cin >> n;

  std::vector<int> nums(n * n);

  for (int i = 0; i < n * n; i++) {
    std::cin >> nums[i];
  }

  Board start = Board(n, std::move(nums));
  Board end = Board::solved(n);

  int nodes_visited;
  auto res = solve(start, end, h, &nodes_visited);

  if (!res) {
    std::cout << "Unsolvable puzzle" << std::endl;
  } else {
    std::cout << "Minimum number of moves = " << res->size() - 1 << std::endl
              << std::endl;
    for (auto &board : *res) {
      board.print(std::cout);
      std::cout << std::endl;
    }
  }

  if(print_stat){
    std::cout << "(Visited " << nodes_visited << " nodes)" << std::endl;
  }
}
