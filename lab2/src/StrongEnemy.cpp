#include <cstdlib>
#include <ctime>

#include "StrongEnemy.hpp"

StrongEnemy::StrongEnemy(float x, float y) : Enemy(x, y) {
    health = 10; 
    speedX = 0.3f;

    if(!this->texture.loadFromFile("strong_enemy.png")) {
        sf::Image image;
        image.create(30, 30, sf::Color::Magenta);
        texture.loadFromImage(image);
    }
    this->sprite.setScale(0.15f, 0.15f);
    this->sprite.setTexture(texture);
    this->sprite.setPosition(x, y);
}

void StrongEnemy::takeDamage(int damage) {
    health -= damage;
    
    if(health <= 0){
        alive = false;
    }
}

bool StrongEnemy::checkInstantDeath() {
    int randomNum = std::rand() % INSTANT_DEATH_CHANCE + 1;
    return (randomNum == 666);
}