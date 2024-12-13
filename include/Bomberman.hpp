#ifndef BOMBERMAN_HPP
#define BOMBERMAN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bomba.hpp"
#include <cmath>

class Bomberman {
public:
    Bomberman(sf::Vector2f position, sf::Color color) {
        shape.setSize(sf::Vector2f(18 * 3, 30 * 3));
        shape.setPosition(position);
        shape.setFillColor(sf::Color(color.r, color.g, color.b, 0));

        if (!texture.loadFromFile("assets/images/bomberman.png")) {
            std::cerr << "Error: No se pudo cargar la textura del personaje" << std::endl;
        }

        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(3, 14, 18, 30));
        sprite.setPosition(position);
        sprite.setScale(3, 3);
    }
    void lostLife() {
    
        vidas--; // Reducir una vida
    sprite.setPosition(-100, -100); // Posición temporal fuera de la pantalla

    // Volver a la posición inicial después del retraso
    sprite.setPosition(128, 40);

    }

    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
        shape.move(offsetX, offsetY);
    }

    void placeBomb(std::vector<Bomba> &bombs) {
        sf::Vector2f position = sprite.getPosition();
        float cellSize = 64.0f;

        // Redondear a la celda más cercana
        float centeredX = std::round(position.x / cellSize) * cellSize;
        float centeredY = std::round(position.y / cellSize) * cellSize;

        // Colocar la bomba en la celda centralizada
        bombs.emplace_back(sf::Vector2f(centeredX, centeredY));
    }

    void draw(sf::RenderWindow &window) {
        window.draw(sprite);
    }

    // Métodos de animación y colisiones
    void left() {
        updateAnimation(132, 6, 60); // Animación izquierda
    }

    void right() {
        updateAnimation(248, 6, 60); // Animación derecha
    }

    void up() {
        updateAnimation(366, 6, 60); // Animación hacia arriba
    }

    void down() {
        updateAnimation(3, 6, 60); // Animación hacia abajo
    }

    void stayd() {
        updateAnimation(3, 3, 14); // Animación quieto
    }

    bool checkBlockCollision(int** matriz, int rows, int cols, float left_bound, float top_bound, float right_bound, float bottom_bound) {
        sf::Vector2f position = sprite.getPosition();
        float x_centro = position.x + sprite.getGlobalBounds().width / 2;
        float y_abajo = position.y + sprite.getGlobalBounds().height;

        // Colisiones con los bordes
        if (x_centro < left_bound + 18 || x_centro > right_bound - 18 || 
            y_abajo < top_bound + 20 || y_abajo > bottom_bound + 20) {
            return true;
        }

        // Colisiones con los bloques
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                float bloqueX = 128 + i * 64;
                float bloqueY = 64 + j * 64;
                if (x_centro >= bloqueX - 24 && x_centro < bloqueX + 64 + 24 &&
                    y_abajo >= bloqueY && y_abajo < bloqueY + 64) {
                    if (matriz[i][j] == 1 || matriz[i][j] == 3) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
    sf::Sprite& getSprite() {
    return sprite;
}

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    int currentFrame = 0;
    float frameTime = 0.1f;
    int vidas;
    void updateAnimation(int startX, int frameCount, int yOffset) {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            currentFrame = (currentFrame + 1) % frameCount;
            sprite.setTextureRect(sf::IntRect(startX + currentFrame * 18, yOffset, 18, 30));
            clock.restart();
        }
    }
};

#endif // BOMBERMAN_HPP