#include "EnemyShipMedium.h"
#include "Level.h"

EnemyShipMedium::EnemyShipMedium()
{
    SetSpeed(120);
    SetMaxHitPoints(2);
    SetCollisionRadius(30);
}

void EnemyShipMedium::Update(const GameTime& gameTime)
{
    if (IsActive())
    {
        float x =
            sin(gameTime.GetTotalTime() * 4 + GetIndex()) * 80.0f *
            gameTime.GetElapsedTime();

        TranslatePosition(
            x,
            GetSpeed() * gameTime.GetElapsedTime()
        );
    }

    EnemyShip::Update(gameTime);
    std::cout << "Medium enemy active\n";
}

void EnemyShipMedium::Draw(SpriteBatch& spriteBatch)
{
    if (IsActive())
    {
        const float alpha = GetCurrentLevel()->GetAlpha();
        spriteBatch.Draw(
            m_pTexture,
            GetPosition(),
            Color::WHITE * alpha,
            m_pTexture->GetCenter()
        );
    }
}
