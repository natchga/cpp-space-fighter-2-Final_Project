#include "BioEnemyShip.h"
#include "Level.h"

BioEnemyShip::BioEnemyShip()
{
    SetSpeed(40);
    SetMaxHitPoints(1);
    SetCollisionRadius(20);
}

void BioEnemyShip::Update(const GameTime& gameTime)
{
    EnemyShip::Update(gameTime);

    if (!IsActive()) return;

    float x = sin(gameTime.GetTotalTime() * Math::PI + GetIndex());
    x *= GetSpeed() * gameTime.GetElapsedTime() * 1.4f;
    TranslatePosition(x, GetSpeed() * gameTime.GetElapsedTime());

    if (!IsOnScreen())
        Deactivate();
}

void BioEnemyShip::Draw(SpriteBatch& spriteBatch)
{
    if (!IsActive()) return;

    const float alpha = GetCurrentLevel()->GetAlpha();
    spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
}
