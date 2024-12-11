#ifndef BLOQUE_HPP
#define BLOQUE_HPP

#include <SFML/Graphics.hpp>
#include <iostream> // Para imprimir errores en consola

// Textura compartida entre todos los bloques (estática y global)
static sf::Texture bloqueDestruibleTexture;

class Bloque {
public:
    Bloque(int i, int j) {
        // Cargar la textura una sola vez (al inicio del programa)
        if (bloqueDestruibleTexture.getSize().x == 0) { // Comprobar si no se ha cargado aún
            if (!bloqueDestruibleTexture.loadFromFile("assets/images/Bloque_Destruible.png")) {
                std::cerr << "Error: No se pudo cargar la textura Bloque_Destruible.png" << std::endl;
            }
        }

        // Configurar el sprite
        float x = 128 + i * 64;
        float y = 64 + j * 64;
        this->sprite.setTexture(bloqueDestruibleTexture); // Usar textura global
        this->sprite.setPosition(x, y);
        this->sprite.setScale(4, 4); // Escalar al 400%
    }

    void draw(sf::RenderWindow &window) {
        window.draw(this->sprite);
    }
private:
    sf::Sprite sprite;
};
#endif // BLOQUE_HPPs