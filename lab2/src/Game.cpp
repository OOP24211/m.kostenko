#include "Game.hpp"

Game::Game():gameOver(false){
    window.create(sf::VideoMode(900, 700), "Piu Piu");

    if (!backgroundTexture.loadFromFile("background.png")) {
        backgroundTexture.create(900, 700);
    }
    this->backgroundSprite.setScale(2.0f, 2.0f);
    backgroundSprite.setTexture(backgroundTexture);
    dangerLine.setSize(sf::Vector2f(900.0f, 3.0f));
    dangerLine.setPosition(0, DANGER_LINE_Y);
    dangerLine.setFillColor(sf::Color::Red);

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    spawnWave();
}

Game::~Game() {
    for (Enemy* enemy : enemies) {
        delete enemy;
    }
    enemies.clear();
}

void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Space) {

                Bullet newBullet = player.Shoot();
                bullets.push_back(newBullet);
            }
        }

    }
}

void Game::update(){
    if (gameOver) {
        return;
    }

    player.update();

    for (Enemy* enemy : enemies) {
        enemy->update();
    }
    for(size_t i = 0; i < bullets.size(); ) {
        if(!bullets[i].isActive()) {
            bullets.erase(bullets.begin() + i);
        } else {
            bullets[i].update();
            i++;
        }
    }
    checkHit();
    checkDangerLine();
        if (enemies.empty()) {
        gameOver = true;
        std::cout << "\n========================\n";
        std::cout << "       VICTORY!\n";
        std::cout << "  All enemies are destroyed!\n";
        std::cout << "========================\n";
    }
}


void Game::render(){
        
    window.clear();
    window.draw(backgroundSprite);
    player.draw(window);
    for (Enemy* enemy : enemies) {
        enemy->draw(window);
    }   
    for(auto& bullet : bullets) {
        bullet.draw(window);
    }
    window.draw(dangerLine);

    window.display();
}


void Game::run(){
    while(window.isOpen()){
        processEvents();
        update();
        render();

    }

}


void Game::checkHit() {
    for (Bullet& bullet : bullets) {
        if (!bullet.isActive()) continue;

        for (size_t i = 0; i < enemies.size(); ++i) {
            Enemy* enemy = enemies[i];
            if (!enemy->isAlive()) continue;
            
            if (bullet.getBounds().intersects(enemy->getBounds())) {

                if (StrongEnemy* strongEnemy = dynamic_cast<StrongEnemy*>(enemy)) {
                    if (strongEnemy->checkInstantDeath()) {
                        gameOver = true;
                        std::cout << "YOU'RE DEAD BECAUSE YOU'RE UNLUCKY." << std::endl;
                    }
                }
                enemy->takeDamage(1);
                bullet.setActive(false);

                if (!enemy->isAlive()) {
                    delete enemy;
                    enemies.erase(enemies.begin() + i);
                    --i;
                }
                
                break;
            }
        }
    }
}
void Game::spawnWave() {
    const int ROWS = 5;
    const int COLS = 7;
    const float START_X = 100.0f;
    const float START_Y = 50.0f;
    const float SPACING_X = 80.0f; 
    const float SPACING_Y = 60.0f;
    
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            float x = START_X + col * SPACING_X;
            float y = START_Y + row * SPACING_Y;
            if (row == ROWS - 1) {
                enemies.push_back(new StrongEnemy(x, y));
            } else {
                enemies.push_back(new Enemy(x, y));
            }
        }
    }
}

void Game::checkDangerLine() {
    for (Enemy* enemy : enemies) {
        if (!enemy->isAlive()) continue;

        sf::FloatRect bounds = enemy->getBounds();
        float enemyBottom = bounds.top + bounds.height;
        if (enemyBottom >= DANGER_LINE_Y) {
            gameOver = true;
            std::cout << "\n========================\n";
            std::cout << "       GAME OVER\n";
            std::cout << " The enemies have crossed the red line!\n";
            std::cout << "========================\n";
            break;
        }
    }
}
