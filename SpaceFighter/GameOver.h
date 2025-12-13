#pragma once
#include "KatanaEngine.h"
using namespace KatanaEngine;

// built mostly off from the main menu header and adjusted it for both vicotry and game over screens.

class GameOverScreen : public MenuScreen
{
public:
    GameOverScreen();
    virtual void LoadContent(ResourceManager& resourceManager);
    virtual void Update(const GameTime& gameTime);
    virtual void Draw(SpriteBatch& spriteBatch);

private:
    Texture* m_pTexture = nullptr;
    Vector2  m_texturePosition;
};
