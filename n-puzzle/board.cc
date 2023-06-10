#include "board.h"

#include <cassert>

Board::Board(int n) : N(n), nums_(N * N) {
  for (int i = 0; i < N * N; i++) {
    nums_[i] = i;
  }
  blank_pos_ = {.x = 0, .y = 0};
}

Board::Board(int n, std::vector<int> nums, Position blank_pos)
    : N(n), nums_(nums), blank_pos_(blank_pos) {
  assert(nums.size() == n * n);
}

Board::Board(int n, std::vector<int> nums) : N(n), nums_(nums) {
  assert(nums.size() == n * n);
  for (int i = 0; i < n * n; i++) {
    if (nums_[i] == 0) {
      blank_pos_ = {.x = i % n, .y = i / n};
      break;
    }
  }
}

Board Board::solved(int n) {
  std::vector<int> nums(n * n);
  for (int i = 0; i < n * n; i++) {
    nums[i] = (i + 1) % (n * n);
  }
  return Board(n, std::move(nums), {.x = n - 1, .y = n - 1});
}

std::optional<Board> Board::make_move(Move move) {
  Position new_pos = blank_pos_;

  switch (move) {
  case Move::UP:
    if (blank_pos_.y == 0) {
      return std::nullopt;
    }
    new_pos.y = blank_pos_.y - 1;
    break;
  case Move::DOWN:
    if (blank_pos_.y == (N - 1)) {
      return std::nullopt;
    }
    new_pos.y = blank_pos_.y + 1;
    break;
  case Move::LEFT:
    if (blank_pos_.x == 0) {
      return std::nullopt;
    }
    new_pos.x = blank_pos_.x - 1;
    break;
  case Move::RIGHT:
    if (blank_pos_.x == (N - 1)) {
      return std::nullopt;
    }
    new_pos.x = blank_pos_.x + 1;
    break;
  }

  int old_idx = blank_pos_.y * N + blank_pos_.x;
  int new_idx = new_pos.y * N + new_pos.x;

  auto new_nums = nums_;
  std::swap(new_nums[old_idx], new_nums[new_idx]);

  return Board(N, std::move(new_nums), new_pos);
}

int Board::hamming_dist(Board b2) const {
  assert(N == b2.N);

  int d = 0;
  for (int i = 0; i < N * N; i++) {
    /* ignore blank */
    if (nums_[i] != 0) {
      if (nums_[i] != b2.nums_[i]) {
        d++;
      }
    }
  }
  return d;
}

int Board::manhattan_dist(Board b2) const {
  assert(N == b2.N);

  int d = 0;

  std::vector<Position> pos1(N * N), pos2(N * N);

  for (int i = 0; i < N * N; i++) {
    pos1[nums_[i]] = Position{.x = i % N, .y = i / N};
    pos2[b2.nums_[i]] = Position{.x = i % N, .y = i / N};
  }

  for (int i = 1; i < N * N; i++) {
    d += Position::distance(pos1[i], pos2[i]);
  }

  return d;
}


int Board::count_inversion() {
  int inv = 0;

  for (int i = 0; i < N * N; i++) {
    for (int j = i + 1; j < N * N; j++) {
      if (nums_[i] != 0 && nums_[j] != 0) {
        if (nums_[i] > nums_[j]) {
          inv++;
        }
      }
    }
  }

  return inv;
}

void Board::print(std::ostream &os) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      os << nums_[i * N + j] << ' ';
    }
    os << std::endl;
  }
}
