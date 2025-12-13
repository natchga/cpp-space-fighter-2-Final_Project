#include "Victory.h"
#include "MainMenuScreen.h"
#include "SelectAircraftScreen.h"
#include "Score.h"

// built off mostly the mainmenu screen. Victory and Game Over are basically the same screen just with different triggers and background images.

VictoryScreen::VictoryScreen()
{
    SetTransitionInTime(1);
    SetTransitionOutTime(0.5f);
    Show();
}

void VictoryScreen::LoadContent(ResourceManager& resourceManager)
{
    // Background image (change to .png if you exported png)
    m_pTexture = resourceManager.Load<Texture>("Textures\\victory.jpg");
    m_texturePosition = Game::GetScreenCenter();

    const int COUNT = 2;              
    SetDisplayCount(COUNT + 1);       // show restart , menu and score.


    Font::SetLoadSize(20, true);
    Font* pFont = resourceManager.Load<Font>("Fonts\\arial.ttf");

    enum Items { RESTART, MAIN_MENU };
    std::string text[COUNT] = { "Restart", "Main Menu" };

    for (int i = 0; i < COUNT; i++)
    {
        MenuItem* pItem = new MenuItem(text[i]);
        pItem->SetPosition(Vector2(100, 100 + 50 * i));
        pItem->SetFont(pFont);
        pItem->SetColor(Color::BLUE);
        pItem->SetSelected(i == 0);
        AddMenuItem(pItem);
    }

    // shows the player score 
    MenuItem* pScore = new MenuItem(
        "Score (enemies destroyed): " + std::to_string(ScoreSystem::GetEnemyDestroyed())
    );
    pScore->SetPosition(Vector2(100, 250));
    pScore->SetFont(pFont);
    pScore->SetColor(Color::WHITE);
    AddMenuItem(pScore);

    GetMenuItem(RESTART)->SetOnSelect([this]() {
        SetOnRemove([this]() {
            ScoreSystem::Reset(); // resets the score, when player hits restart
            AddScreen(new SelectAircraftScreen());
            });
        Exit();
        });

    GetMenuItem(MAIN_MENU)->SetOnSelect([this]() {
        SetOnRemove([this]() {
            ScoreSystem::Reset(); // resets the score once the player hits mainmenu
            AddScreen(new MainMenuScreen());
            });
        Exit();
        });
}

void VictoryScreen::Update(const GameTime& gameTime)
{
    float alpha = GetAlpha();
    float offset = sinf(gameTime.GetTotalTime() * 10) * 5 + 5;

    int index = 0;
    for (MenuItem* pItem : GetMenuItems())
    {
        pItem->SetAlpha(alpha);

        if (index < 2) // Restart + Main Menu
        {
            bool isSelected = pItem->IsSelected();
            pItem->SetColor(isSelected ? Color::WHITE : Color::BLUE);
            pItem->SetTextOffset(isSelected ? Vector2::UNIT_X * offset : Vector2::ZERO);
        }
        else // Score label
        {
            // If score ever becomes selected, force selection back to Restart
            if (pItem->IsSelected())
            {
                pItem->SetSelected(false);
                GetMenuItem(0)->SetSelected(true); // Restart
            }

            pItem->SetColor(Color::WHITE);
            pItem->SetTextOffset(Vector2::ZERO);
        }

        index++;
    }

    MenuScreen::Update(gameTime);
}


void VictoryScreen::Draw(SpriteBatch& spriteBatch)
{
    spriteBatch.Begin();
    spriteBatch.Draw(m_pTexture, m_texturePosition, Color::WHITE * GetAlpha(), m_pTexture->GetCenter());
    MenuScreen::Draw(spriteBatch);
    spriteBatch.End();
}


