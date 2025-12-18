#include "Game.hpp"
#include <iostream>


void init_board(Board& board) {
    char counter = '1';   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = counter;
            counter++; 
        }
    }
}

void draw_game_board(const Board& board) {
    std::cout <<std::endl;
    for (int i = 0; i < 3; i++) {
       
        std::cout << "|"; 
        for (int j = 0; j < 3; j++) {
            
            std::cout << " " << board[i][j] << " |";
        }
        
        std::cout <<std::endl;
    }
}