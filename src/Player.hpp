#pragma once
#include<string>

struct Player {
    std::string name;
    char symbol;
};

Player create_player();
