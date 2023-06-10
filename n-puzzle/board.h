#include <cmath>
#include <optional>
#include <vector>
#include <iostream>

struct Position {
  int x, y;

  /* taxicab distance */
  static int distance(Position p1, Position p2) {
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
  }
};

enum class Move { UP, DOWN, LEFT, RIGHT };

class Board {

public:
  /* default state of board */
  Board(int n);
  /* set board config manually */
  Board(int n, std::vector<int> nums);
  Board(int n, std::vector<int> nums, Position blank_pos);

  static Board solved(int n);

  /* counts inversions of permutation in row major order */
  int count_inversion();

  /* makes respective move and returns new board state if possible */
  std::optional<Board> make_move(Move move);

  /* calculate hamming distance */
  int hamming_dist(Board b2) const;

  /* calculate manhattan distance */
  int manhattan_dist(Board b2) const;

  /* test equality */
  friend bool operator==(const Board& b1, const Board& b2) {
    return b1.nums_ == b2.nums_;
  }

  friend auto operator<=>(const Board& b1, const Board& b2) {
    return b1.nums_ <=> b2.nums_;
  }

  /* return the position of the blank square */
  Position blank_pos() { return blank_pos_; }

  /* print to file */
  void print(std::ostream& os = std::cout);

  const int N;

private:
  /* stores the numbers in row major order */
  std::vector<int> nums_;
  Position blank_pos_;
};