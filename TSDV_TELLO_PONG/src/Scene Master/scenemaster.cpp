#include "scenemaster.h"
#include <iostream>

namespace pong {

	namespace config {

		namespace scenes {

			void SceneManager(SCENE& scene, SCENE nextScene)
			{

				if (scene != nextScene)
				{

					switch (scene) //Deinit
					{
					case SCENE::MENU:
						menu::Deinit();
						std::cout << "\nMENU Deinited";
						break;
					case SCENE::GAME:
						game::Deinit();
						std::cout << "\nGAME Deinited";
						break;
					case SCENE::CONFIG:
						configScreen::Deinit();
						std::cout << "\nConfig Deinited";
						break;
					case SCENE::CREDITS:
						credits::Deinit();
						std::cout << "\nCredits Deinited";
						break;
					}

					switch (nextScene)//Init
					{
					case SCENE::MENU:
						std::cout << "\nMENU Inited\n";
						menu::Init();
						break;
					case SCENE::GAME:
						std::cout << "\nGAME Inited\n";
						game::Init();
						break;
					case SCENE::CONFIG:
						std::cout << "\nConfig Inited\n";
						configScreen::Init();
						break;
					case SCENE::CREDITS:
						std::cout << "\nCredits Inited\n";
						credits::Init();
						break;
					}

					scene = nextScene;

				}

				else
				{
					//std::cout << "On SCENE > ";
					switch (scene) //Deinit
					{
					case SCENE::MENU:
						//std::cout << "MENU\n";
						break;
					case SCENE::GAME:
						//std::cout << "GAME\n";
						break;
					}

				}

			}

		}

		void GeneralInit()
		{
			backgroundColor = CreateColor(20,20,20);
			InitWindow(screen::width, screen::height, "Pong By Guido Tello");
			SetTargetFPS(screen::fpsRate);
			screen::SetCenterPoint();
			std::string fontPath = "res/assets/Font/font.ttf";
			font = LoadFontEx(&fontPath[0], fontSize, 0, 250);
			fontPath = "res/assets/Font/score.ttf";
			scoreFont = LoadFontEx(&fontPath[0], fontSize, 0, 250);

			InitAudioDevice();
			InitAudioButtons();

		}

		void GeneralDeinit()
		{
			DeinitAudioButtons();
			CloseAudioDevice();
			UnloadFont(font);
			UnloadFont(scoreFont);
		}

		void GeneralUpdate(config::scenes::SCENE scene)
		{

			using namespace scenes;

			switch (scene)
			{
			case SCENE::MENU:
				menu::Update();
				break;
			case SCENE::GAME:
				game::Update();
				break;
			case SCENE::CONFIG:
				configScreen::Update();
				//std::cout << "GAME Deinited";
				break;
			case SCENE::CREDITS:
				credits::Update();
				break;
			case SCENE::QUIT:
				menu::continueInGame = false;
				break;
			}
		}

		void GeneralDraw(config::scenes::SCENE scene)
		{
			using namespace scenes;

			BeginDrawing();
			ClearBackground(backgroundColor);
			//ClearBackground(LIGHTGRAY);
			//ClearBackground(CreateColor(20,20,20));

			switch (scene)
			{
			case SCENE::MENU:
				menu::Draw();
				break;
			case SCENE::GAME:
				game::Draw();
				break;
			case SCENE::CONFIG:
				configScreen::Draw();
				//std::cout << "GAME Deinited";
				break;
			case SCENE::CREDITS:
				credits::Draw();
				break;
			case SCENE::QUIT:
				menu::continueInGame = false;
				break;
			}

			UpdateAudioButtons();
			DrawAudioButtons();

			EndDrawing();

		}

		

	}


	void RunGame() {

		config::GeneralInit();

		do {

			using namespace config;
			using namespace scenes;

			scenes::SceneManager(scene, next_scene);

			GeneralUpdate(scene);

			GeneralDraw(scene);

		} while (!WindowShouldClose() && menu::continueInGame);

		config::GeneralDeinit();

	}



}