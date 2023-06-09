#include "board.h"

#include <cassert>

Board::Board(int n) : N(n) {
  for (int i = 0; i < N * N; i++) {
    nums_[i] = i;
  }
}

Board::Board(int n, std::vector<int> nums, Position blank_pos)
    : N(n), nums_(nums), blank_pos_(blank_pos) {
  assert(nums.size() == n*n);
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

  return Board(N, new_nums, new_pos);
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

  std::vector<Position>  pos1(N*N), pos2(N*N);

  for (int i = 0; i < N * N; i++) {
    pos1[nums_[i]] = Position{.x = i % N, .y = i / N};
    pos2[b2.nums_[i]] = Position{.x = i % N, .y = i / N};
  }

  for (int i = 1; i < N * N; i++) {
    d += Position::distance(pos1[i], pos2[i]);
  }

  return d;
}

bool operator==(Board b1, Board b2) {
  assert(b1.N == b2.N);

  for (int i = 0; i < b1.N * b1.N; i++) {
    if (b1.nums_[i] != b2.nums_[i]) {
      return false;
    }
  }
  return true;
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
