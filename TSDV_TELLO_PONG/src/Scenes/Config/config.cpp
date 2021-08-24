#include "config.h"
#include "Extern Vars/Button/button.h"
#include <string>

const int howManyButtons = 2;
const int spaceBetweenButtons = 10;

namespace pong {

	namespace configScreen {

		using namespace elements;
		
		Vector2 mousePos;

		Button* buttons[howManyButtons];

		void init() 
		{
			LoadAudio();

			std::string btn_text[howManyButtons] = { "Jugar","Volver Al Menu" };
			buttons::Selector btn_type[howManyButtons] = { buttons::Selector::GAME, buttons::Selector::MENU };

			for (short i = 0; i < howManyButtons; i++)
			{
				buttons[i] = new Button();
				buttons[i]->MakeStandardButton();
				buttons[i]->SetText(btn_text[i]);
				buttons[i]->SetButtonType(btn_type[i]);
				buttons[i]->SetButtonPosition({ buttons[i]->GetButtonPosition().x,(buttons[i]->GetButtonSize().y + spaceBetweenButtons) *i});
			}

		}
		void update() 
		{
			mousePos = GetMousePosition();
			if (playMusic)
			{
				UpdateMusicStream(configMusic);
			}
			
			CheckButtons();

		}
		void draw() 
		{

			for (short i = 0; i < howManyButtons; i++)
			{
				if (buttons[i]) 
				{
					buttons[i]->Draw();
				}
			}

		}
		void deinit() 
		{
			UnloadSound(buttonBeep);
			UnloadMusicStream(configMusic);

			for (short i = 0; i < howManyButtons; i++)
			{
				if (buttons[i])
				{
					buttons[i]->UnloadTx();
					buttons[i] = NULL;
					delete buttons[i];
				}
			}

		}
		void LoadAudio()
		{
			configMusic = LoadMusicStream("res/assets/Music/config.mp3");
			PlayMusicStream(configMusic);
			SetMusicVolume(configMusic, 0.1f);

			buttonBeep = LoadSound("res/assets/Sounds/buttonClic.ogg");
			SetSoundVolume(buttonBeep, 0.3f);
		}
		
		void CheckButtons()
		{
			
			for (short i = 0; i < howManyButtons; i++)
			{
				if (CheckCollisionPointRec(mousePos, buttons[i]->GetRec()))
				{
					if (!buttons[i]->isHovered())
					{
						if (playSounds)
						{
							PlaySound(buttonBeep);
						}
						buttons[i]->Hover();
					}
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
					{
						switch (buttons[i]->GetButtonType())
						{
						case pong::elements::buttons::Selector::MENU:
							config::scenes::next_scene = config::scenes::Scene::MENU;
							break;
						case pong::elements::buttons::Selector::GAME:
							config::scenes::next_scene = config::scenes::Scene::GAME;
							break;
						default:
							break;
						}
					}
				}
				else
				{
					if (buttons[i]->isHovered())
					{
						buttons[i]->UnHover();
					}
				}
			}
			
		}
		

	}

}