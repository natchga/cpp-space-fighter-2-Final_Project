#include "Level02.h"
#include "BioEnemyShip.h"
#include "EnemyShipMedium.h"
#include "EnemyShipLarge.h"
#include "PlayerShip.h"
#include <iostream>

Level02::Level02(AircraftType aircraftType)
    : Level(aircraftType)
{
}

void Level02::LoadContent(ResourceManager& resourceManager)
{
    std::cout << "[Level02] LoadContent started.\n";

    m_hasHadActiveEnemy = false;
    m_bossAlive = true;

    // Small/Bio Enemies
    Texture* pBioTex = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");
    float delay = 0.0f;

    const int BIO_COUNT = 22;
    for (int i = 0; i < BIO_COUNT; i++)
    {
        delay += 0.25f;
        Vector2 position(0.25f * Game::GetScreenWidth(), -pBioTex->GetCenter().Y);

        BioEnemyShip* pEnemy = new BioEnemyShip();
        pEnemy->SetTexture(pBioTex);
        pEnemy->SetCurrentLevel(this);
        pEnemy->Initialize(position, delay);
        AddGameObject(pEnemy);
    }

    // Medium Enemies
    Texture* pMediumTex = resourceManager.Load<Texture>("Textures\\EnemyShipMedium.png");
    for (int i = 0; i < 5; i++)
    {
        float enemyDelay = 4.0f + i;
        EnemyShipMedium* pMedium = new EnemyShipMedium();
        pMedium->SetTexture(pMediumTex);
        pMedium->SetCurrentLevel(this);
        pMedium->Initialize(Vector2(200 + i * 120, -50), enemyDelay);
        AddGameObject(pMedium);
    }

    // Boss / Large Enemy
    Texture* pBossTex = resourceManager.Load<Texture>("Textures\\BioEnemyBoss.png");
    EnemyShipLarge* pBoss = new EnemyShipLarge();
    pBoss->SetTexture(pBossTex);
    pBoss->SetCurrentLevel(this);
    pBoss->Initialize(Vector2(Game::GetScreenWidth() / 2, pBossTex->GetCenter().Y + 40), 0.0f);
    pBoss->Activate();
    AddGameObject(pBoss);

    SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground02.png"));

    std::cout << "[Level02] LoadContent finished.\n";

    Level::LoadContent(resourceManager);
}

void Level02::Update(const GameTime& gameTime)
{
    Level::Update(gameTime);
    CheckEnemies();
}

void Level02::CheckEnemies()
{
    bool hasActiveEnemy = false;
    bool bossAlive = false;

    for (GameObject* obj : GetGameObjects())
    {
        if (!obj->IsActive()) continue;

        if (obj->HasMask(CollisionType::Enemy))
        {
            hasActiveEnemy = true;
        }

        if (dynamic_cast<EnemyShipLarge*>(obj) && obj->IsActive())
        {
            bossAlive = true;
        }
    }

    m_hasHadActiveEnemy = m_hasHadActiveEnemy || hasActiveEnemy;
    m_bossAlive = bossAlive;
}

bool Level02::IsComplete() const
{
    // Level is complete only if at least one enemy appeared AND boss is dead
    return m_hasHadActiveEnemy && !m_bossAlive;
}
