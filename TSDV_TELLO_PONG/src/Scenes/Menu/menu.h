#ifndef MENU_H
#define MENU_H

#include "raylib.h"
#include "Extern Vars/extern.h"

namespace pong {

	namespace menu {

		const int baseTextHeight = 50; // 30px
		const int howManyButtons = 4;
		const int titleLenght = 3;

		extern Buttons buttons[howManyButtons];
		static Text title[titleLenght];

		static Sound buttonBeep;
		static Music menuMusic;

		extern bool continueInGame;

		extern void init();
		extern void update();
		extern void draw();
		extern void deinit();

	}

}

#endif