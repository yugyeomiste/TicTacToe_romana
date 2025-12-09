#include<iostream>
#include"Player.hpp"

Player create_player(){
    Player p;
    std::cout<<"Entrez votre nom:";
    std::cin >> p.name;

    char symbol;
    while (true) {
        std::cout <<"Choisissez X ou O; ";
        std::cin>> symbol;

        if(symbol == 'X' || symbol == 'O'){
            p.symbol= symbol;
            break;
        } else {
         std::cout <<"[ERROR] Choisir X ou O"<<std::endl;
        }
    }
    return p;
}
