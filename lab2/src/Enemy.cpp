#include "Enemy.hpp"

Enemy::Enemy(float startX,float startY) : speedX(0.2f), speedY(0.0f), health(1), alive(true){
        if(!this->texture.loadFromFile("enemy.png")){
        sf::Image image;
        image.create(40, 40, sf::Color::Yellow);
        texture.loadFromImage(image);
    }
    this->sprite.setScale(0.1f,0.1f);
    this->sprite.setTexture(texture);
    this->sprite.setPosition(startX,startY);
}

void Enemy::update(){
    if(!alive)return;

    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if(pos.x <=0 || pos.x + bounds.width>=900){
        speedX = -speedX;
        speedY = 10.0f;
    }
    sprite.move(speedX, speedY);
    speedY=0.0f;

}

void Enemy::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

void Enemy::takeDamage(int damage){
    health-=damage;

    if(health<=0){
        alive = false;
    }
}

sf::FloatRect Enemy::getBounds() {
    return sprite.getGlobalBounds();
}
bool Enemy::isAlive(){
    return alive;
}

sf::Vector2f Enemy:: getPosition(){

    return sprite.getPosition();
}
