#include "gameplay.h"
#include "Extern Vars/Button/button.h"
#include "Extern Vars/Timer/timer.h"
#include "Extern Vars/Ball/ball.h"
#include "Player/player.h"
#include <iostream>
#include <string>
#include <vector>

namespace pong {

	namespace game {

		using namespace elements;
		using namespace std;

		float timeElapsed = 0;
		
		Collision ball;

		TextureInfo table, lateralTable;
		Limits limit;

		Rectangle gameplayRec, lowerRec, menuRec, lateralViewRec, scoreRec;

		Player p1, p2;

		Button button[howManyButtons];

		bool isPaused = false;

		void init() 
		{
			p1.SetColor(PINK);
			p2.SetColor(WHITE);

			ball.Init();
			ball.SetRadius(16);
			ball.SetBallSpeed(Vec2(100, 40));
#if _DEBUG
			ball.SetBallSpeed(Vec2(100, 40));
#endif
			ball.SetBallAcceleration(Vec2(30,25));
			ball.SetTexture(LoadTexture("res/assets/Ball/ball_blue.png"));
			ball.SetColor(BLACK);

			zonesInit();

			backgroundInit();
			
			limit.InitLimits(gameplayRec, table.position, table.texture.width, table.texture.height);

			std::string btn_text[howManyButtons] = { "Pause","Main Menu" };
			buttons::Selector btn_type[howManyButtons] = { buttons::Selector::PAUSE, buttons::Selector::MENU };

			for (short i = 0; i < howManyButtons; i++)
			{
				button[i].MakeStandardButton();
				button[i].SetText(btn_text[i]);
				button[i].SetButtonType(btn_type[i]);
				button[i].SetButtonPosition({ menuRec.x + menuRec.width / 2 - (button[i].GetButtonSize().x) / 2  ,   menuRec.y + menuRec.height / 4 - (button[i].GetButtonSize().y) / 2 + (menuRec.height / 2) * i });
			}

			playersInit();

		}
		void update()
		{
			//timeElapsed += GetFrameTime();
			Vec2 mousePos = GetMousePosition();

			if (playMusic)
			{
				UpdateMusicStream(gameMusic);
			}

			checkButtons();

			if (!isPaused) {

				checkWinConditions();

				float deltaTime = GetFrameTime();

				ball.Move(deltaTime);
				ball.ApplyAcceleration(deltaTime);

				bool onLateralLimit = false;
				bool onSideLimit = false;
				int whichLateralLimit = 0;
				int whichSideLimit = 0;

				for (short i = 0; i < howManyLateralLimits; i++)
				{
					if (CheckCollisionCircleRec(ball.GetBallCenter().ToVector2(), ball.GetRadius(), limit.GetLimit(static_cast<SIDE>(i))))
					{
						onSideLimit = true;
						whichSideLimit = i;
					}
				}

				if (CheckCollisionCircleRec(ball.GetBallCenter().ToVector2(), ball.GetRadius(), p1.GetRectangle()))
				{
					ball.SetBallAcceleration(Vec2(0 - ball.GetBallAcceleration().x, ball.GetBallAcceleration().y));
					ball.SetBallSpeed(Vec2(0 - ball.GetBallSpeed().x, ball.GetBallSpeed().y));
					ball.SetColor(p2.GetColor());
				}

				if (CheckCollisionCircleRec(ball.GetBallCenter().ToVector2(), ball.GetRadius(), p2.GetRectangle()))
				{
					ball.SetBallAcceleration(Vec2(0 - ball.GetBallAcceleration().x, ball.GetBallAcceleration().y));
					ball.SetBallSpeed(Vec2(0 - ball.GetBallSpeed().x, ball.GetBallSpeed().y));
					ball.SetColor(p1.GetColor());
				}

				for (short i = howManyLateralLimits; i < howManyLimits; i++)
				{
					if (CheckCollisionCircleRec(ball.GetBallCenter().ToVector2(), ball.GetRadius(), limit.GetLimit(static_cast<SIDE>(i))))
					{
						onLateralLimit = true;
						whichLateralLimit = i;
					}
				}
				
				if (onLateralLimit)
				{
					switch (static_cast<SIDE>(whichLateralLimit))
					{
					case pong::SIDE::LEFT:
						p2.AddOneToScore();
						break;
					case pong::SIDE::RIGHT:
						p1.AddOneToScore();
						break;
					default:
						break;
					}

				}

				if (onSideLimit)
				{
					switch (static_cast<SIDE>(whichSideLimit))
					{
					case pong::SIDE::UP:
						ball.SetBallAcceleration(Vec2(ball.GetBallAcceleration().x, 0 - ball.GetBallAcceleration().y));
						ball.SetBallSpeed(Vec2(ball.GetBallSpeed().x, 0 - ball.GetBallSpeed().y));
						break;
					case pong::SIDE::DOWN:
						ball.SetBallAcceleration(Vec2(ball.GetBallAcceleration().x, 0 - ball.GetBallAcceleration().y));
						ball.SetBallSpeed(Vec2(ball.GetBallSpeed().x, 0 - ball.GetBallSpeed().y));
						break;
					default:
						break;
					}

				}

				p1.MovePlayer();
				p2.MovePlayer();

			}

		}
		void draw() 
		{
			table.Draw();
			ball.Draw();
			
#if  _DEBUG
			DrawRectangleLinesEx(ball.GetBallRectangle(), 1, RED);
			DrawRectangleLinesEx(gameplayRec, 2, RED);
			DrawRectangleLinesEx(lowerRec, 2, GREEN);
			DrawRectangleLinesEx(lateralViewRec, 2, BLACK);
			DrawRectangleLinesEx(menuRec, 2, PINK);
			DrawRectangleLinesEx(scoreRec, 2, DARKBLUE);
			limit.Draw();
#endif //  DEBUG
			for (short i = 0; i < howManyButtons; i++)
			{
				button[i].Draw();
			}

			p1.DrawLetter();
			p2.DrawLetter();

			p1.DrawPlayer();
			p2.DrawPlayer();

			lateralTable.Draw();

		}
		void deinit() 
		{
			UnloadSound(buttonBeep);
			UnloadMusicStream(gameMusic);
			ball.Deinit();
			table.Deinit();
			lateralTable.Deinit();
		}

