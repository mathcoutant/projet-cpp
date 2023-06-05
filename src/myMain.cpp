//
// Created by leo on 31/05/23.
//

#include "myMain.h"
#include <SFML/Graphics.hpp>
#include "SFMLOrthogonalLayer.h"

int myMain() {

    tmx::Map map;
    map.load("resources/demo.tmx");

    MapLayer layerZero(map,0);
    MapLayer layerOne(map,1);
    MapLayer layerTwo(map,2);

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
        window.draw(layerZero);
        window.draw(layerOne);
        window.draw(layerTwo);
        window.display();
        sf::sleep(sf::milliseconds(17));
    }

    return 0;
}