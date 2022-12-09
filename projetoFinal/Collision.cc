#include <allegro5/allegro_primitives.h>
#include "include/Collision.h"

__BEGIN_API

Collision::Collision() {}

Collision::~Collision() {}

void Collision::run()
{
    while (!GameConfigs::finished)
    {

        this->verifyCollisions();
        this->cleanOutsideObjects();
        Thread::yield();
    }
}

void Collision::verifyCollisions()
{
    // Verifica os tiros dos inimigos contra o player
    for (auto listItem = this->enemiesShots.begin(); listItem != this->enemiesShots.end();)
    {
        Projectile *enemyShot = *listItem;
        listItem++;

        if (this->verifyIfHit(enemyShot, this->_playerShip))
        {
            // Dá o dano no player
            this->_playerShip->hit(1);
            // Destrói o tiro
            this->_window->removeDrawableItem(enemyShot);
            this->enemiesShots.remove(enemyShot);
            delete enemyShot;

            if (this->_playerShip->isDead())
            {
                GameConfigs::finished = true;
                return;
            }
        }
    }

    // Verifica os tiros do player contra os inimigos
    for (auto listItem = this->playerShots.begin(); listItem != this->playerShots.end();)
    {
        // Pega o tiro
        Projectile *playerShot = *listItem;
        listItem++;

        for (auto enemyItem = this->enemies.begin(); enemyItem != this->enemies.end();)
        {
            // Para cada um dos inimigos verifica se ele tomou o tiro
            Enemy *enemy = *enemyItem;
            enemyItem++;

            if (this->verifyIfHit(playerShot, enemy))
            {
                // Remove o tiro do jogador da tela e destrói
                this->_window->removeDrawableItem(playerShot);
                this->playerShots.remove(playerShot);
                delete playerShot;

                enemy->hit(1);
                if (enemy->isDead())
                {
                    this->_window->removeDrawableItem(enemy);
                    this->enemies.remove(enemy);
                    delete enemy;
                }
            }
        }
    }
}

bool Collision::verifyIfHit(Projectile *projectile, Hittable *hittable)
{
    Point projectilePos = projectile->getPosition();
    Point hittablePos = hittable->getPosition();
    int hittableSize = hittable->getSize();

    if (projectilePos.x > hittablePos.x - hittableSize &&
        (projectilePos.x < hittablePos.x + hittableSize) &&
        (projectilePos.y > hittablePos.y - hittableSize) &&
        (projectilePos.y < hittablePos.y + hittableSize))
        return true;
    return false;
}

void Collision::cleanOutsideObjects()
{
    // Clean enemies
    for (auto enemyItem = this->enemies.begin(); enemyItem != this->enemies.end();)
    {
        Enemy *enemy = *enemyItem;
        enemyItem++;

        if (enemy->isOutside())
        {
            this->_window->removeDrawableItem(enemy);
            this->enemies.remove(enemy);
            delete enemy;
        }
    }

    // Clean enemies shots
    for (auto enemyItem = this->enemiesShots.begin(); enemyItem != this->enemiesShots.end();)
    {
        Projectile *projectile = *enemyItem;
        enemyItem++;

        if (projectile->isOutside())
        {
            this->_window->removeDrawableItem(projectile);
            this->enemiesShots.remove(projectile);
            delete projectile;
        }
    }

    // Clean playerShots
    for (auto playerShot = this->playerShots.begin(); playerShot != this->playerShots.end();)
    {
        Projectile *projectile = *playerShot;
        playerShot++;

        if (projectile->isOutside())
        {
            this->_window->removeDrawableItem(projectile);
            this->playerShots.remove(projectile);
            delete projectile;
        }
    }
}

__END_API