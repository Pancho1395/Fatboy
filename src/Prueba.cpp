#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Bomberman.hpp>
#include <Mapa.hpp>
#include <Bomba.hpp>
#include <vector>

double velocidad = 0.1;

int main() {
    float left = 128.0f;
    float top = 64.0f;
    float right = 960.0f;
    float bottom = 768.0f;
    sf::RenderWindow window(sf::VideoMode(1084, 828), "Fatboy");

    Bomberman man1(sf::Vector2f(128, 40), sf::Color::Red);
    Bomberman man2(sf::Vector2f(896, 640), sf::Color::Blue); // Jugador 2 un bloque más arriba

    Mapa map(sf::Vector2f(0, 0));
    map.genMatriz();
    map.generarBloques();

    std::vector<Bomba> bombs;
    std::vector<Bomba> bombs2; // Bombas del jugador 2

    sf::Music music;
    if (!music.openFromFile("./assets/music/Super Bomberman - World 1 (SNES OST).OGG")) {
        return -1;
    }

    music.play();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Colocar bombas
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                man1.placeBomb(bombs);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                man2.placeBomb(bombs2);
            }
        }

        // Movimiento del jugador 1 con colisiones
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

        // Movimiento del jugador 2 con colisiones
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            man2.left();
            man2.move(-velocidad, 0);
            if (man2.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man2.move(velocidad, 0); // Revertir el movimiento si hay colisión
                man2.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            man2.right();
            man2.move(velocidad, 0);
            if (man2.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man2.move(-velocidad, 0); // Revertir el movimiento si hay colisión
                man2.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            man2.up();
            man2.move(0, -velocidad);
            if (man2.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man2.move(0, velocidad); // Revertir el movimiento si hay colisión
                man2.stayd();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            man2.down();
            man2.move(0, velocidad);
            if (man2.checkBlockCollision(map.getmatriz(), filas, columnas, left, top, right, bottom)) {
                man2.move(0, -velocidad); // Revertir el movimiento si hay colisión
                man2.stayd();
            }
        } else {
            man2.stayd();
        }

        // Verificar daños al jugador 1 por todas las bombas
        for (auto &bomb : bombs) {
            bomb.update(map, man1.getSprite());
            sf::FloatRect spriteBounds = man1.getSprite().getGlobalBounds();
            spriteBounds.top += spriteBounds.height * 0.4f;   // Ajustar área de colisión
            spriteBounds.height *= 0.6f;                      // Limitar altura

            for (const auto &explosion : bomb.getExplosions()) {
                if (explosion.getGlobalBounds().intersects(spriteBounds)) {
                    man1.move(128 - man1.getSprite().getPosition().x, 40 - man1.getSprite().getPosition().y); // Reiniciar posición jugador 1
                    break;
                }
            }
        }

        for (auto &bomb : bombs2) {
            bomb.update(map, man1.getSprite());
            sf::FloatRect spriteBounds = man1.getSprite().getGlobalBounds();
            spriteBounds.top += spriteBounds.height * 0.4f;   // Ajustar área de colisión
            spriteBounds.height *= 0.6f;                      // Limitar altura

            for (const auto &explosion : bomb.getExplosions()) {
                if (explosion.getGlobalBounds().intersects(spriteBounds)) {
                    man1.move(128 - man1.getSprite().getPosition().x, 40 - man1.getSprite().getPosition().y); // Reiniciar posición jugador 1
                    break;
                }
            }
        }

        // Verificar daños al jugador 2 por todas las bombas
        for (auto &bomb : bombs) {
            bomb.update(map, man2.getSprite());
            sf::FloatRect spriteBounds = man2.getSprite().getGlobalBounds();
            spriteBounds.top += spriteBounds.height * 0.4f;   // Ajustar área de colisión
            spriteBounds.height *= 0.6f;                      // Limitar altura

            for (const auto &explosion : bomb.getExplosions()) {
                if (explosion.getGlobalBounds().intersects(spriteBounds)) {
                    man2.move(896 - man2.getSprite().getPosition().x, 640 - man2.getSprite().getPosition().y); // Reiniciar posición jugador 2
                    break;
                }
            }
        }

        for (auto &bomb : bombs2) {
            bomb.update(map, man2.getSprite());
            sf::FloatRect spriteBounds = man2.getSprite().getGlobalBounds();
            spriteBounds.top += spriteBounds.height * 0.4f;   // Ajustar área de colisión
            spriteBounds.height *= 0.6f;                      // Limitar altura

            for (const auto &explosion : bomb.getExplosions()) {
                if (explosion.getGlobalBounds().intersects(spriteBounds)) {
                    man2.move(896 - man2.getSprite().getPosition().x, 640 - man2.getSprite().getPosition().y); // Reiniciar posición jugador 2
                    break;
                }
            }
        }

        // Limpiar y dibujar en la ventana
        window.clear();
        map.draw(window);
        man1.draw(window);
        man2.draw(window);
        for (auto &bomb : bombs) {
            bomb.draw(window);
        }
        for (auto &bomb : bombs2) {
            bomb.draw(window);
        }
        window.display();
    }
    return 0;
}
