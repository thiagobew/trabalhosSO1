#include "include/MinesControl.h"

__BEGIN_API
// 30 segundos
int MinesControl::DELAY_MINE_SPAWN = GameConfigs::fps * 5;

MinesControl::MinesControl()
{
    this->loadSprites();
    this->_color = al_map_rgb(255, 0, 0);
    this->minesSpawnTimer = std::make_shared<Timer>(GameConfigs::fps);
    this->minesSpawnTimer->create();
    this->minesSpawnTimer->startTimer();
}

MinesControl::~MinesControl() {}

void MinesControl::setWindowReference(Window *window) { this->_window = window; }
void MinesControl::setCollisionReference(Collision *collision) { this->_collision = collision; }
void MinesControl::removeMine(Mine *enemy)
{
    if (this->mines.size() == 0)
        return;

    if (!GameConfigs::finished)
        this->mines.remove(enemy);
    else
        this->mines.clear();
}

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

        // Caso a mina já tenha sido destruída mas não foi removida ainda
        if (mine->isDead() || mine->isOutside())
            continue;

        // Caso a mina já esteja pronta para atacar
        if (mine->canFire())
        {
            // Executa o ataque
            mine->attack();
            for (int i = -500; i <= 500; i += 325)
            {
                for (int j = -500; j <= 500; j += 325)
                {
                    // Cria o tiro a adiciona nas listas
                    Laser *laser = new Laser(mine->getPosition(), this->_color, Vector(i, j), false);
                    this->_collision->addEnemiesShot(laser);
                    this->_window->addDrawableItem(laser);
                }
            }
        }
    }
}

void MinesControl::createMine()
{
    // Gera um ponto aleatório em y para a bomba aparecer
    Point point = Point(0, 0);
    point.rollRandom();
    point.x = GameConfigs::windowWidth;

    // Cria uma mina
    Mine *mine = new Mine(point, Vector(-100, 0), this->mineSprite, this->mineExplosionSprite, this);

    // Adiciona referência dela nas listas
    this->mines.push_back(mine);
    this->_collision->addEnemies(mine);
    this->_window->addDrawableItem(mine);

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