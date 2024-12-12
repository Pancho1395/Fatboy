#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath> // Para usar std::round
#include "Bomba.hpp"

class Bomberman {
public:
    Bomberman(sf::Vector2f position, sf::Color color)
    {
        shape.setSize(sf::Vector2f(18 * 3, 30 * 3)); // Tamaño escalado del personaje
        shape.setPosition(position);
        shape.setFillColor(sf::Color(color.r, color.g, color.b, 0));

        if (!texture.loadFromFile("assets/images/bomberman.png")) {
            std::cerr << "Error: No se pudo cargar la textura del personaje" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(3, 14, 18, 30)); // Rectángulo inicial
        sprite.setPosition(position);
        sprite.setScale(3, 3);
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
        shape.move(offsetX, offsetY);
    }

    void placeBomb(std::vector<Bomba>& bombs)
    {
        sf::Vector2f position = sprite.getPosition();

        // Centrar la bomba en la celda del mapa
        float cellSize = 64.0f; // Tamaño de la celda
        float centeredX = std::round(position.x / cellSize) * cellSize;
        float centeredY = std::round(position.y / cellSize) * cellSize;

        bombs.emplace_back(sf::Vector2f(centeredX, centeredY)); // Agregar la bomba al vector
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }

    bool checkBlockCollision(int** matriz, int filas, int columnas)
    {
        sf::Vector2f position = sprite.getPosition();
        float x_centro = position.x + sprite.getGlobalBounds().width / 2;
        float y_abajo = position.y + sprite.getGlobalBounds().height;

        for (int i = 0; i < filas; ++i) {
            for (int j = 0; j < columnas; ++j) {
                float bloqueX = 128 + i * 64; // Calcular posición del bloque
                float bloqueY = 64 + j * 64;

                if (x_centro >= bloqueX && x_centro < bloqueX + 64 &&
                    y_abajo >= bloqueY && y_abajo < bloqueY + 64) {
                    if (matriz[i][j] == 1 || matriz[i][j] == 3) {
                        return true; // Colisión detectada
                    }
                }
            }
        }
        return false; // No hay colisión
    }

    // Métodos para actualizar la animación y movimiento
    void right() { updateAnimation(248, 6); }
    void left() { updateAnimation(132, 6); }
    void up() { updateAnimation(366, 6); }
    void down() { updateAnimation(3, 6); }
    void stayd() { updateAnimation(3, 3, 14); }

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    int currentFrame = 0;
    float frameTime = 0.1f; // Tiempo entre cuadros

    void updateAnimation(int startX, int frameCount, int yOffset = 60) {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(sf::IntRect(startX + currentFrame * 18, yOffset, 18, 30));
            clock.restart();
        }
    }
};

#endif // BOMBERMAN_HPP
