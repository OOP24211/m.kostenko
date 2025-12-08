#include"Player.hpp"
#include "Bullet.hpp"

const float SPEED_PLAYER = 0.2f;

Player::Player(){
    if(!this->texture.loadFromFile("player.png")){
        sf::Image image;
        image.create(64, 64, sf::Color::Red);
        texture.loadFromImage(image);
    }
    this->sprite.setScale(0.2f, 0.2f);
    this->sprite.setTexture(texture);
    this->sprite.setPosition(400,500);

}

void Player::setPosition(float x, float y){
    sprite.setPosition(x,y);
}

void Player::update(){

    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && pos.x > 0){
        sprite.move(-(SPEED_PLAYER), 0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && pos.x + bounds.width<900){
        sprite.move(SPEED_PLAYER,0);
    }
    

}

void Player::draw(sf::RenderWindow& window){
    window.draw(sprite);
}

sf::FloatRect Player::getBounds(){
    return sprite.getGlobalBounds(); 
}

Bullet Player::Shoot(){
    Bullet bullet;

    sf::FloatRect bounds = sprite.getGlobalBounds();

    float x = bounds.left + (bounds.width/2) - 2.5f;
    float y = bounds.top - 15.0f;
    
    bullet.activator(x, y);

    return bullet;

}
