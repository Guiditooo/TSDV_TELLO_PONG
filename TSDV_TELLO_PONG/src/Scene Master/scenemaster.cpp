#include "scenemaster.h"
#include <iostream>

namespace pong {

	namespace config {

		namespace scenes {

			void sceneManager(Scene& scene, Scene nextScene)
			{

				if (scene != nextScene)
				{

					switch (scene) //deinit
					{
					case Scene::MENU:
						menu::deinit();
						std::cout << "\nMENU Deinited";
						break;
					case Scene::GAME:
						game::deinit();
						std::cout << "\nGAME Deinited";
						break;
					case Scene::CONFIG:
						configScreen::deinit();
						std::cout << "\nConfig Deinited";
						break;
					case Scene::CREDITS:
						credits::deinit();
						std::cout << "\nCredits Deinited";
						break;
					}

					switch (nextScene)//init
					{
					case Scene::MENU:
						std::cout << "\nMENU Inited\n";
						menu::init();
						break;
					case Scene::GAME:
						std::cout << "\nGAME Inited\n";
						game::init();
						break;
					case Scene::CONFIG:
						std::cout << "\nConfig Inited\n";
						configScreen::init();
						break;
					case Scene::CREDITS:
						std::cout << "\nCredits Inited\n";
						credits::init();
						break;
					}


					scene = nextScene;

				}

				else
				{
					//std::cout << "On Scene > ";
					switch (scene) //deinit
					{
					case Scene::MENU:
						//std::cout << "MENU\n";
						break;
					case Scene::GAME:
						//std::cout << "GAME\n";
						break;
					}
				}

			}

		}

		void generalInit()
		{

			InitWindow(screen::width, screen::height, "Pong By Guido Tello");
			SetTargetFPS(screen::fpsRate);
			screen::setCenterPoint();
			std::string fontPath = "res/assets/Font/font.ttf";
			font = LoadFontEx(&fontPath[0], fontSize, 0, 250);
			fontPath = "res/assets/Font/score.ttf";
			scoreFont = LoadFontEx(&fontPath[0], fontSize, 0, 250);

			InitAudioDevice();
			InitAudioButtons();

		}

		void generalDeinit()
		{
			DeinitAudioButtons();
			CloseAudioDevice();
			UnloadFont(font);
			UnloadFont(scoreFont);
		}

		void generalUpdate(config::scenes::Scene scene)
		{

			using namespace scenes;

			switch (scene)
			{
			case Scene::MENU:
				menu::update();
				break;
			case Scene::GAME:
				game::update();
				break;
			case Scene::CONFIG:
				configScreen::update();
				//std::cout << "GAME Deinited";
				break;
			case Scene::CREDITS:
				credits::update();
				break;
			case Scene::QUIT:
				menu::continueInGame = false;
				break;
			}
		}

		void generalDraw(config::scenes::Scene scene)
		{
			using namespace scenes;

			BeginDrawing();
			ClearBackground(LIGHTGRAY);

			switch (scene)
			{
			case Scene::MENU:
				menu::draw();
				break;
			case Scene::GAME:
				game::draw();
				break;
			case Scene::CONFIG:
				configScreen::draw();
				//std::cout << "GAME Deinited";
				break;
			case Scene::CREDITS:
				credits::draw();
				break;
			case Scene::QUIT:
				menu::continueInGame = false;
				break;
			}

			UpdateAudioButtons();
			DrawAudioButtons();

			EndDrawing();

		}

		

	}


	void runGame() {

		config::generalInit();

		do {

			using namespace config;
			using namespace scenes;

			scenes::sceneManager(scene, next_scene);

			generalUpdate(scene);

			generalDraw(scene);

		} while (!WindowShouldClose() && menu::continueInGame);

		config::generalDeinit();

	}



}