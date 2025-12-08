#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

class Bullet{
    private:
    sf::Sprite sprite;
    sf::Texture texture;
    bool active;

    public:
    Bullet();
    void update();
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds();
    void setPosition(float x, float y);
    bool isActive();
    void activator(float x, float y);
    void setActive(bool isActive);
};

#endif