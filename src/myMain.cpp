//
// Created by leo on 31/05/23.
//

#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "SFMLOrthogonalLayer.h"
#include "Game.h"
#include <SFML/Window/Event.hpp>

int myMain() {
    Game game;
    game.run();

    return 0;
}