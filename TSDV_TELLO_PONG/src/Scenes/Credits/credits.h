#ifndef MENU_CREDITS
#define MENU_CREDITS

#include "Extern Vars/extern.h"

using namespace std;

namespace pong {

	namespace credits {

		static Sound buttonBeep;
		static Music creditMusic;

		void Init();
		void Update();
		void Draw();
		void Deinit();

	}

}

#endif