#pragma once
#include "Snake.hpp"

enum GameState {
	Running,
	GameOver
};

struct FoodPoint {
    int pointX;
    int pointY;
};

class Board {
public:
    Board(int x, int y, Snake &snake);
    void Draw();
    void CheckCollision();
    FoodPoint GenerateFood();
private:
    int sizeX,sizeY;
    Snake &snake;
public:
    GameState gamestate;
    FoodPoint food;
};
