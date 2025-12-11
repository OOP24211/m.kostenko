#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>
#include "Bullet.hpp"

class Player{
private:
    sf::Sprite sprite;
    sf::Texture texture;
public:
    Player();
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void setPosition(float x, float y);
    Bullet Shoot();
};

#endif
