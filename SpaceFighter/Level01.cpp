
#include "Level01.h"
#include "BioEnemyShip.h"
#include "EnemyShipMedium.h"



Level01::Level01(AircraftType type) : Level(type) {}

void Level01::LoadContent(ResourceManager& resourceManager)
{
    // bio/small enemies
    Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

    const int COUNT = 5; 
    SetTotalEnemiesToSpawn(COUNT);

    float delay = 3.0f;


    float xPositions[COUNT] = { 300.0f, 400.0f, 500.0f, 600.0f, 700.0f };

    for (int i = 0; i < COUNT; i++)
    {
        delay += 0.25f; 
        Vector2 position(xPositions[i], -pTexture->GetCenter().Y);

        BioEnemyShip* pEnemy = new BioEnemyShip();
        pEnemy->SetTexture(pTexture);
        pEnemy->SetCurrentLevel(this);
        pEnemy->Initialize(position, delay); 
        AddGameObject(pEnemy);
    }

    // Medium Enemies
    Texture* pMediumTex = resourceManager.Load<Texture>("Textures\\EnemyShipMedium.png");

    float mediumXPositions[4] = { 350.0f, 450.0f, 550.0f, 650.0f };

    for (int i = 0; i < 4; i++)
    {
        float enemyDelay = 8.0f + i;
        Vector2 pos(mediumXPositions[i], -pMediumTex->GetCenter().Y);

        Vector2 position(700.0f, -pTexture->GetCenter().Y);
        BioEnemyShip* pEnemy = new BioEnemyShip();
        pEnemy->SetTexture(pTexture);
        pEnemy->SetCurrentLevel(this);
        pEnemy->Initialize(position, delay);
        AddGameObject(pEnemy);
    }

    // Background
    SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground01.png"));

    Level::LoadContent(resourceManager);
}

