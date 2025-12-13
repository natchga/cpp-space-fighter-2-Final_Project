/*********************************************
 * By @Emilien
 ********************************************/
#pragma once
#include "KatanaEngine.h"
#include "AircraftType.h"


using namespace KatanaEngine;

/** @brief Screen allowing the player to select an aircraft before the game starts */
class SelectAircraftScreen : public MenuScreen
{
	public:

		/** @brief Constructor */
		SelectAircraftScreen();
		virtual ~SelectAircraftScreen() {}

		/** @brief Load screen content */
		virtual void LoadContent(ResourceManager& resourceManager) override;

		/** @brief Update screen logic */
		virtual void Update(const GameTime& gameTime) override;

		/** @brief Draw screen */
		virtual void Draw(SpriteBatch& spriteBatch) override;

	private:

		Texture* m_pTitleTexture = nullptr;

		//Aircraft
		Texture* m_pLightFighter = nullptr;
		Texture* m_pHeavyBomber = nullptr;
		Texture* m_pDefaultFighter = nullptr;
		//Aircraft preview
		Texture* pPreview = nullptr;

		//Position
		Vector2 m_titlePosition;
		Vector2 m_previewPosition;


};
