#include "Level02.h"
#include "BioEnemyShip.h"
#include "EnemyShipMedium.h"
#include "EnemyShipLarge.h"

Level02::Level02(AircraftType type) : Level(type) {}

void Level02::LoadContent(ResourceManager& resourceManager)
{
    m_bossAlive = true;

    // small bio enemies
    Texture* pTexture =
        resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

    const int COUNT = 22;
    float delay = 3.0f;
    Vector2 position;

    for (int i = 0; i < COUNT; i++)
    {
        delay += 0.25f;

        position.Set(
            0.25f * Game::GetScreenWidth(),
            -pTexture->GetCenter().Y
        );

        BioEnemyShip* pEnemy = new BioEnemyShip();
        pEnemy->SetTexture(pTexture);
        pEnemy->SetCurrentLevel(this);
        pEnemy->Initialize(position, delay);
        AddGameObject(pEnemy);
    }

    // medium enemies
    Texture* pMediumTex =
        resourceManager.Load<Texture>("Textures\\EnemyShipMedium.png");

    for (int i = 0; i < 5; i++)
    {
        EnemyShipMedium* pMedium = new EnemyShipMedium();
        pMedium->SetTexture(pMediumTex);
        pMedium->SetCurrentLevel(this);
        pMedium->Initialize(
            Vector2(200 + i * 120, -50),
            4.0f + i
        );
        AddGameObject(pMedium);
    }

    // boss enemy
    Texture* pBossTex =
        resourceManager.Load<Texture>("Textures\\BioEnemyBoss.png");

    EnemyShipLarge* pBoss = new EnemyShipLarge();
    pBoss->SetTexture(pBossTex);
    pBoss->SetCurrentLevel(this);

    pBoss->Initialize(
        Vector2(
            Game::GetScreenWidth() / 2,
            pBossTex->GetCenter().Y + 40
        ),
        0.0f
    );

    pBoss->Activate();
    AddGameObject(pBoss);

    Level::LoadContent(resourceManager);
}

