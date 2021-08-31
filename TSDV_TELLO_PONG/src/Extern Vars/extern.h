#ifndef MENU_EXTERN
#define MENU_EXTERN

#include "raylib.h"
#include "Extern Vars/Vec2/vec2.h"
#include <iostream>


namespace pong {

	using namespace elements;

	extern Font font;
	extern Font scoreFont;

	extern int pointLimit;

	const int fontSize = 64;

	const float plusSelected = 1.15f;
	const float  nonSelected = 1.0f;

	const int spacing = 1;

	const int actionKeysCount = 6;

	Color CreateColor(Vector4 v);
	Color CreateColor(Vector3 v);
	Color CreateColor(int r, int g, int b, int a);
	Color CreateColor(int r, int g, int b);
	
	extern Color backgroundColor;

	enum class AXIS
	{
		HORIZONTAL,
		VERTICAL,
		BOTH,
		NONE
	};

	enum class SIDE
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	struct Text 
	{
		std::string tx = "";
		Vec2 pos = { 0,0 };
		int size = 5;
		Color color = BLACK;
		Text();
	};

	enum class ACTIONKEYS
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ACTION1,
		ACTION2
	};

	struct Letter
	{
		Text text;
		Vec2 pos;
		bool isActive = false;
		int width;
		int height;
		int paddingX = 5;
		int paddingY = 1;
		void Init(std::string txt);
		Color backgroundColor; 
		Color frameColor;
		int frameWidth;
		Rectangle GetRec();
		void Draw();
		void CenterText();
		Letter();
	};

	struct TextureInfo 
	{
	public:
		Texture2D texture;
		Color color;
		Vec2 position = { 0,0 };
		TextureInfo()
		{
			texture = Texture2D();
			color = WHITE;
			position = Vec2(0,0);
		}
		void Draw() 
		{
			DrawTexture(texture, position.x, position.y, color);
		}
		void Deinit()
		{
			UnloadTexture(texture);
		}
	};

	struct Buttons 
	{
		Color color = WHITE;
		Rectangle square;
		bool selected = false;
		bool clicked = false;
		float scale = 1;
		Text txt;
		TextureInfo texture;
		void DrawButton() 
		{
			DrawRectangleRec(square, BLACK);
			DrawRectangleLinesEx(square, 3, WHITE);
			DrawTextEx(font, &(txt.tx)[0], { square.x, square.y }, square.height, 1, WHITE);
		}
	};

	namespace config {

		namespace screen{
		
			extern int width;
			extern int height;
			extern int fpsRate;
			extern Vec2 screenCenter;

			void SetCenterPoint();

		}

		namespace scenes {

			enum class SCENE 
			{
				MENU,
				CONFIG,
				CREDITS,
				WINS,
				QUIT,
				GAME,
				NONE
			};

			extern SCENE scene;
			extern SCENE next_scene;

		}

		namespace general {

			extern Color hoverColorSideUp;
			extern Color hoverColorSideDown;
			extern Color boardColor;
			extern int howManyTurns;
			extern int timePerTurn;

			const Color pieceColorSideUp = WHITE;
			const Color pieceColorSideDown = BROWN;

			const int buttonSize = 60;
			const int buttonPadding = 20;
			const float toAugment = 1.3f;
			const float toDisminish = 10 / 13;

		}

	}

	extern Buttons music;
	extern Buttons sound;

	extern bool playMusic;
	extern bool playSounds;

	void InitAudioButtons();
	void UpdateAudioButtons();
	void DrawAudioButtons();
	void DeinitAudioButtons();

	Color GetRandomColor(int min, int max);
	void DrawButton(Buttons btn);

}
#endif