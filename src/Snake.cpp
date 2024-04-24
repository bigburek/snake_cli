#include "Snake.hpp"
#include <ncurses.h>

Snake::Snake() {
    positions.push_back({1, 1});
    direction = RIGHT;
}

void Snake::Move(){
    Position newHead = positions.front();

    switch(direction) {
        case(RIGHT):
            newHead.x++;
            break;
        case(LEFT):
            newHead.x--;
            break;
        case(UP):
            newHead.y--;
            break;
        case(DOWN):
            newHead.y++;
            break;
    }

    // Add the new head to the front of the snake
    positions.push_front(newHead);

    // Remove the tail to maintain the snake's length
    positions.pop_back();
}

void Snake::ChangeDirection() {
    char a = getch();
    int newDirection;
    switch (a) {
        case 'w':
            newDirection = UP;
            break;
        case 's':
            newDirection = DOWN;
            break;
        case 'a':
            newDirection = LEFT;
            break;
        case 'd':
            newDirection = RIGHT;
            break;
        default:
            return; //Do nothing for other keys
    }

    // New direction can't be the opposite of current direction otherwise the snake will collapse into itself
      if (newDirection == UP && direction != DOWN ||
        newDirection == DOWN && direction != UP ||
        newDirection == LEFT && direction != RIGHT ||
        newDirection == RIGHT && direction != LEFT) {
        direction = (SnakeDirection)newDirection;
    }
}

void Snake::IncreaseLength() {
    switch(direction) {
        case RIGHT:
            positions.push_back({positions.back().x - 1, positions.back().y});
            break;
        case LEFT:
            positions.push_back({positions.back().x + 1, positions.back().y});
            break;
        case UP:
            positions.push_back({positions.back().x, positions.back().y + 1});
            break;
        case DOWN:
            positions.push_back({positions.back().x, positions.back().y - 1});
            break;
    }
}