#ifndef MENU_SCENEMASTER
#define MENU_SCENEMASTER

#include "Extern Vars/extern.h"
#include "Scenes/Game/gameplay.h"
#include "Scenes/Menu/menu.h"
#include "Scenes/Credits/credits.h"
#include "Scenes/Config/config.h"

namespace pong {

	namespace config {

		namespace scenes {			

			void sceneManager(Scene&, Scene);

		}

		void generalInit();
		void generalUpdate(config::scenes::Scene scene);
		void generalDraw(config::scenes::Scene scene);
		void generalDeinit();

		void setCenterPoint();

	}

	void runGame();

}
#endif