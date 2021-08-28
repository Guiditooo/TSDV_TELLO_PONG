#ifndef GAME_OPTIONS
#define GAME_OPTIONS

#include "Extern Vars/extern.h"
#include "Scenes/Game/Player/player.h"

using namespace std;

namespace pong {

	extern game::Player* p1;
	extern game::Player* p2;

	namespace configScreen {

		static Sound buttonBeep;
		static Music configMusic;

		enum class COLORS
		{
			COLOR_WHITE,
			COLOR_RED,
			COLOR_GREEN,
			COLOR_PURPLE,
			COLOR_BLUE
		};

		void Init();
		void Update();
		void Draw();
		void Deinit();

		void LoadAudio();
		void InitAreas();
		void DrawAreas();
		void CheckButtons();

	}

}

#endif