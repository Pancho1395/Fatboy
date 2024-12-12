#ifndef BLOQUE_HPP
#define BLOQUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

static sf::Texture bloqueDestruibleTexture;

class Bloque {
public:
    Bloque(int i, int j) {
        if (bloqueDestruibleTexture.getSize().x == 0) {
            if (!bloqueDestruibleTexture.loadFromFile("assets/images/Bloque_Destruible.png")) {
                std::cerr << "Error: No se pudo cargar la textura Bloque_Destruible.png" << std::endl;
            }
        }

        float x = 128 + i * 64;
        float y = 64 + j * 64;
        this->sprite.setTexture(bloqueDestruibleTexture);
        this->sprite.setPosition(x, y);
        this->sprite.setScale(4, 4);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(this->sprite);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

private:
    sf::Sprite sprite;
};

#endif // BLOQUE_HPP
