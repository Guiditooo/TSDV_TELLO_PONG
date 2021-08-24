#ifndef MENU_EXTERN
#define MENU_EXTERN

#include "raylib.h"
#include "Extern Vars/Vec2/vec2.h"
#include <iostream>


namespace pong {

	using namespace elements;

	extern Font font;
	extern Font scoreFont;
	
	const int fontSize = 64;

	const float plusSelected = 1.15f;
	const float  nonSelected = 1.0f;

	const int spacing = 1;

	const int actionKeysCount = 6;

	Color createColor(Vector4 v);
	Color createColor(Vector3 v);
	Color createColor(int r, int g, int b, int a);

	enum class Axis
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
		void drawButton() 
		{
			DrawRectangleRec(square, BLACK);
			DrawRectangleLinesEx(square, 3, WHITE);
			//DrawText(&txt.tx[0], txt.pos.x, txt.pos.y, txt.size, WHITE);
			DrawTextEx(font, &(txt.tx)[0], { square.x, square.y }, square.height, 1, WHITE);
		}
	};

	namespace config {

		namespace screen{
		
			extern int width;
			extern int height;
			extern int fpsRate;
			extern Vec2 screenCenter;

			void setCenterPoint();

		}

		namespace scenes {

			enum class Scene 
			{
				MENU,
				CONFIG,
				CREDITS,
				WINS,
				QUIT,
				GAME,
				NONE
			};

			extern Scene scene;
			extern Scene next_scene;

		}

		namespace board {

			const int slotSize = 74;
			const int boardFrame = 55;

			extern int width;
			extern int height;
			extern Color tint;

			enum class SIDE 
			{
				UP, //WHITE
				DOWN, //BLACK
				NONE
			};

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

	Color getRandomColor(int min, int max);
	void drawButton(Buttons btn);

}
#endif