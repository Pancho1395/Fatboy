#include <SFML/Graphics.hpp>
#include <Bomberman.hpp>
#include <Mapa.hpp>
#include <Bomba.hpp>
#include <vector>

double velocidad = 0.1;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1084, 828), "Fatboy");

    Bomberman man1(sf::Vector2f(128, 40), sf::Color::Red);
    Mapa map(sf::Vector2f(0,0));
    map.genMatriz();
    map.generarBloques(); // Generar los bloques basados en la matriz

    std::vector<Bomba> bombs; // Vector para almacenar las bombas

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
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas)) {
                man1.move(velocidad, 0); // Revertir el movimiento si hay colisión
                man1.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            man1.right();
            man1.move(velocidad, 0);
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas)) {
                man1.move(-velocidad, 0); // Revertir el movimiento si hay colisión
                man1.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            man1.up();
            man1.move(0, -velocidad);
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas)) {
                man1.move(0, velocidad); // Revertir el movimiento si hay colisión
                man1.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            man1.down();
            man1.move(0, velocidad);
            if (man1.checkBlockCollision(map.getmatriz(), filas, columnas)) {
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
