#ifndef MENU_CREDITS
#define MENU_CREDITS

#include "Extern Vars/extern.h"

using namespace std;

namespace pong {

	namespace credits {

		static Sound buttonBeep;
		static Music creditMusic;

		void init();
		void update();
		void draw();
		void deinit();

	}

}

#endif