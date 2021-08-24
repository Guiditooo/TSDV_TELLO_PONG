#ifndef GAME_OPTIONS
#define GAME_OPTIONS

#include "Extern Vars/extern.h"

using namespace std;

namespace pong {

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
		

		void init();
		void update();
		void draw();
		void deinit();

		void LoadAudio();
		void CheckButtons();

	}

}

#endif