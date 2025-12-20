#pragma once
#include <array>
#include<string>
#include"Player.hpp"

using Board = std::array<std::array<char, 3>, 3>;

class Game {
public:
    Game(); 
    void run(); 

private:
    void init_board();
    void draw_game_board() const;
    void play_turn(Player& player);
    void play_ia_turn();
    bool check_win(char symbol) const;
    void setup_players(); 
    void erase_terminal() const;
    int blocking_ia(char symbol) const;

    Board board;
    Player p1;
    Player p2;

    bool mode_ia;
    std::string info_case;

};