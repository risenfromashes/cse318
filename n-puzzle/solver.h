#include "board.h"

#include <list>

class Node {
public:
  Node(Board board, Node *prev = nullptr);

  /* getters */
  const Board &board() const { return board_; }
  Board &board() { return board_; }

  Node *prev() const { return prev_; }
  int depth() const { return depth_; }

private:
  Board board_;
  Node *prev_;
  int depth_;
};

enum class Heuristic { HAMMING, MANHATTAN };

/* returns the steps to solve the board, if solvable, null otherwise */
std::optional<std::list<Board>> solve(Board start, Board target,
                                      Heuristic h = Heuristic::MANHATTAN,
                                      int *explored_nodes = nullptr,
                                      int *expanded_nodes = nullptr);
