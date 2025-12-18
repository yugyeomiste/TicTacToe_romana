#include "Game.hpp"
#include <iostream>
#include"Player.hpp"



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

void play_turn(Board& board, const Player& player) {
    int choix = 0;
    bool coupValide = false;

    while (!coupValide) {
        std::cout << player.name << ", choisis une case (1-9) : ";
        std::cin >> choix;

        // Entre 1 et 9
        if (choix < 1 || choix > 9) {
            std::cout << "[ERREUR] Le chiffre doit etre entre 1 et 9 !" << std::endl;
            continue; 
        }

        // Enleve 1 car tableau commence a 0
        int index = choix - 1; 
        int ligne = index / 3; 
        int col = index % 3;   

        // Case indispo
        if (board[ligne][col] == 'X' || board[ligne][col] == 'O') {
            std::cout << "[ERREUR] La case est deja prise !" << std::endl;
        } else {
            
            board[ligne][col] = player.symbol;
            coupValide = true; 
        }
    }
}
