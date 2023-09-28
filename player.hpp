#pragma once

#include <SFML/Graphics.hpp>

const int SCREEN_LENGHT = 1920;
const int SCREEN_WIDTH = 1080;


class Player: sf::Shape
{
    public:
        sf::RectangleShape hitbox;
        sf::Texture texture;
    
        int speed;
        int x;
        int y;

        int lenght;
        int width;

        

        void move_right()
        {
            hitbox.setPosition(sf::Vector2f(  (x + speed) <= SCREEN_LENGHT ? (x + speed) : SCREEN_LENGHT, y));
        }

        void move_left()
        {
            hitbox.setPosition(sf::Vector2f(  (x - speed) >= 0 ? x - speed : 0, y));
        }

        void move_up()
        {
            hitbox.setPosition(sf::Vector2f(x, (y - speed) >= 0 ? (y - speed) : 0));
        }

        void move_down()
        {
            hitbox.setPosition(sf::Vector2f(x, (y + speed <= SCREEN_WIDTH) ? (y + speed) : SCREEN_WIDTH));
        }
};