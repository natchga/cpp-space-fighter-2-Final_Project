#pragma once
#include "EnemyShip.h"

class EnemyShipMedium : public EnemyShip
{
public:
    EnemyShipMedium();
    virtual void Update(const GameTime& gameTime);
    virtual void Draw(SpriteBatch& spriteBatch);

    void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }

private:
    Texture* m_pTexture = nullptr;
};
