#include "EnemyShipLarge.h"
#include "Level.h"
#include "PlayerShip.h"
#include <iostream>

EnemyShipLarge::EnemyShipLarge()
{
    SetSpeed(40);
    SetMaxHitPoints(10);
    SetCollisionRadius(60);
}

void EnemyShipLarge::Update(const GameTime& gameTime)
{
    EnemyShip::Update(gameTime);

    if (!IsActive())
    {
        std::cout << "Boss waiting to activate\n";
        return;
    }

    PlayerShip* pPlayer = GetCurrentLevel()->GetPlayerShip();
    if (!pPlayer)
        return;

    Vector2 direction = pPlayer->GetPosition() - GetPosition();

    if (direction.LengthSquared() > 0.001f)
        direction.Normalize();

    TranslatePosition(
        direction.X * GetSpeed() * gameTime.GetElapsedTime(),
        GetSpeed() * gameTime.GetElapsedTime()
    );
}

void EnemyShipLarge::Draw(SpriteBatch& spriteBatch)
{
    if (!IsActive())
        return;

    const float alpha = GetCurrentLevel()->GetAlpha();

    spriteBatch.Draw(
        m_pTexture,
        GetPosition(),
        Color::WHITE * alpha,
        m_pTexture->GetCenter()
    );
    std::cout << "Boss draw at Y=" << GetPosition().Y << '\n';

}

void EnemyShipLarge::Hit(const float damage)
{
    EnemyShip::Hit(damage);

    if (!IsActive())
    {
        GetCurrentLevel()->m_bossAlive = false;
        std::cout << "Boss destroyed\n";
    }
}
