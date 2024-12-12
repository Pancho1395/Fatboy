
#ifndef BOMBA_HPP
#define BOMBA_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Mapa.hpp"

class Bomba {
public:
    Bomba(sf::Vector2f position) {
        // Cargar textura de la bomba
        if (!texture.loadFromFile("assets/images/Bomba sprite.png")) {
            std::cerr << "Error: No se pudo cargar la textura de la bomba" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 32, 32)); // Tamaño inicial del frame
        sprite.setPosition(position);
        sprite.setScale(2, 2);

        // Inicializar estados y temporizadores
        explosionTimer.restart();
        exploded = false;
        explosionFinished = false;
        explosionDuration = 1.0f; // Duración de la explosión en segundos
    }

    void update(Mapa &map) {
        if (!exploded && explosionTimer.getElapsedTime().asSeconds() >= 3.0f) {
            exploded = true;
            generateExplosion(map); // Generar la explosión
            explosionTimer.restart(); // Reiniciar temporizador para la duración de la explosión
        }

        // Finalizar la explosión después de 1 segundo
        if (exploded && explosionTimer.getElapsedTime().asSeconds() >= explosionDuration) {
            explosions.clear(); // Limpiar las explosiones
            explosionFinished = true; // Marcar como finalizada
        }
    }

    void draw(sf::RenderWindow &window) {
        if (!exploded) {
            window.draw(sprite); // Dibujar la bomba
        } else if (!explosionFinished) {
            for (auto &explosion : explosions) {
                window.draw(explosion); // Dibujar las explosiones
            }
        }
    }

    bool isFinished() const {
        return explosionFinished; // Verificar si la explosión ha terminado
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock explosionTimer;
    float explosionDuration;
    bool exploded;
    bool explosionFinished;
    std::vector<sf::RectangleShape> explosions;

    void generateExplosion(Mapa &map) {
        sf::Vector2f size(64, 64);

        // Crear explosiones en direcciones cardinales
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 || j == 0) { // Evitar diagonales, solo direcciones cardinales
                    sf::RectangleShape explosion(size);
                    explosion.setFillColor(sf::Color::Yellow); // Color amarillo para la explosión
                    explosion.setPosition(sprite.getPosition().x + i * size.x,
                                          sprite.getPosition().y + j * size.y);
                    explosions.push_back(explosion);

                    // Verificar y destruir bloques en el mapa
                    int x = (sprite.getPosition().x + i * size.x - 128) / 64;
                    int y = (sprite.getPosition().y + j * size.y - 64) / 64;
                    if (x >= 0 && x < filas && y >= 0 && y < columnas &&
                        map.getmatriz()[x][y] == 3) {
                        map.eliminarBloque(x, y);
                    }
                }
            }
        }
    }
};

#endif // BOMBA_HPP
