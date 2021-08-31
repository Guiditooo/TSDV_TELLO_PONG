#ifndef WINSCREEN_H
#define WINSCREEN_H

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

#endif#pragma once
