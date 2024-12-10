#include <SFML/Graphics.hpp>
#include<Bloque.hpp>
#include<vector>
#include <ctime>
#include <stdlib.h>
#define filas 13
#define columnas 11
// using namespace System :: Drawing; // borrar linea si se queda en comentarios
class Mapa{
public:
Mapa(sf::Vector2f position){
     if (!texture.loadFromFile("assets/images/Mapa.png"))
        {
        
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
        matriz = new int*[filas];
        for (int i = 0; i < filas; i++) 
            matriz[i] = new int[columnas];
}
void draw(sf::RenderWindow &window)
    {
        this->sprite.setScale(4, 4); // Escala la imagen al 400%
        window.draw(this->shape);
        window.draw(this->sprite);
        for (auto &bloque : bloques) {
            bloque.draw(window);
        }
        
    }
    void generarBloques() {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                // Solo generar bloques destruibles (matriz[i][j] == 3)
                if (matriz[i][j] == 3) {
                    bloques.emplace_back(i, j); // Crear y agregar el bloque al vector
                }
                else{}
            }
        }
    }
    void genMatriz() {
        srand(time(NULL));
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (i % 2 == 1 && j % 2 == 1) {
                    matriz[i][j] = 1; // Bloques sólidos
                } else {
                    matriz[i][j] = (rand() % 2) ? 3 : 0; // Aleatoriamente crea un bloque destruible (3) o espacio vacío (0)
                }
            }
        }
    }

int **getmatriz(){
    return matriz;
}

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    int **matriz;
    std::vector<Bloque> bloques; // Vector para almacenar los bloques generados
};