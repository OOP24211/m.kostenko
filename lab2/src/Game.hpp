#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include "Player.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "StrongEnemy.hpp"

class Game {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape dangerLine;
    const float DANGER_LINE_Y = 500.0f;
    sf::RenderWindow window;
    
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy*> enemies;
    bool gameOver;
    
    void processEvents();
    void update();
    void render();
    void checkHit();
    
    void spawnWave();

    void checkDangerLine(); 
    
public:
    Game();
    ~Game();
    void run();
};

#endif