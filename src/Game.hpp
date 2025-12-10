#pragma once
#include<array>

using Board = std::array<std::array<int, 3>,3>;

void init_board(Board& board);

void draw_game_board(const Board& board);



