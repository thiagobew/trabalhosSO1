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
        Thread::yield();
    }
}

void Collision::verifyCollisions()
{
    // Verifica os tiros dos inimigos contra o player
    for (auto listItem = this->enemiesShots.begin(); listItem != this->enemiesShots.end(); listItem++)
    {
        Projectile *enemyShot = *listItem;
        if (this->verifyIfHit(enemyShot, this->_playerShip))
        {
            // Dá o dano no player
            this->_playerShip->hit();
            // Destrói o tiro
            this->_window->removeDrawableItem(enemyShot);
            // TODO -> Tem que deletar o tiro
            if (this->_playerShip->isDead())
                GameConfigs::finished = true;
        }
    }

    // Verifica os tiros do player contra os inimigos
    for (auto listItem = this->playerShots.begin(); listItem != this->playerShots.end(); listItem++)
    {
        // Pega o tiro
        Projectile *playerShot = *listItem;
        for (auto enemyItem = this->enemies.begin(); enemyItem != this->enemies.end(); enemyItem++)
        {
            // Para cada um dos inimigos verifica se ele tomou o tiro
            Enemy *enemy = *enemyItem;
            if (this->verifyIfHit(playerShot, this->_playerShip))
            {
                // Remove o tiro do jogador da tela
                this->_window->removeDrawableItem(playerShot);

                enemy->hit();
                if (enemy->isDead())
                    this->_window->removeDrawableItem(enemy);
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

__END_API