#include<iostream>
#include"Player.hpp"
#include <cctype>

Player create_player(){
    Player p;
    std::cout<<"Entrez votre nom: ";
    std::cin >> p.name;

    // si mm symbol pris

    char symbol;
    while (true) {
        std::cout <<"Choisissez X ou O; ";
        std::cin>> symbol;

        symbol= std::toupper(symbol);

        if(symbol == 'X' || symbol == 'O'){
            p.symbol= symbol;
            break;
            } else {
            std::cout <<"[ERROR] Choisir X ou O"<<std::endl;
            }
            }
    return p;
    }

