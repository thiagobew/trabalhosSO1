#include "include/MinesControl.h"

__BEGIN_API

std::shared_ptr<Sprite> purpleMinesprite;

MinesControl::MinesControl()
{
    this->loadSprites();
    this->DELAY_MINE_SPAWN = 3000;
    this->DELAY_MINE_EXPLOSION = 500;
	this->_color = al_map_rgb(255, 0, 0);
    this->minesSpawnTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->minesSpawnTimer->create();
    this->minesSpawnTimer->startTimer();
}

MinesControl::~MinesControl() {}

void MinesControl::setWindowReference(Window *window) { this->_window = window; }
void MinesControl::setCollisionReference(Collision *collision) { this->_collision = collision; }
void MinesControl::removeMine(Mine *enemy) { this->mines.remove(enemy); }

void MinesControl::run()
{
    this->loadSprites();
    while (!GameConfigs::finished)
    {
        if (this->_window == nullptr || this->_collision == nullptr)
        {
            Thread::yield();
            continue;
        }

        this->processLoop();
        Thread::yield();
    }
}

void MinesControl::processLoop()
{
    // Há uma dependência aqui do timer ser maior do que o tempo para o ultimo sair da tela por causa de referência de ponteiros
    if (this->minesSpawnTimer->getCount() > this->DELAY_MINE_SPAWN)
        this->createMine();
    this->handleMines();
}

void MinesControl::handleMines()
{
    for (auto mineItem = this->mines.begin(); mineItem != this->mines.end();)
    {
        Mine *mine = *mineItem;
        mineItem++;

        if (this->minesSpawnTimer->getCount() > this->DELAY_MINE_EXPLOSION)
		{
			for(int i = 0; i < 20; i++) {
				Vector v = Vector(0, 0);
				v.rollRandom();
				Laser *laser = new Laser(mine->getPosition(), _color, v, this->mineExplosionSprite, false);
				this->_collision->addEnemiesShot(laser);
			}
		}
    }
}

void MinesControl::createMine()
{
    this->mines.clear();

	Point p = Point(0, 0);
	p.rollRandom();

    Mine* mine = new Mine(p, Vector(-180, 0), this->mineSprite, this->mineExplosionSprite, this->_collision, this->_window);
	this->mines.push_back(mine);
	this->_collision->addEnemies(mine);

    // Reset o timer
    this->minesSpawnTimer->srsTimer();
}

void MinesControl::loadSprites()
{
    // Go to resources directory
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_append_path_component(path, "resources");
    al_change_directory(al_path_cstr(path, '/'));

    this->mineSprite = std::make_shared<Sprite>("spikebomb.png");
    this->mineExplosionSprite = std::make_shared<Sprite>("explode.png");
    al_destroy_path(path);
}

__END_API