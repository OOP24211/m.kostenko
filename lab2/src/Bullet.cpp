#include "Bullet.hpp"
const float SPEED_BULLET = 1.0f;
Bullet::Bullet(){
    texture.create(5, 15);

    sf::Image image;
    image.create(5, 15, sf::Color::Blue);
    texture.update(image);
    
    sprite.setScale(1.0, 1.0);
    this->sprite.setTexture(texture);
    active = false;
}

void Bullet::update(){
    if(!active)return;
    sprite.move(0,-SPEED_BULLET);
    
    if (sprite.getPosition().y < 0) {
     active = false;
    }
}

void Bullet::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

sf::FloatRect Bullet::getBounds(){
    return sprite.getGlobalBounds();
}

void Bullet::setPosition(float x, float y){
    sprite.setPosition(x,y);
}

bool Bullet::isActive(){
    return active;
}

void Bullet::activator(float x, float y){
    sprite.setPosition(x,y);
    active = true;
}

void Bullet::setActive(bool isActive) {
    active = isActive;
}
