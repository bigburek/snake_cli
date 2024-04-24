#pragma once
#include <deque>

//Snake position points
struct Position {
    int x,y;
friend bool operator==(const Position& first ,const Position& other) {
    return first.x == other.x && first.y == other.y; 
}
};

enum SnakeDirection{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    Snake();
    void Move();
    void ChangeDirection();
    void IncreaseLength();
public:
    std::deque<Position> positions;
    SnakeDirection direction;
    Position* head;
};
