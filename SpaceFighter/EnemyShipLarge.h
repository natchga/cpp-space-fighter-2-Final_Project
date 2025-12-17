#pragma once
#include "EnemyShip.h"

class EnemyShipLarge : public EnemyShip
{
public:
    EnemyShipLarge();

    virtual void Update(const GameTime& gameTime) override;
    virtual void Draw(SpriteBatch& spriteBatch) override;
    virtual void Hit(const float damage) override;

    void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

private:
    Texture* m_pTexture = nullptr;
};
