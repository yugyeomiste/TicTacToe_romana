#pragma once
#include <array>
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
    bool check_win(char symbol) const;
    void setup_players(); 

    Board board;
    Player p1;
    Player p2;
};