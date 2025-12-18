#include <iostream>
#include <cctype>
#include "Player.hpp"
#include "Game.hpp"

int main() {

    //Joueur 1
    std::cout<< "Joueur 1"<<std::endl;
    Player p1 = create_player();
    std::cout <<"Joueur 1 " <<p1.name<< " joue le " << p1.symbol <<std::endl;
    
    //Joueur 2
    std::cout<< "Joueur 2"<<std::endl;
    Player p2 = create_player();

    // si mm symbol pris
    while(p1.symbol==p2.symbol){
        std::cout << "[ERROR] Le symbole " << p1.symbol << " est deja pris par " << p1.name <<std::endl;
        std::cout << p2.name << ", choisissez un autre symbole : ";
        std::cin >> p2.symbol;
        }
    std::cout <<"Joueur 2 " <<p2.name<< " joue le " << p2.symbol <<std::endl;

    //Plateau de jeu
    std::cout<<p1.name<<" VS "<<p2.name<< " START! ";

        Board plateau;

        init_board(plateau);

        draw_game_board(plateau);

        std::cout << "test" << std::endl;

        play_turn(plateau, p1);

        draw_game_board(plateau);
        
    return 0;
}