#include "credits.h"

namespace pong {

	namespace credits {


		const float toAugment = 1.3f;
		const float toDisminish = 10 / 13;
		const int howManyCreditLines = 4;
		const int textSize = 30;
		const int textPadding = 30;

		const int buttonSize = 60;

		Text credits[howManyCreditLines];

		TextureInfo background;
		Buttons buttonExit;

		Vector2 mousePos;		

		void Init()
		{
			string lines[howManyCreditLines] =
			{
				"Programmer:  Guido Tello",
				"Textures by:  CRAFTPIX.NET",
				"Music:  Fiesta Online OST",
				    "Created Using Raylib"
			};

			for (short i = 0; i < howManyCreditLines; i++)
			{
				credits[i].tx = lines[i];
				credits[i].size = textSize;
				credits[i].color = WHITE;
				credits[i].pos.x = config::screen::width * 2 / 7;
				credits[i].pos.y = config::screen::height * 1 / 5 + textPadding*i + i *  MeasureTextEx(font, &credits[i].tx[0], textSize, 1).y;
			}
			credits[3].pos.x = config::screen::width / 2 - MeasureTextEx(font, &credits[3].tx[0], textSize, 1).x / 2;

			creditMusic = LoadMusicStream("res/assets/Music/credits.mp3");
			PlayMusicStream(creditMusic);
			SetMusicVolume(creditMusic, 0.1f);

			buttonBeep = LoadSound("res/assets/Sounds/buttonClic.ogg");
			SetSoundVolume(buttonBeep, 0.3f);

			background.texture = LoadTexture("res/assets/Backgrounds/BG.png");
			buttonExit.texture.texture = LoadTexture("res/assets/Buttons/CloseButton.png");

			background.texture.height = config::screen::height;
			background.texture.width = config::screen::width;

			buttonExit.texture.texture.width = buttonSize;
			buttonExit.texture.texture.height = buttonSize;
			buttonExit.square.width = buttonSize;
			buttonExit.square.height = buttonSize;

			buttonExit.selected = false;
			buttonExit.clicked = false;
		}
		void Update()
		{
			mousePos = GetMousePosition();

			if (playMusic)
			{
				UpdateMusicStream(creditMusic);
			}
			if (CheckCollisionPointRec(mousePos, buttonExit.square)) 
			{
				
				if (!buttonExit.selected)
				{
					buttonExit.scale = plusSelected;

					if (playSounds)
					{
						PlaySound(buttonBeep);
					}
				}
				buttonExit.selected = true;
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					buttonExit.clicked = true;
				}
				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
				{
					config::scenes::next_scene = config::scenes::SCENE::MENU;
					
				}
			}
			else
			{
				buttonExit.scale = nonSelected;
				buttonExit.selected = false;
			}
		}

		void Draw()
		{

			DrawTexture(background.texture, 0, 0, WHITE);
			if (buttonExit.clicked)
			{
				DrawTextureEx(buttonExit.texture.texture, { 0,0 }, 0, buttonExit.scale, BROWN);
			}
			else
			{
				DrawTextureEx(buttonExit.texture.texture, { 0,0 }, 0, buttonExit.scale, WHITE);
			}

			for (short i = 0; i < howManyCreditLines; i++)
			{
				DrawTextEx(font, &credits[i].tx[0], credits[i].pos.ToVector2(), credits[i].size, 1, credits[i].color);
			}

		}

		void Deinit()
		{
			UnloadTexture(background.texture);
			UnloadTexture(buttonExit.texture.texture);
			UnloadSound(buttonBeep);
			UnloadMusicStream(creditMusic);
		}

	}

}