#include "config.h"
#include "Extern Vars/Button/button.h"
#include "Extern Vars/area.h"
#include <string>

const int howManyButtons = 2;
const int spaceBetweenButtons = 10;

namespace pong {

	int pointLimit = 5;

	namespace configScreen {

		using namespace elements;
		
		Vector2 mousePos;

		Button* buttons[howManyButtons];

		Area areaOptions = Area();
		Area areaMenu = Area();
		Area areaP1 = Area();
		Area areaP2 = Area();
		Area areaGame = Area();

		void Init() 
		{
			
			LoadAudio();

			InitAreas();

			std::string btn_text[howManyButtons] = { "Start","Back" };
			buttons::Selector btn_type[howManyButtons] = { buttons::Selector::GAME, buttons::Selector::MENU };
			
			for (short i = 0; i < howManyButtons; i++)
			{
				buttons[i] = new Button();
				buttons[i]->MakeStandardButton();
				buttons[i]->SetText(btn_text[i]);
				buttons[i]->SetButtonType(btn_type[i]);
				buttons[i]->SetButtonPosition(Vec2(areaMenu.GetPos().x + areaMenu.GetDim().x * (3 - (2 * i)) / 4 - buttons[i]->GetButtonSize().x / 2, areaMenu.GetPos().y + areaMenu.GetDim().y / 2 - buttons[i]->GetButtonSize().y / 2));
			}
			
		}
		void Update() 
		{
			mousePos = GetMousePosition();
			if (playMusic)
			{
				UpdateMusicStream(configMusic);
			}
			
			CheckButtons();

		}
		void Draw() 
		{

			DrawAreas();

			for (short i = 0; i < howManyButtons; i++)
			{
				if (buttons[i]) 
				{
					buttons[i]->Draw();
				}
			}


		}
		void Deinit() 
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
		void InitAreas()
		{
			areaGame.SetDim(config::screen::width, config::screen::height * 35 / 40);
			areaGame.SetColor(BLUE);
			areaP1.SetDim(areaGame.GetRec().width / 3, areaGame.GetRec().height);
			areaP1.SetColor(RED);
			areaOptions.SetDim(areaP1.GetDim());
			areaOptions.SetPos(areaP1.GetPos().x + areaP1.GetDim().x, areaP2.GetPos().y);
			areaOptions.SetColor(GREEN);
			areaP2.SetDim(areaP1.GetDim());
			areaP2.SetPos(areaOptions.GetPos().x + areaOptions.GetDim().x, areaP2.GetPos().y);
			areaP2.SetColor(YELLOW);
			areaMenu.SetDim(areaP1.GetDim().x, config::screen::height - areaGame.GetDim().y);
			areaMenu.SetPos(areaP2.GetPos().x, areaP2.GetPos().y + areaP2.GetDim().y);
			areaMenu.SetColor(BLACK);

		}
		void DrawAreas()
		{
			areaGame.DrawAreaTransparentWithLines();
			areaP1.DrawAreaTransparentWithLines();
			areaOptions.DrawAreaTransparentWithLines();
			areaP2.DrawAreaTransparentWithLines();
			areaMenu.DrawAreaTransparentWithLines();
		}
		void CheckButtons()
		{
			Rectangle clickDown = Rectangle();
			Rectangle clickUp = Rectangle();
			for (short i = 0; i < howManyButtons; i++)
			{
				if (CheckCollisionPointRec(mousePos, buttons[i]->GetRec()))
				{
					if (!buttons[i]->IsHovered())
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
							config::scenes::next_scene = config::scenes::SCENE::MENU;
							break;
						case pong::elements::buttons::Selector::GAME:
							config::scenes::next_scene = config::scenes::SCENE::GAME;
							break;
						default:
							break;
						}
					}
				}
				else
				{
					if (buttons[i]->IsHovered())
					{
						buttons[i]->UnHover();
					}
				}
			}
			
		}
		

	}

}