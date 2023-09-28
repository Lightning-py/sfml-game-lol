#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape shape(50.f);
    sf::RectangleShape bro(sf::Vector2f(50, 50));

    shape.setFillColor(sf::Color::Transparent);
    bro.setFillColor(sf::Color::Cyan);
    shape.setPosition(sf::Vector2f(0, 0));


    float speed = 5;


    std::vector<sf::Color> colors = {
        sf::Color::Blue,
        sf::Color::Cyan,
        sf::Color::Green,
        sf::Color::Magenta,
        sf::Color::Red,
        sf::Color::White, 
        sf::Color::Yellow
        };
    unsigned int i = 0;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                shape.setFillColor(colors[i % colors.size()]);
                ++i;
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::A)
                    bro.move(-1 * speed, 0);
                if (event.key.code == sf::Keyboard::D)
                    bro.move(1 * speed, 0);
                if (event.key.code == sf::Keyboard::W)
                    bro.move(0, -1 * speed);
                if (event.key.code == sf::Keyboard::S)
                    bro.move(0, 1 * speed);
                if (event.key.code == sf::Keyboard::R)
                    bro.rotate(5);
            }
        }

        window.clear();
        window.draw(shape);
        window.draw(bro);
        window.display();
    }

    return 0;
}
