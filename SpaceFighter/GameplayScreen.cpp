
#include "GameplayScreen.h"
#include "MainMenuScreen.h"
#include "Level.h"
#include "Level01.h"
#include "PlayerShip.h"  
#include "Blaster.h"     
#include "Projectile.h"     
#include "GameOver.h"
#include "Victory.h"
#include "Score.h"




GameplayScreen::GameplayScreen(AircraftType aircraftType)
    : m_levelIndex(0),
    m_pLevel(nullptr),
    m_pResourceManager(nullptr),
    m_aircraftType(aircraftType)
{
	SetTransitionInTime(1);
	SetTransitionOutTime(3);

	SetOnRemove([this](){ AddScreen(new MainMenuScreen()); });

	Show();
}

void GameplayScreen::LoadContent(ResourceManager& resourceManager)
{
	m_pResourceManager = &resourceManager;
	LoadLevel(m_levelIndex);
}

void GameplayScreen::LoadLevel(const int levelIndex)
{
	if (m_pLevel) delete m_pLevel;

	switch (levelIndex)
	{
	case 0: m_pLevel = new Level01(); break;
	}

	m_pLevel->SetGameplayScreen(this);
	m_pLevel->LoadContent(*m_pResourceManager);
}

void GameplayScreen::HandleInput(const InputState& input)
{
	m_pLevel->HandleInput(input);
}

void GameplayScreen::Update(const GameTime& gameTime) // updated the update to see if the game is over or a victory -- tommy
{

    m_pLevel->Update(gameTime);

    if (m_gameEnded)
        return;

    PlayerShip* pPlayer = m_pLevel->GetPlayerShip();

    // gives us a gameover screen oncce done.
    if (pPlayer && !pPlayer->IsActive())
    {
        m_gameEnded = true;

        SetOnRemove([this]()
            {
                AddScreen(new GameOverScreen());
            });

        Exit();
        return;
    }

    // gives us a victory screen once done.
    if (m_pLevel->IsComplete())
    {
        m_gameEnded = true; 

        SetOnRemove([this]()
            {
                AddScreen(new VictoryScreen());
            });

        Exit();
        return;
    }
}



void GameplayScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	m_pLevel->Draw(spriteBatch);

	spriteBatch.End();
}
