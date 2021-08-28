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

			void SceneManager(SCENE&, SCENE);

		}

		void GeneralInit();
		void GeneralUpdate(config::scenes::SCENE scene);
		void GeneralDraw(config::scenes::SCENE scene);
		void GeneralDeinit();

		void SetCenterPoint();

	}

	void RunGame();

}
#endif