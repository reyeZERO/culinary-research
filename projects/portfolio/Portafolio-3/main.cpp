#include <iostream>
#include "game.h"

int main() {
    GameOfLife game;
    game.configureRules(); 
    game.initialize();     
    while (game.run()) {  
        game.update();
        game.display();
    }
    return 0;
}
