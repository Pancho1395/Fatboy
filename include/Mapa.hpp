#ifndef MAPA_HPP
#define MAPA_HPP

#include <SFML/Graphics.hpp>
#include <Bloque.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

constexpr int filas = 13;
constexpr int columnas = 11;

class Mapa {
public:
    Mapa(sf::Vector2f position) {
        if (!texture.loadFromFile("assets/images/Mapa.png")) {
            // Manejo de error si es necesario
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position);
        matriz = new int*[filas];
        for (int i = 0; i < filas; i++)
            matriz[i] = new int[columnas];
    }

    void draw(sf::RenderWindow &window) {
        this->sprite.setScale(4, 4);
        window.draw(this->sprite);
        for (auto &bloque : bloques) {
            bloque.draw(window);
        }
    }

    void generarBloques() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (matriz[i][j] == 3) {
                    bloques.emplace_back(i, j);
                }
            }
        }
    }

    void genMatriz() {
        srand(time(NULL));
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                // Áreas libres para el jugador 1 y jugador 2
                if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 1 && j == 0) || // Área libre jugador 1
                    (i == 12 && j == 10) || (i == 12 && j == 9) || (i == 11 && j == 10)) { // Área libre jugador 2
                    matriz[i][j] = 0;
                } else if (i % 2 == 1 && j % 2 == 1) {
                    matriz[i][j] = 1; // Bloques sólidos
                } else {
                    matriz[i][j] = (rand() % 2) ? 3 : 0; // Bloques destructibles o vacíos
                }
            }
        }
    }

    void eliminarBloque(int i, int j) {
        matriz[i][j] = 0;
        bloques.erase(std::remove_if(bloques.begin(), bloques.end(),
            [i, j](const Bloque &bloque) {
                return bloque.getPosition().x == 128 + i * 64 &&
                       bloque.getPosition().y == 64 + j * 64;
            }), bloques.end());
    }

    int** getmatriz() {
        return matriz;
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    int **matriz;
    std::vector<Bloque> bloques;
};

#endif // MAPA_HPP
