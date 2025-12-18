#include <iostream>
#include <cctype>
#include"Player.hpp"
#include "Game.hpp"

Game::Game() {}

void Game::setup_players(){

    //Joueur 1
    std::cout<< "Joueur 1"<<std::endl;
    p1 = create_player();
    std::cout <<"Joueur 1 " <<p1.name<< " joue le " << p1.symbol <<std::endl;
    
    //Joueur 2
    std::cout<< "Joueur 2"<<std::endl;
    p2 = create_player();

    // si mm symbol pris
    while(p1.symbol==p2.symbol){
        std::cout << "[ERROR] Le symbole " << p1.symbol << " est deja pris par " << p1.name <<std::endl;
        std::cout << p2.name << ", choisissez un autre symbole : ";
        std::cin >> p2.symbol;
        p2.symbol = std::toupper(p2.symbol);
        }
    std::cout <<"Joueur 2 " <<p2.name<< " joue le " << p2.symbol <<std::endl;
    }

void Game::init_board() {
    char counter = '1';   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = counter;
            counter++; 
        }
    }
}

void Game::draw_game_board() const {
    std::cout <<std::endl;
    for (int i = 0; i < 3; i++) {
       
        std::cout << "|"; 
        for (int j = 0; j < 3; j++) {
            
            std::cout << " " << board[i][j] << " |";
        }
        
        std::cout <<std::endl;
    }
}

void Game::play_turn(Player& player) {
    int choix = 0;

    while (true) {
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
            break; 
        }
        }
    }      

    bool Game::check_win(char symbol) const {
    // on verifie si il y a un gagnant sur les lignes et colonnes
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
    }

    // sur les diagonales
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;

    return false;
}

void Game::run() {
    setup_players();
    init_board();
    
    std::cout << "DEBUT DE LA PARTIE !" << std::endl;
    draw_game_board();

    bool gagne = false;

    // Boucle max de 9 tours
    for (int i = 0; i < 9; i++) {
        
        // Si i est pair c'est le joueur 1
        if (i % 2 == 0) {
            play_turn(p1);
            if (check_win(p1.symbol)) {
                draw_game_board();
                std::cout << "Bravo " << p1.name << ", GAGNE la partie !" << std::endl;
                gagne = true;
                break;
            }
        } else {
            // Sinon c'est le joueur 2
            play_turn(p2);
            if (check_win(p2.symbol)) {
                draw_game_board();
                std::cout << "Bravo " << p2.name << ", GAGNE la partie !" << std::endl;
                gagne = true;
                break;
            }
        }
        
        draw_game_board();
    }

    if (!gagne) {
        std::cout << "Match Nul !" << std::endl;
    }
}