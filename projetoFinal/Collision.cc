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
            // Notifica o objeto tiro que ele acertou algo
            enemyShot->ackHitSomething();
            // Dá o dano no player
            this->_playerShip->hit(enemyShot->getDamage());

            // Se o tiro foi destruído deleta ele
            if (enemyShot->wasDestroyed())
            {
                // Destrói o tiro
                this->_window->removeDrawableItem(enemyShot);
                this->enemiesShots.remove(enemyShot);
                delete enemyShot;
            }

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
                enemy->hit(playerShot->getDamage());
                if (enemy->isDead())
                {
                    this->_window->removeDrawableItem(enemy);
                    this->enemies.remove(enemy);
                    delete enemy;
                }

                // Notifica o projetil que acertou alguma coisa
                playerShot->ackHitSomething();
                // Verifica se foi destruído no hit
                if (playerShot->wasDestroyed())
                {
                    // Remove o tiro do jogador da tela e destrói
                    this->_window->removeDrawableItem(playerShot);
                    this->playerShots.remove(playerShot);
                    delete playerShot;
                    break;
                }
            }
        }
    }

    // Verifica impacto entre o player ship e os inimigos
    for (auto listItem = this->enemies.begin(); listItem != this->enemies.end();)
    {
        Enemy *enemy = *listItem;
        listItem++;

        if (this->verifyIfHit(enemy, this->_playerShip))
        {
            enemy->hit(1);

            if (enemy->isDead())
            {
                this->_window->removeDrawableItem(enemy);
                this->enemies.remove(enemy);
                delete enemy;
            }

            this->_playerShip->hit(1);
            if (this->_playerShip->isDead())
            {
                GameConfigs::finished = true;
                return;
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

bool Collision::verifyIfHit(Drawable *first, Drawable *second)
{
    int firstSize = first->getSize();
    Point firstPos = first->getPosition();
    int secondSize = second->getSize();
    Point secondPos = second->getPosition();

    return (abs(firstPos.x - secondPos.x) < (firstSize + secondSize) && 
            abs(firstPos.y - secondPos.y) < (firstSize + secondSize));
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