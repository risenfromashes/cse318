#include "solver.h"
#include <cassert>
#include <memory>
#include <queue>

Node::Node(Board board, Node *prev) : board_(board), prev_(prev) {
  if (prev) {
    depth_ = prev->depth_ + 1;
  } else {
    depth_ = 0;
  }
}

std::optional<std::list<Board>> solve(Board start, Board target, Heuristic h) {

  assert(start.N == target.N);

  int N = start.N;

  int p1, p2;
  if (N % 2 == 0) {
    p1 = (start.count_inversion() % 2 + start.blank_pos().y % 2) % 2;
    p2 = (target.count_inversion() % 2 + target.blank_pos().y % 2) % 2;
  } else {
    p1 = start.count_inversion() % 2;
    p2 = target.count_inversion() % 2;
  }

  if (p1 != p2) {
    return std::nullopt;
  }

  auto heur = [h, &target](const Node *&n) {
    switch (h) {
    case Heuristic::HAMMING:
      return n->board().hamming_dist(target);
    case Heuristic::MANHATTAN:
      return n->board().manhattan_dist(target);
    }
  };
  auto comp = [&target, &heur](const Node *&n1, const Node *&n2) {
    int d1, d2;
    d1 = n1->depth() + heur(n1);
    d2 = n2->depth() + heur(n2);

    return d1 > d2;
  };

  std::list<Board> path;

  std::priority_queue<Node *, std::vector<Node *>, decltype(comp)> queue(comp);

  std::vector<Node *> nodes;

  auto enqueue = [&queue, &nodes](Node *top, Move move) {
    if (auto b = top->board().make_move(move)) {
      Node *n = new Node(*b, top);
      nodes.push_back(n);
      queue.push(n);
    }
  };

  Node *s = new Node(start), *l = nullptr;
  nodes.push_back(s);
  queue.push(s);


  for (;;) {
    auto top = queue.top();
    queue.pop();

    if (top->board() == target) {
      l = top;
      break;
    }

    enqueue(top, Move::DOWN);
    enqueue(top, Move::UP);
    enqueue(top, Move::LEFT);
    enqueue(top, Move::DOWN);
  }

  assert(l);
  Node* n = l;
  do {
    path.push_front(std::move(n->board()));
  }while(n != nullptr);
  
  for(auto& node : nodes){
    delete node;
  }

  return path;
}
