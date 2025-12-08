#ifndef STRONGENEMY_HPP
#define STRONGENEMY_HPP

#include "Enemy.hpp"

class StrongEnemy : public Enemy {
private:
    const int INSTANT_DEATH_CHANCE = 1000;
    
public:
    StrongEnemy(float x, float y);
    void takeDamage(int damage) override;
    bool checkInstantDeath();
};

#endif
