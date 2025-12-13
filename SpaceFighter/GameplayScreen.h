
#pragma once

#include "KatanaEngine.h"
#include "AircraftType.h"
#include "Level.h"
#include "Projectile.h" 


using namespace KatanaEngine;

class Level;

/** @brief The gameplay screen for the Space Fighter Game.
	It is responsible for creating and loading levels.
	@see Level
	@see Screen
*/
class GameplayScreen : public Screen
{

public:

	// Constructors

	/** @brief Instantiate a gameplay screen object.
		@param levelIndex The index of the level to load. */

	//GameplayScreen(const int levelIndex = 0);
	GameplayScreen(AircraftType aircraftType);

	virtual ~GameplayScreen() {}

	// Screen methods

	/** @brief Load the content for the screen.
		@param resourceManager A reference to the game's resource manager. */
	virtual void LoadContent(ResourceManager& resourceManager) ;

	/** @brief Handle input for the screen.
		@param input The current state of all player input devices. */
	virtual void HandleInput(const InputState& input);

	/** @brief Update the screen.
		@param gameTime A reference to the game time object. */
	virtual void Update(const GameTime& gameTime);

	/** @brief Render the screen.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch);

	/** @brief Load a specific level.
		@param levelIndex The index of the level to load. */
	virtual void LoadLevel(const int levelIndex);


private:

	bool m_gameEnded = false; // checks to see if the game is over. - Tommy

	int m_levelIndex = 0;

	Level *m_pLevel = nullptr;

	ResourceManager *m_pResourceManager = nullptr;

	/*Added by @Emilien*/
	AircraftType m_aircraftType;
	bool m_useAircraftType = false; // Flag to know which constructor was used
};