		void resetGame() 
		{

		}
		void playersInit()
		{

			p1.SetScore(0);
			p1.SetLetterWidth((scoreRec.width - lateralViewRec.width) / 2);
			p1.SetLetterPos(Vec2(scoreRec.GetPos().x, lateralViewRec.y));

			p2.SetScore(0);
			p2.SetLetterWidth((scoreRec.width - lateralViewRec.width) / 2);
			p2.SetLetterPos(Vec2(scoreRec.GetPos().x + scoreRec.width - p2.GetLetterWidth(), lateralViewRec.y));
			
			p1.SetLetterColors(BLACK, WHITE, PINK, 3);
			p2.SetLetterColors(BLACK, WHITE, PINK, 3);

			p1.SetAxis(Axis::VERTICAL);
			p2.SetAxis(Axis::VERTICAL);
			p1.Setside(SIDE::LEFT);
			p2.Setside(SIDE::RIGHT);

			p1.SetColor(BLUE);
			p2.SetColor(RED);

			p1.SetActionKey(ACTIONKEYS::UP, KEY_W);
			p1.SetActionKey(ACTIONKEYS::DOWN, KEY_S);
			p2.SetActionKey(ACTIONKEYS::UP, KEY_I);
			p2.SetActionKey(ACTIONKEYS::DOWN, KEY_K);

			p1.SetWidth(20);
			p2.SetWidth(20);
			p1.SetHeight(120);
			p2.SetHeight(120);

			p1.SetPosition(Vec2(table.position.x - p1.GetWidth() / 2, gameplayRec.GetCenter().y - p1.GetHeight() / 2));
			p2.SetPosition(Vec2(table.position.x + table.texture.width - p2.GetWidth() / 2, gameplayRec.GetCenter().y - p2.GetHeight() / 2));

			p1.SetSpeed(Vec2(200, 200));
			p2.SetSpeed(Vec2(200, 200));


		}
		void musicInit()
		{
			gameMusic = LoadMusicStream("res/assets/Music/gameplay.mp3");
			PlayMusicStream(gameMusic);
			SetMusicVolume(gameMusic, 0.1f);

			buttonBeep = LoadSound("res/assets/Sounds/buttonClic.ogg");
			SetSoundVolume(buttonBeep, 0.3f);
		}
		void buttonsInit()
		{
			/*
			string label[howManyButtons]
			{
				"Main Menu", //0 to main menu
				"Restart",
				"Pause"
			};

			for (short i = 0; i < howManyButtons; i++)
			{
				
				button[i] = new Button();
				button[i]->SetText(label[i]);
				button[i]->SetTextSize(textInitialSize);
				button[i]->SetTextColor(BROWN);
				button[i]->LoadTx();
				button[i]->SetButtonPosition({ button[i]->GetButtonPosition().x,(button[i]->GetButtonSize().y + buttonSeparation) * i });
				
			}
			*/
		}
		void timersInit()
		{
			/*
			timerWhite = new Timer();
			timerWhite->SetTextSize(textInitialSize);
			timerWhite->SetTextColor(BROWN);
			timerWhite->LoadTx();
			Vector2 timerPos;
			timerPos.x = config::screen::width - timerWhite->GetTimerSize().x;
			timerPos.y = 0;
			timerWhite->SetTimerPosition(timerPos);
			timerWhite->SetText(to_string(timeWhite));
			*/
		}
		void backgroundInit()
		{
			table.texture = LoadTexture("res/assets/Table/table_black.png");
			table.texture.height = gameplayRec.height * 9 / 10;
			table.texture.width = table.texture.height * 16 / 9;
			table.color = WHITE;
			table.position = Vec2(gameplayRec.GetCenter().x - table.texture.width / 2, gameplayRec.GetCenter().y - table.texture.height / 2);
		
			lateralTable.texture = LoadTexture("res/assets/Backgrounds/TableB.png");
			lateralTable.texture.width = lateralViewRec.width;
			lateralTable.texture.height = lateralViewRec.height/2;
			lateralTable.position = Vec2(lateralViewRec.x, lateralViewRec.y + (lateralViewRec.height / 2 - lateralTable.texture.height / 2) * 2);
			lateralTable.color = WHITE;
		}
		void zonesInit()
		{
			gameplayRec.x = 0;
			gameplayRec.y = 0;
			gameplayRec.width = config::screen::width;
			gameplayRec.height = config::screen::height * 3 / 4;

			lowerRec.x = 0;
			lowerRec.y = gameplayRec.height;
			lowerRec.width = gameplayRec.width;
			lowerRec.height = config::screen::height - gameplayRec.height;

			lateralViewRec.height = lowerRec.height * 9 / 10;
			lateralViewRec.width = lateralViewRec.height * 16 / 9;
			lateralViewRec.x = lowerRec.width / 2 - lateralViewRec.width / 2;
			lateralViewRec.y = lowerRec.y + lowerRec.height / 2 - lateralViewRec.height / 2;

			menuRec.x = lowerRec.width * 4 / 5;
			menuRec.y = lowerRec.y;
			menuRec.width = lowerRec.width / 5;
			menuRec.height = lowerRec.height;

			scoreRec.y = lowerRec.y;
			scoreRec.width = lowerRec.width * 2 / 5;
			scoreRec.x = lowerRec.width / 2 - scoreRec.width / 2;
			scoreRec.height = lowerRec.height;
		}

