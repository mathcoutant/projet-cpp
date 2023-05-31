//
// Created by leo on 31/05/23.
//

#include "myMain.h"
#include <SFML/Graphics.hpp>

int myMain() {
    sf::RenderWindow window(sf::VideoMode(1000,1000),"projet cpp");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.display();
        sf::sleep(sf::milliseconds(17));
    }

    return 0;
}