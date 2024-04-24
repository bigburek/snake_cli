#include "Board.hpp"
#include <iostream>
#include <ncurses.h>
#include <random>

Board::Board(int x, int y, Snake &snake) : sizeX(x), sizeY(y), snake(snake) {
    gamestate = Running;
    food = GenerateFood();
}

void Board::Draw() {
    //Draw board edges
    for (int i = 0; i < sizeX + 2; ++i) {
        mvprintw(0, i, "#");
        mvprintw(sizeY + 1, i, "#");
    }
    for (int i = 0; i < sizeY + 2; ++i) {
        mvprintw(i, 0, "#");
        mvprintw(i, sizeX + 1, "#");
    }

    // Draw the snake
    for (const auto &point : snake.positions) {
        mvprintw(point.y, point.x, "o");
    }

    //Draw the food
    mvprintw(food.pointY, food.pointX, "F");

    //Draw score
    mvprintw(sizeY + 2, 0, "Score: %d", snake.positions.size());
}

void Board::CheckCollision() {
	for(int i = 1; i < snake.positions.size(); i++) {
		if (snake.positions[0] == snake.positions[i]) {
			gamestate = GameOver;	
		}
	}
    if(snake.positions[0].x <= 0 || snake.positions[0].x >= sizeX + 1 || snake.positions[0].y <= 0 || snake.positions[0].y >= sizeY + 1) {
        gamestate = GameOver;
    }
    if(snake.positions[0].x == food.pointX && snake.positions[0].y == food.pointY) {
        snake.IncreaseLength();
        food = GenerateFood();
    }

}

FoodPoint Board::GenerateFood() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> disx(1, sizeX);
    std::uniform_int_distribution<> disy(1, sizeY);
    int foodx = disx(gen);
    int foody = disy(gen);
    FoodPoint fp;
    fp.pointX = foodx;
    fp.pointY = foody;
    return fp;
}
