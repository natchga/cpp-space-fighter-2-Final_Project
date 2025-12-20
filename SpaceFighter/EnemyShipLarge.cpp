#include "EnemyShipLarge.h"
#include "Level.h"
#include "PlayerShip.h"

EnemyShipLarge::EnemyShipLarge()
{
    SetSpeed(40);
    SetMaxHitPoints(50);
    SetCollisionRadius(60);
}

void EnemyShipLarge::Update(const GameTime& gameTime)
{
    if (!IsActive())
    {
        EnemyShip::Update(gameTime);
        return;
    }

    PlayerShip* pPlayer = GetCurrentLevel()->GetPlayerShip();
    if (pPlayer)
    {
        Vector2 direction = pPlayer->GetPosition() - GetPosition();
        if (direction.LengthSquared() > 0.001f)
            direction.Normalize();

        TranslatePosition(direction.X * GetSpeed() * gameTime.GetElapsedTime(),
            GetSpeed() * gameTime.GetElapsedTime());
    }

    EnemyShip::Update(gameTime);
}

void EnemyShipLarge::Draw(SpriteBatch& spriteBatch)
{
    if (!IsActive()) return;

    const float alpha = GetCurrentLevel()->GetAlpha();
    spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter());
}

void EnemyShipLarge::Hit(float damage)
{
    EnemyShip::Hit(damage);

    if (GetHitPoints() <= 0)
    {
        Deactivate();
        if (Level* level = GetCurrentLevel())
            level->m_bossAlive = false;
    }
}
