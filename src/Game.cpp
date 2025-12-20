#include <iostream>
#include <cctype>
#include <random>
#include <vector>
#include <limits>
#include"Player.hpp"
#include "Game.hpp"
#include <terminal_ctrl.hpp>

Game::Game() {}

void Game::erase_terminal() const {
    terminal_ctrl::clear_screen();
    terminal_ctrl::set_cursor_position(1, 3);
}

void Game::setup_players(){
    erase_terminal();

    // Menu
    std::cout << "   JEU DU MORPION    " << std::endl;
    std::cout << "1. Joueur vs Joueur" << std::endl;
    std::cout << "2. Joueur vs IA" << std::endl;
    
    int choix = 0;

    while (true) {
        std::cout << "Choix : ";
        if (std::cin >> choix) {
            // Verif si nombre 1 ou 2
            if (choix == 1 || choix == 2) {
                break; 
            } else {
                std::cout << "ERROR : Tapez 1 ou 2." << std::endl;
            }
        } else {
            // si l'utilisateur tape autre chose
            std::cout << "ERROR : Choisir 1 ou 2 !" << std::endl;
            std::cin.clear(); // on répare cin
            std::cin.ignore(1000, '\n'); // on vide la mauvaise saisie
        }
    }

    // On regarde le choix du joueur
    mode_ia = (choix == 2);
    
    std::cout << std::endl;

    //Joueur 1
    std::cout<< "Joueur 1"<<std::endl;
    p1 = create_player();
    std::cout <<"Joueur 1 " <<p1.name<< " joue le " << p1.symbol <<std::endl;
    
    //Joueur 2
    std::cout<< "Joueur 2"<<std::endl;

    if (mode_ia) {
        // choix IA
        p2.name = "IA";
        
        // Il prend l'autre symbole'
        if (p1.symbol == 'X') {
            p2.symbol = 'O';
        } else {
            p2.symbol = 'X';
        }


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

       if (!(std::cin >> choix)) {
            // si le joueur tape une lettre
            std::cout << "Choisir une case (1-9) !" << std::endl;
            std::cin.clear(); // On répare
            std::cin.ignore(1000, '\n'); 
            continue; 
        }

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
            info_case = player.name + " a joué en case " + std::to_string(choix);
            break; 
        }
        }
    }      
int Game::blocking_ia(char symbol) const {
    
    // verif lignes
    for (int i = 0; i < 3; i++) {
        int compteur = 0;
        int index_vide = -1; 

        for (int j = 0; j < 3; j++) {
            if (board[i][j] == symbol) {
                compteur++;
            } else if (board[i][j] != 'X' && board[i][j] != 'O') {
                
                index_vide = (i * 3) + j;
            }
        }
        // 2 symboles + 1 case vide
        if (compteur == 2 && index_vide != -1) {
            return index_vide;
        }
    }

    // colonnes
    for (int j = 0; j < 3; j++) {
        int compteur = 0;
        int index_vide = -1;

        for (int i = 0; i < 3; i++) {
            if (board[i][j] == symbol) {
                compteur++;
            } else if (board[i][j] != 'X' && board[i][j] != 'O') {
                index_vide = (i * 3) + j;
            }
        }
        if (compteur == 2 && index_vide != -1) {
            return index_vide;
        }
    }

    // Diagonales
    
    int d1_indices[3] = {0, 4, 8}; 
    int compteur = 0;
    int index_vide = -1;
    
    for (int k = 0; k < 3; k++) {
        int case_idx = d1_indices[k];
        int r = case_idx / 3;
        int c = case_idx % 3;
        
        if (board[r][c] == symbol) compteur++;
        else if (board[r][c] != 'X' && board[r][c] != 'O') index_vide = case_idx;
    }
    if (compteur == 2 && index_vide != -1) return index_vide;

    int d2_indices[3] = {2, 4, 6};
    compteur = 0;
    index_vide = -1;

    for (int k = 0; k < 3; k++) {
        int case_idx = d2_indices[k];
        int l = case_idx / 3;
        int c = case_idx % 3;
        
        if (board[l][c] == symbol) compteur++;
        else if (board[l][c] != 'X' && board[l][c] != 'O') index_vide = case_idx;
    }
    if (compteur == 2 && index_vide != -1) return index_vide;

    return -1;
}


void Game::play_ia_turn() {

int case_choisie = -1;

    case_choisie = blocking_ia(p2.symbol);
    
    if (case_choisie != -1) {
        info_case = "L'IA gagne en case " + std::to_string(case_choisie + 1);
    } 
    else {
        // IA regarde si le joueur va gagner
        case_choisie = blocking_ia(p1.symbol);
        
        if (case_choisie != -1) {
             info_case = "L'IA bloque le joueur en case " + std::to_string(case_choisie + 1);
        }
        else {

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
                info_case = "L'IA a joué en case " + std::to_string(case_choisie + 1);
            }
        }
    }   

    if (case_choisie != -1) {
        int ligne = case_choisie / 3;
        int col = case_choisie % 3;
        board[ligne][col] = p2.symbol;
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
    bool gagne = false;

    // Boucle max de 9 tours
    for (int i = 0; i < 9; i++) {

        // efface l'ecran
        erase_terminal(); 
        
        std::cout << " TOUR " << (i + 1) << " / 9 " << std::endl;

        if (i == 0) {
                // Seulement au tour 1
                std::cout << "DEBUT DE LA PARTIE !" << std::endl << std::endl;
                if (mode_ia) {
                    std::cout << "L'IA joue le symbole " << p2.symbol << std::endl << std::endl;
                }
            } else {
                // on affiche le dernier coup
                std::cout << ">> DERNIER COUP : " << info_case << " <<" << std::endl;
            }
        
        // plateau a jour
        draw_game_board();
        
        // Si i est pair c'est le joueur 1
        if (i % 2 == 0) {
            play_turn(p1);
            if (check_win(p1.symbol)) {
                erase_terminal();
                draw_game_board();
                std::cout << "Bravo " << p1.name << ", GAGNE la partie !" << std::endl;
                gagne = true;
                break;
            }
        } else {
            // Sinon c'est le joueur 2 ou IA

            if (mode_ia) {
                play_ia_turn();
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