		void checkButtons()
		{
			Vec2 mousePos = GetMousePosition();
			for (short i = 0; i < howManyButtons; i++)
			{
				if (CheckCollisionPointRec(mousePos.ToVector2(), button[i].GetRec()))
				{
					if (!button[i].isHovered())
					{
						if (playSounds)
						{
							PlaySound(buttonBeep);
						}
						button[i].Hover();
					}
					if (button[i].GetButtonType()==elements::buttons::Selector::MENU)
					{
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							config::scenes::next_scene = config::scenes::Scene::MENU;
						}
					}
					if (button[i].GetButtonType() == elements::buttons::Selector::PAUSE)
					{
						if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
						{
							isPaused = !isPaused;
						}
					}
				}
				else
				{
					if (button[i].isHovered())
					{
						button[i].UnHover();
					}
				}

			}
		}
		void checkWinConditions() 
		{
			
		}
		
		void drawTimers()
		{
			
		}
		void drawButtons()
		{
			for (short i = 0; i < howManyButtons; i++)
			{
				/*
				if (button[i] != NULL)
				{
					button[i]->Draw();
				}
				*/
			}
		}

		void deinitButtons()
		{

		}
		void deinitTimers()
		{
			
		}

		void Score::SetScoreAsText()
		{
			text.tx = std::to_string(score);
		}

	}

}