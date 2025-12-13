/*********************************************
 * By @Emilien 
 ********************************************/

#include "SelectAircraftScreen.h"
#include "GameplayScreen.h"
#include "AircraftType.h"

//Created by @Emilien
SelectAircraftScreen::SelectAircraftScreen()
{
	// Transition effects
	SetTransitionInTime(1.0f);
	SetTransitionOutTime(0.5f);

	Show();
}

void SelectAircraftScreen::LoadContent(ResourceManager& resourceManager)
{

	//Set and Change the font of the menu items on the screen.
	Font::SetLoadSize(20, true);
	Font* pFont = resourceManager.Load<Font>("Fonts\\Ethnocentric.ttf"); 

	const int COUNT = 4; // Initialize the Array to 3 for: Light Fighter, Heavy Bomber, m_pDefault, Quit
	SetDisplayCount(COUNT);
	

	enum Aircraft { LIGHT_FIGHTER, HEAVY_BOMBER, DEFAULT_FIGHTER, QUIT };

	std::string text[COUNT] =
	{
		"Light Fighter  - Fast | Single Shot | Low Stealth",
		"Heavy Bomber   - Slow | Spread Shot | High Stealth",
		"Default",
		"Quit"
	};

	//Menu selected text position
	for (int i = 0; i < COUNT; i++)
	{
		MenuItem* pItem = new MenuItem(text[i]);
		pItem->SetFont(pFont);
		pItem->SetPosition(Vector2(100, 200 + 60 * i));
		//pItem->SetColor(Color::BLUE);
		//pItem->SetSelected(i == 0);

		AddMenuItem(pItem);
	}

	// Light Fighter selected
	GetMenuItem(LIGHT_FIGHTER)->SetOnSelect([this]()
	{
		// @TODO: Store aircraft choice if needed (GameSettings / PlayerData)
		AddScreen(new GameplayScreen(AircraftType::LightFighter));
		Exit();
	});

	// Heavy Bomber selected
	GetMenuItem(HEAVY_BOMBER)->SetOnSelect([this]()
	{
		// @TODO: Store aircraft choice if needed (GameSettings / PlayerData)
		AddScreen(new GameplayScreen(AircraftType::HeavyBomber));
		Exit();
	});

	// Heavy Bomber selected
	GetMenuItem(DEFAULT_FIGHTER)->SetOnSelect([this]()
	{
		// @TODO: Store aircraft choice if needed (GameSettings / PlayerData)
		AddScreen(new GameplayScreen(AircraftType::DefaultFighter));
		Exit();
	});

	// Quit Game selected
	GetMenuItem(QUIT)->SetOnSelect([this]()
	{
		GetGame()->Quit(); // Quit the game
	});


	// ---------- Aircraft Menu preview  ----------
	// Aircraft preview 
	m_pLightFighter = resourceManager.Load<Texture>("Textures\\AircraftPreview\\LightFighterShip.png");
	m_pHeavyBomber = resourceManager.Load<Texture>("Textures\\AircraftPreview\\HeavyBomberShip.png");
	m_pDefaultFighter = resourceManager.Load<Texture>("Textures\\AircraftPreview\\DefaultFighterShip.png");

	// Aircraft's preview: Positionned on the right side of the screen
	m_previewPosition = Vector2(
		Game::GetScreenWidth() - 500, //Position X
		Game::GetScreenCenter().Y + 40 //Position Y
	);

}

void SelectAircraftScreen::Update(const GameTime& gameTime)
{
	//float alpha = GetAlpha(); //Delete
	float offset = sinf(gameTime.GetTotalTime() * 10) * 5 + 5;

	for (MenuItem* pItem : GetMenuItems())
	{
		bool selected = pItem->IsSelected();
		//pItem->SetAlpha(alpha); //Delete
		pItem->SetColor(selected ? Color::YELLOW : Color::TEAL); // Change the color text on the menu ==>Hover over: YELLOW and Text: TEAL
		pItem->SetTextOffset(selected ? Vector2::UNIT_X * offset : Vector2::ZERO); // Add animation on the text
	}
	MenuScreen::Update(gameTime);
}

void SelectAircraftScreen::Draw(SpriteBatch& spriteBatch)
{
	spriteBatch.Begin();

	// Draw selected aircraft preview
	MenuItem* pSelectedItem = nullptr;

	for (MenuItem* pItem : GetMenuItems())
	{
		if (pItem->IsSelected())
		{
			pSelectedItem = pItem;
			break;
		}
	}

	int selectedIndex = 0;
	int index = 0;

	// Find selected menu item index
	for (MenuItem* pItem : GetMenuItems())
	{
		if (pItem->IsSelected())
		{
			selectedIndex = index;
			break;
		}
		index++;
	} 

	//Check which previw to display
	if (selectedIndex == 0)
		pPreview = m_pLightFighter;
	else if (selectedIndex == 1)
		pPreview = m_pHeavyBomber;
	else pPreview = m_pDefaultFighter;

	//Check the Aircraft's preview and display it on the screen
	if (pPreview)
	{
		spriteBatch.Draw(
			pPreview,
			m_previewPosition,
			Color::WHITE * GetAlpha(),
			pPreview->GetCenter()
		);
	}

	// Display the menu (text)
	MenuScreen::Draw(spriteBatch);

	spriteBatch.End();// Display Aircraft Preview
}
