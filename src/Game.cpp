#include <iostream>
#include <cctype>
#include <random>
#include <vector>
#include"Player.hpp"
#include "Game.hpp"

Game::Game() {}

void Game::setup_players(){

    // Menu
    std::cout << "   MORPION    " << std::endl;
    std::cout << "1. Joueur vs Joueur" << std::endl;
    std::cout << "2. Joueur vs Ordi" << std::endl;
    std::cout << "Choix : ";
    
    int choix = 0;
    std::cin >> choix;

    // On regarde le choix du joueur
    if (choix == 2) {
        mode_ia = true;
    } else {
        mode_ia = false;
    }
    std::cout << std::endl;

    //Joueur 1
    std::cout<< "Joueur 1"<<std::endl;
    p1 = create_player();
    std::cout <<"Joueur 1 " <<p1.name<< " joue le " << p1.symbol <<std::endl;
    
    //Joueur 2
    std::cout<< "Joueur 2"<<std::endl;
    if (mode_ia == true) {
        // choix ordi
        p2.name = "Ordi";
        
        // Il prend l'autre symbole'
        if (p1.symbol == 'X') {
            p2.symbol = 'O';
        } else {
            p2.symbol = 'X';
        }
        std::cout << "L'ordi joue avec " << p2.symbol << std::endl;

        } else {
        // Si humain, on demande ses infos
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
        std::cout << std::endl;
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


void Game::play_ai_turn() {
    std::cout << "Tour de l'ordi..." << std::endl;

    // Cherche les cases vides
    std::vector<int> cases_vides;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Si c'est pas un symbole X ou O, c'est libre
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                // On garde le numero de la case 
                int numero = i * 3 + j;
                cases_vides.push_back(numero);
            }
        }
    }

    // on en choisit une au hasard
    if (cases_vides.size() > 0) {
        // random
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, cases_vides.size() - 1);

        int random_number = distrib(gen);
        int case_choisie = cases_vides[random_number];

        // on remet en ligne/colonne
        int ligne = case_choisie / 3;
        int col = case_choisie % 3;

        board[ligne][col] = p2.symbol;
        std::cout << "L'ordi a joue en case " << (case_choisie + 1) << std::endl;
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
            // Sinon c'est le joueur 2 ou IA

            if (mode_ia == true) {
                play_ai_turn();
            } else {
                play_turn(p2);
            }
            
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