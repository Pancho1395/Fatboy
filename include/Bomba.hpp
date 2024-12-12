#ifndef BOMBA_HPP
#define BOMBA_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Bomba {
public:
    Bomba(sf::Vector2f position)
    {
        // Configurar el sprite de la bomba
        if (!texture.loadFromFile("assets/images/bomba.png")) {
            std::cerr << "Error: No se pudo cargar la textura de la bomba" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(3, 3); // Ajustar el tamaño de la bomba

        explosionTimer.restart(); // Iniciar el temporizador
        exploded = false;
        explosionFinished = false;
        explosionDuration = 1.0f; // Duración de la explosión en segundos
    }

    void update() {
        // Verificar si la bomba debe explotar
        if (explosionTimer.getElapsedTime().asSeconds() >= 3.0f && !exploded) {
            exploded = true;
            explosionStartTime = explosionTimer.getElapsedTime();
            generateExplosion();
        }

        // Verificar si la explosión debe terminar
        if (exploded && (explosionTimer.getElapsedTime() - explosionStartTime).asSeconds() >= explosionDuration) {
            explosions.clear(); // Eliminar las explosiones
            explosionFinished = true;
        }
    }

    void draw(sf::RenderWindow &window) {
        if (!exploded) {
            window.draw(sprite);
        } else if (!explosionFinished) {
            // Dibujar las explosiones
            for (auto &explosion : explosions) {
                window.draw(explosion);
            }
        }
    }

    bool hasExploded() const {
        return exploded;
    }

    bool isFinished() const {
        return explosionFinished;
    }

private:
    void generateExplosion() {
        // Generar explosiones en las 4 direcciones
        sf::Vector2f size(64, 64);

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 || j == 0) { // Solo en direcciones cardinales
                    sf::RectangleShape explosion(size);
                    explosion.setFillColor(sf::Color::Yellow);
                    explosion.setPosition(sprite.getPosition().x + i * size.x, 
                                          sprite.getPosition().y + j * size.y);
                    explosions.push_back(explosion);
                }
            }
        }
    }

    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock explosionTimer;
    sf::Time explosionStartTime;
    float explosionDuration;
    bool exploded;
    bool explosionFinished;
    std::vector<sf::RectangleShape> explosions;
};

#endif // BOMBA_HPP
