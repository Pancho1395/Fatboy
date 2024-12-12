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

    bool checkBlockCollision(int** matriz, int filas, int columnas, float left, float top, float right, float bottom) {
    // Posición de la mitad inferior del sprite
    sf::Vector2f position = sprite.getPosition();
    float x_centro = position.x + sprite.getGlobalBounds().width / 2; // Mitad del ancho
    float y_abajo = position.y + sprite.getGlobalBounds().height;     // Borde inferior

    // Verificar colisiones con los bordes del mapa considerando los ajustes
    if (x_centro < left + 18 || x_centro > right - 18 || y_abajo < top + 20 || y_abajo > bottom) {
        return true; // Colisión con el borde del mapa
    }

    // Recorrer la matriz para verificar bloques en las posiciones (x, y)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            float bloqueX = 128 + i * 64; // Calcular posición X del bloque
            float bloqueY = 64 + j * 64;  // Calcular posición Y del bloque

            // Comparar la posición con la del sprite (ajustando 36 píxeles en los lados)
            if (x_centro >= bloqueX - 24 && x_centro < bloqueX + 64 + 24 &&
                y_abajo >= bloqueY && y_abajo < bloqueY + 64) {
                // Si encuentra un bloque en la matriz
                if (matriz[i][j] == 1 || matriz[i][j] == 3) {
                    return true; // Colisión con bloque sólido o destruible
                }
            }
        }
    }

    return false; // No hay colisión
}
    // Métodos para actualizar la animación y movimiento
    void right() { updateAnimation(248, 6); }
    void left() { updateAnimation(132, 6); }
    void up(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 6;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21)+366, 60, 18, 30));
            clock.restart();
        }
    }
    void down(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 6;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21)+3, 60, 18, 30));
            clock.restart();
        }
    }
     void stayd(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 3;
            sprite.setTextureRect(sf::IntRect((currentFrame * 21)+3, 14, 18, 30));
            clock.restart();
        }
    }
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
