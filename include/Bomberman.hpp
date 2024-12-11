#include <SFML/Graphics.hpp>

class Bomberman
{
public:
    Bomberman(sf::Vector2f position, sf::Color color)
    {
        shape.setSize(sf::Vector2f(18, 30));
        shape.setPosition(position); // Posición inicial cuadro
        shape.setFillColor(sf::Color(color.r, color.g, color.b, 0));

        // Cargar la imagen desde un archivo
        
        if (!texture.loadFromFile("assets/images/bomberman.png"))
        {
        
        }
        this->sprite = sf::Sprite(texture);
        this->sprite.setPosition(position); // Posición inicial sprite
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
        shape.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow &window)
    {
        this->sprite.setScale(3, 3); // Escala la imagen al 50%
        window.draw(this->shape);
        window.draw(this->sprite);
    }

    void right(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 6;
            sprite.setTextureRect(sf::IntRect((currentFrame * 18)+248, 60, 17, 30));
            clock.restart();
        }
    }
    void left(){
        // Actualizar el frame de la animación
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % 6;
            sprite.setTextureRect(sf::IntRect((currentFrame * 18)+132, 60, 17, 30));
            clock.restart();
        }
    }
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
bool checkBlockCollision(int** matriz, int filas, int columnas) {
    // Posición de la mitad inferior del sprite
    sf::Vector2f position = sprite.getPosition();
    float x_centro = position.x + sprite.getGlobalBounds().width / 2; // Mitad del ancho
    float y_abajo = position.y + sprite.getGlobalBounds().height;     // Borde inferior

    // Recorrer la matriz para verificar bloques en las posiciones (x, y)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            float bloqueX = 128 + i * 64; // Calcular posición X del bloque
            float bloqueY = 64 + j * 64;  // Calcular posición Y del bloque

            // Comparar la posición con la del sprite (centro-abajo)
            if (x_centro >= bloqueX && x_centro < bloqueX + 64 &&
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
private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.1f; // Tiempo entre cada frame en segundos
    int currentFrame = 0;
    int numFrames = 4; // Número total de frames en la animación
    int frameWidth = 32;
    int frameHeight=32;
};