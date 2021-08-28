#include "extern.h"

namespace pong {

	Font font;
	Font scoreFont;

	Buttons music;
	Buttons sound;

	bool playMusic = true;
	bool playSounds = true;

	Color backgroundColor;

	Color CreateColor(Vector4 v)
	{
		Color aux;
		aux.r = v.x;
		aux.g = v.y;
		aux.b = v.z;
		aux.a = v.w;
		return aux;
	}
	Color CreateColor(Vector3 v) 
	{
		Color aux;
		aux.r = v.x;
		aux.g = v.y;
		aux.b = v.z;
		return aux;
	}
	Color CreateColor(int r, int g, int b, int a)
	{
		Color aux;
		aux.r = r;
		aux.g = g;
		aux.b = b;
		aux.a = a;
		return aux;
	}
	Color CreateColor(int r, int g, int b)
	{
		Color aux;
		aux.r = r;
		aux.g = g;
		aux.b = b;
		return aux;
	}

	Text::Text()
	{
		tx = "";
		pos = Vec2();
		size = fontSize;
		color = BLACK;
	}
	Letter::Letter()
	{
		text = Text();
		pos = Vec2();
		width = 0;
		height = 0;
		paddingX = 5;
		paddingY = 1;
		backgroundColor = BLACK;
		frameColor = WHITE;
		frameWidth = 3;
	}
	void Letter::CenterText()
	{
		text.pos.x = pos.x + width / 2 - MeasureTextEx(scoreFont, &text.tx[0], fontSize, spacing).x / 2;
		text.pos.y = pos.y + height / 2 - MeasureTextEx(scoreFont, &text.tx[0], fontSize, spacing).y / 2;
	}
	
	Rectangle Letter::GetRec() 
	{
		Rectangle aux;
		aux.x = pos.x;
		aux.y = pos.y;
		aux.width = width;
		aux.height = height;
		return aux;
	}

	void Letter::Init(std::string txt)
	{
		text.tx = txt;
		width = paddingX * 2 + MeasureTextEx(scoreFont, &txt[0], fontSize, spacing).x;
		height = paddingY * 2 + MeasureTextEx(scoreFont, &txt[0], fontSize, spacing).y;
	}

	void Letter::Draw()
	{
		DrawRectangleRec(GetRec(), backgroundColor);
		DrawRectangleLinesEx(GetRec(), frameWidth, frameColor);
		CenterText();
		DrawTextEx(scoreFont, &text.tx[0], text.pos.ToVector2(), fontSize, spacing, text.color);
	}

	void InitAudioButtons()
	{
		music.texture.texture = LoadTexture("res/assets/Buttons/music.png");
		music.color = WHITE;
		music.texture.texture.width = config::general::buttonSize;
		music.texture.texture.height = config::general::buttonSize;
		music.square.x = config::general::buttonPadding;
		music.square.y = config::screen::height - music.texture.texture.height * config::general::toAugment;
		music.square.width = music.texture.texture.width;
		music.square.height = music.texture.texture.height;
		
		
		sound.texture.texture = LoadTexture("res/assets/Buttons/sound.png");
		sound.color = WHITE;
		sound.texture.texture.width = config::general::buttonSize;
		sound.texture.texture.height = config::general::buttonSize;
		sound.square.x = config::general::buttonPadding + config::general::buttonSize * config::general::toAugment;
		sound.square.y = config::screen::height - sound.texture.texture.height * config::general::toAugment;
		sound.square.width = sound.texture.texture.width;
		sound.square.height = sound.texture.texture.height;

	}
	void UpdateAudioButtons()
	{
		Vector2 mousePos = GetMousePosition();

		if (CheckCollisionPointRec(mousePos, music.square))
		{
			music.scale = plusSelected;

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				playMusic = !playMusic;
			}
		}
		else
		{
			music.scale = nonSelected;
		}

		if (CheckCollisionPointRec(mousePos, sound.square))
		{
			sound.scale = plusSelected;

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				playSounds = !playSounds;
			}
		}
		else
		{
			sound.scale = nonSelected;
		}

	}
	void DrawAudioButtons()
	{
		if (playMusic)
		{
			DrawTextureEx(music.texture.texture, { music.square.x,music.square.y }, 0, music.scale, GREEN);
		}
		else
		{
			DrawTextureEx(music.texture.texture, { music.square.x,music.square.y }, 0, music.scale, RED);
		}
		if (playSounds)
		{
			DrawTextureEx(sound.texture.texture, { sound.square.x,sound.square.y }, 0, sound.scale, GREEN);
		}
		else
		{
			DrawTextureEx(sound.texture.texture, { sound.square.x,sound.square.y }, 0, sound.scale, RED);
		}
		
	}
	void DeinitAudioButtons()
	{
		UnloadTexture(music.texture.texture);
		UnloadTexture(sound.texture.texture);
	}

	namespace config {

		namespace screen {

			int width = 1400;
			int height = 700;
			int fpsRate = 60;
			Vec2 screenCenter = Vec2(0, 0);

			void SetCenterPoint()
			{
				screen::screenCenter = Vec2(screen::width / 2, screen::height / 2);
			}

		}

		namespace scenes {

			SCENE scene = SCENE::NONE;
			SCENE next_scene = SCENE::MENU;

		}

		namespace board {

			int width = 700;
			int height = 700;
			Color tint = WHITE;

		}

		namespace general {

			Color hoverColorSideUp = RED;
			Color hoverColorSideDown = GREEN;
			Color boardColor = WHITE;

			int howManyTurns = 25;
			int timePerTurn = 20;

		}

	}

	

	Color GetRandomColor(int min, int max) {

		return { static_cast<unsigned char>(GetRandomValue(min, max)), static_cast<unsigned char>(GetRandomValue(min, max)), static_cast<unsigned char>(GetRandomValue(min,max)), static_cast<unsigned char>(GetRandomValue(200,255)) };

	}

}