#include <iostream>
#include "Player.hpp"

int main() {
std::cout<< "Joueur 1"<<std::endl;
Player p1 = create_player();
std::cout <<"Joueur 1 " <<p1.name<< " joue le " << p1.symbol <<std::endl;

char other_symbol; 
    if (p1.symbol == 'X') {
        other_symbol = 'O';
    } else {
        other_symbol= 'X';
    }

std::cout<< "Joueur 2"<<std::endl;
Player p2 = create_player(other_symbol);
std::cout <<"Joueur 2 " <<p2.name<< " joue le " << p2.symbol <<std::endl;\

while(p1.symbol==p2.symbol){
    std::cout << "[ERROR] Le symbole " << p1.symbol << " est deja pris par " << p1.name <<std::endl;
    std::cout << p2.name << ", choisissez un autre symbole : ";
    std::cin >> p2.symbol;
    }

std::cout<<p1.name<<" VS "<<p2.name<< " START! ";

return 0;
}