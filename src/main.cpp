#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include "Board.hpp"

void LoadBoardSize(int &width, int &height);

int main() {
    initscr();  // Initialize ncurses mode
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    int board_width, board_height;
    LoadBoardSize(board_width, board_height);

    Snake snek;
    Board a(board_width, board_height, snek);
    
    while (a.gamestate == Running) {
        clear();
        
        snek.Move();
        snek.ChangeDirection();
        a.CheckCollision();
        a.Draw();
        
        refresh();
        usleep(100000);
    }
    clear();
    refresh();
    mvprintw(0, 0, "GAME OVER!");
    mvprintw(1, 0, "Your score: %d", snek.positions.size());
    mvprintw(2, 0, "Press any key to exit...");
    refresh();
    getchar();
    endwin();
    return 0;
}

void LoadBoardSize(int &width, int &height) {
    std::ifstream file("board_size.txt");
    if (file.is_open()) {
        std::string line;
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            if (!(ss >> width >> height)) {
                std::cerr << "Warning: Incorrect format in board_size.txt. Loading default size (50x25)." << std::endl;
                width = 50;
                height = 25;
                getchar();
            }
        } else {
            std::cerr << "Warning: Empty file board_size.txt. Loading default size (50x25)." << std::endl;
            width = 50;
            height = 25;
            getchar();
        }
        file.close();
    } else {
        std::cerr << "Warning: Unable to open file board_size.txt. Loading default size (50x25)." << std::endl;
        width = 50;
        height = 25;
        getchar();
    }
}
