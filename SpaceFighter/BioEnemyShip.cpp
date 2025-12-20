#include "BioEnemyShip.h"
#include "Level.h"

BioEnemyShip::BioEnemyShip()
{
    SetSpeed(150);
    SetMaxHitPoints(1);
    SetCollisionRadius(20);
}

void BioEnemyShip::Update(const GameTime& gameTime)
{
    EnemyShip::Update(gameTime);
    if (!IsActive()) return;

    float dy = GetSpeed() * gameTime.GetElapsedTime();

    float wave =
        sin(gameTime.GetTotalTime() * Math::PI + GetIndex()) * 40.0f;

    Vector2 pos = GetPosition();
    pos.Y += dy;
    pos.X = m_spawnX + wave;

    SetPosition(pos);

    if (!IsOnScreen())
        Deactivate();
}

void BioEnemyShip::Draw(SpriteBatch& spriteBatch)
{
    if (!IsActive()) return;

    const float alpha = GetCurrentLevel()->GetAlpha();
    spriteBatch.Draw(m_pTexture, GetPosition(), Color::WHITE * alpha, m_pTexture->GetCenter(), Vector2::ONE, Math::PI, 1);
}

void BioEnemyShip::Initialize(const Vector2 position, const double delaySeconds)
{
    m_spawnX = position.X;
    EnemyShip::Initialize(position, delaySeconds);
}
