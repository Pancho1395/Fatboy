#include <SFML/Graphics.hpp>
#include<Bomberman.hpp>
double velocidad = 0.05;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "DinoChrome");

    Bomberman man1(sf::Vector2f(400, 300), sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            man1.left();
            man1.move(velocidad * -1, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // Actualizar animacion man1chu
            man1.right();
            man1.move(velocidad, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            man1.up();
            man1.move(0, velocidad * -1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            man1.down();
            man1.move(0, velocidad);
        }else
            man1.stayd();

        
        window.clear();
        man1.draw(window);
        window.display();
    }

    return 0;
}