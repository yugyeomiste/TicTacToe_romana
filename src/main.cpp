#include <iostream>
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

    while(p1.symbol==p2.symbol){
        std::cout << "[ERROR] Le symbole " << p1.symbol << " est deja pris par " << p1.name <<std::endl;
        std::cout << p2.name << ", choisissez un autre symbole : ";
        std::cin >> p2.symbol;
        }
    std::cout <<"Joueur 2 " <<p2.name<< " joue le " << p2.symbol <<std::endl;

    std::cout<<p1.name<<" VS "<<p2.name<< " START! ";

    std::cout << "LE MATCH : " << p1.name << " (" << p1.symbol << ") VS " 
                << p2.name << " (" << p2.symbol << ") START !"<<std::endl;

        Board plateau;

        init_board(plateau);

        draw_game_board(plateau);
        
    return 0;
}