#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>


class Enemy{
protected:
    sf::Sprite sprite;
    sf::Texture texture;

    int health;
    float speedX;
    float speedY;
    bool alive;
public:
    Enemy(float startX,float startY);
    virtual ~Enemy()=default;    
    virtual void update();
    virtual void draw(sf::RenderWindow& window);
    virtual void takeDamage(int damage = 1);

    sf::FloatRect getBounds();
    bool isAlive();
    sf::Vector2f getPosition();

};

#endif
