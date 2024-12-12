#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Bomberman.hpp>
#include <Mapa.hpp>
#include <Bomba.hpp>
#include <vector>

double velocidad = 0.1;

int main()
{
    float left = 128.0f;
    float top = 64.0f;
    float right = 960.0f;
    float bottom = 768.0f;
    sf::RenderWindow window(sf::VideoMode(1084, 828), "Fatboy");

    Bomberman man1(sf::Vector2f(128, 40), sf::Color::Red);
    Mapa map(sf::Vector2f(0,0));
    map.genMatriz();
    map.generarBloques(); // Generar los bloques basados en la matriz

    std::vector<Bomba> bombs; // Vector para almacenar las bombas
    sf::Music music;
    if (!music.openFromFile("./assets/music/Super Bomberman - World 1 (SNES OST).OGG"))
    {
        // Error al cargar el archivo de música
        return -1;
    }

    // Reproducir la música
    music.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Colocar una bomba al presionar la barra espaciadora
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                man1.placeBomb(bombs);
            }
        }

        // Movimiento del personaje
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            man1.left();
            man1.move(-velocidad, 0);
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man1.move(velocidad, 0); // Revertir el movimiento si hay colisión
                man1.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            man1.right();
            man1.move(velocidad, 0);
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man1.move(-velocidad, 0); // Revertir el movimiento si hay colisión
                man1.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            man1.up();
            man1.move(0, -velocidad);
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man1.move(0, velocidad); // Revertir el movimiento si hay colisión
                man1.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            man1.down();
            man1.move(0, velocidad);
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man1.move(0, -velocidad); // Revertir el movimiento si hay colisión
                man1.stayd();
            }
        } else {
            man1.stayd();
        }

        // Actualizar el estado de las bombas
        for (auto &bomb : bombs) {
            bomb.update();
        }

        // Limpiar y dibujar en la ventana
        window.clear();
        map.draw(window);
        man1.draw(window);

        for (auto &bomb : bombs) {
            bomb.draw(window);
        }

        window.display();
    }

    return 0;
}
