#include "menu.h"
#include <iostream> 
#include <string>

namespace pong {

	namespace menu {

		const int timeToShowLetters = 3;

		bool continueInGame = true;
		bool playedButtonSound = false;
		bool stTimeLoop;

		int time;
		float timer;

		Buttons buttons[howManyButtons];
		Vector2 mousePoint = {0,0};

		int hoveredOption = 0;
		int hoveredOptionPast = 0;

		Color background;
		Texture2D bgTexture;


		void init() {

			bgTexture = LoadTexture("res/assets/Backgrounds/BG.png");
			bgTexture.width = config::screen::width;
			bgTexture.height = config::screen::height;

			//Music
			menuMusic = LoadMusicStream("res/assets/Music/menu.mp3");
			PlayMusicStream(menuMusic);
			SetMusicVolume(menuMusic, 0.1f);

			stTimeLoop = true;

			buttonBeep = LoadSound("res/assets/Sounds/buttonClic.ogg");
			SetSoundVolume(buttonBeep, 0.3f);

			title[1].tx = "PONG";

			for (short i = 0; i < titleLenght; i++)
			{
				title[i].size = config::screen::height / 13;
				title[i].pos.x = config::screen::width / 2 - MeasureTextEx(font, &title[i].tx[0], title->size, 1).x / 2;
				title[i].pos.y = config::screen::height * (2 + i) / 13 + 5 * i;
				title[i].color = getRandomColor(200,255);

			}

			background = getRandomColor(170,255);

			for (short i = 0; i < howManyButtons; i++) {

				Buttons btn;
				std::string text;

				switch ((config::scenes::Scene)(i+1)) {

				case config::scenes::Scene::CONFIG:
					text = "PLAY";
					break;
				case config::scenes::Scene::CREDITS:
					text = "CREDITS";
					break;
				case config::scenes::Scene::QUIT:
					text = "EXIT";
					break;

				}

				btn.txt.tx = text;

				btn.square.width = (float)MeasureTextEx(font, &btn.txt.tx[0], baseTextHeight, 1).x;
				btn.square.height = (float)baseTextHeight;
				btn.square.x = (float)(config::screen::width / 2 - MeasureTextEx(font,&btn.txt.tx[0], btn.square.height,1).x/2);
				btn.square.y = config::screen::height * 19 / 40 + config::screen::height * i * 2 / 25;

				btn.color = BLACK;

				buttons[i] = btn;

			}

		}

		void update() 
		{

			time++;
			timer += GetFrameTime();

			if (stTimeLoop) 
			{
				mousePoint = { 0,0 };
				stTimeLoop = false;
			}
			else 
			{
				mousePoint = GetMousePosition();
			}

			if (playMusic)
			{
				UpdateMusicStream(menuMusic);
			}

			for (int i = 0; i < howManyButtons; i++) 
			{

				if (CheckCollisionPointRec(menu::mousePoint, buttons[i].square)) 
				{

					if (!buttons[i].selected) 
					{

						if (playSounds)
						{
							PlaySound(buttonBeep);
						}
						buttons[i].selected = true;

					}

					if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
					{

						config::scenes::next_scene = static_cast<config::scenes::Scene>(i + 1);

					}

				}
				else 
				{
					buttons[i].selected = false;
				}

			}

		}

		void draw() 
		{

			Color color;

			DrawTexture(bgTexture, 0, 0, background);

			for (short i = 0; i < titleLenght; i++) 
			{
				DrawTextEx(font, &title[i].tx[0], title[i].pos.ToVector2(), title->size, 1, title[i].color);
			}

			for (short i = 0; i < howManyButtons; i++) 
			{
				Buttons btn = buttons[i];
				int heightCorrect = btn.square.height;

				if (btn.selected) 
				{
					color = LIME;
					btn.square.height *= plusSelected;
					btn.square.width = MeasureTextEx(font,&btn.txt.tx[0], baseTextHeight, spacing).x;
					btn.square.x = config::screen::width / 2 - MeasureTextEx(font, &btn.txt.tx[0], btn.square.height, spacing).x / 2;
					btn.square.y = config::screen::height * 19 / 40 + config::screen::height * i * 2 / 25 - (btn.square.height - heightCorrect) / 2;
					//                      BASE                   +                VARIACION           - DIFERENCIA ENTRE LETRA GRANDE Y CHICA
				}
				else 
				{
					color = btn.color;
				}

				DrawTextEx(font, &(btn.txt.tx)[0], { btn.square.x, btn.square.y }, btn.square.height, 1, color);

				//btn.drawButton();

			}

		}

		void deinit() 
		{
			UnloadTexture(bgTexture);
			UnloadSound(buttonBeep);
			UnloadMusicStream(menuMusic);
		}


	}

}