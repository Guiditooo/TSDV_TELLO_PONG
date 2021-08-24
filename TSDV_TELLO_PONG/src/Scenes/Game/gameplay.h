#ifndef GAME_PLAY
#define GAME_PLAY

#include "raylib.h"
#include "Extern Vars/extern.h"

namespace pong {

	namespace game {

		const int howManyButtons = 3; //Restart, Back to menu, Resume
		const int howManyLateralLimits = 2;
		const int howManySideLImits = 2;
		const int howManyLimits = 4;
		const int howManyPieces = 16;
		const int rows = 2;
		const int distanceFromBoard = 10;

		//extern Score p1Score, p2Score;

		static Sound buttonBeep;
		static Music gameMusic;

		struct Score : public Letter
		{
			int score;
			void SetScoreAsText();
		};

		void init();
		void update();
		void draw();
		void deinit();

		void resetGame();
		void playersInit();

		void musicInit();

		void buttonsInit();
		void timersInit();
		void backgroundInit();
		void zonesInit();

		void checkButtons();
		void checkWinConditions();

		void drawTimers();
		void drawButtons();

		void deinitButtons();
		void deinitTimers();

		struct Limits
		{
		private:
			Rectangle limit[howManyLimits];
		public:
			void InitLimits(Rectangle actualRec, Vec2 tablePos, float tableWidth, float tableHeight)
			{
				int upDownCorrect = 10;
				int limitSize = 2;
				for (short i = 0; i < howManyLimits; i++)
				{
					switch (static_cast<SIDE>(i))
					{
					case pong::SIDE::UP:
						limit[i].width = actualRec.width;
						limit[i].height = (actualRec.height - tableHeight) / 2;
						limit[i].x = actualRec.x;
						limit[i].y = actualRec.y;
						break;
					case pong::SIDE::DOWN:
						limit[i].width = actualRec.width;
						limit[i].height = (actualRec.height - tableHeight) / 2;
						limit[i].x = actualRec.x;
						limit[i].y = limit[i].height + tableHeight;
						break;
					case pong::SIDE::LEFT:
						limit[i].width = (actualRec.width - tableWidth) / 2;
						limit[i].height = actualRec.height;
						limit[i].x = actualRec.x;
						limit[i].y = actualRec.y;
						break;
					case pong::SIDE::RIGHT:
						limit[i].width = (actualRec.width - tableWidth) / 2;
						limit[i].height = actualRec.height;
						limit[i].x = limit[i].width + tableWidth;
						limit[i].y = actualRec.y;
						break;
					default:
						break;
					}
				}
			}
			void Draw()
			{
				for (short i = 0; i < 4; i++)
				{
					DrawRectangleLinesEx(limit[i], 5, BLUE);
				}
			}
			Rectangle GetLimit(SIDE side) 
			{ 
				return limit[static_cast<int>(side)];
			}
		};

	}

}
#endif