#include "gameplay.h"


namespace pong {

	namespace game {

		using namespace elements;
		using namespace std;

		float timeElapsed = 0;
		
		Ball* ball;

		TextureInfo table, lateralTable;
		Limits limit;

		Rectangle gameplayRec, lowerRec, menuRec, lateralViewRec, scoreRec;

		Letter winScreen;
		Text winText;

		Player* p1;
		Player* p2;

		Button button[howManyButtons];
		
		bool alreadyGivenPoints = false;
		bool onCollition = false;
		int colliderIndex = -1;
		bool isPaused = false;

		void Init() 
		{

			ZonesInit();

			BackgroundInit();

			ButtonsInit();
			
			limit.InitLimits(gameplayRec, table.position, table.texture.width, table.texture.height);

			ResetGame();

		}
		void Update()
		{

			Vec2 mousePos = GetMousePosition();

			if (playMusic)
			{
				UpdateMusicStream(gameMusic);
			}

			CheckButtons();

			if (!isPaused) 
			{

				CheckWinConditions();

				float deltaTime = GetFrameTime();

				ball->Move(deltaTime);
				ball->ApplyAcceleration(deltaTime);

				bool onLateralLimit = false;
				bool onSideLimit = false;
				int whichLateralLimit = 0;
				int whichSideLimit = 0;

				for (short i = 0; i < howManyLateralLimits; i++)
				{
					if (CheckCollisionCircleRec(ball->GetBallCenter().ToVector2(), ball->GetRadius(), limit.GetLimit(static_cast<SIDE>(i))))
					{
						onSideLimit = true;
						whichSideLimit = i;
					}
				}

				if (CheckCollisionCircleRec(ball->GetBallCenter().ToVector2(), ball->GetRadius(), p1->GetRectangle()))
				{	//Colision con el pad izquierdo
					ball->SetBallAcceleration(Vec2(0 - ball->GetBallAcceleration().x, ball->GetBallAcceleration().y));
					ball->SetBallSpeed(Vec2(0 - ball->GetBallSpeed().x, ball->GetBallSpeed().y));
					ball->SetColor(p2->GetColor());
					p1->Hitted(true);
				}

				if (CheckCollisionCircleRec(ball->GetBallCenter().ToVector2(), ball->GetRadius(), p2->GetRectangle()))
				{	//Colision con el pad derecho
					ball->SetBallAcceleration(Vec2(0 - ball->GetBallAcceleration().x, ball->GetBallAcceleration().y));
					ball->SetBallSpeed(Vec2(0 - ball->GetBallSpeed().x, ball->GetBallSpeed().y));
					ball->SetColor(p1->GetColor());
					p2->Hitted(true);
				}
				if (!p1->JustHitted() && !p2->JustHitted()) 
				{	//Si hizo colision con alguno de los pads, no chequea los fondos.

					for (short i = howManyLateralLimits; i < howManyLimits; i++)
					{
						if (CheckCollisionCircleRec(ball->GetBallCenter().ToVector2(), ball->GetRadius(), limit.GetLimit(static_cast<SIDE>(i))))
						{
							onLateralLimit = true;
							whichLateralLimit = i;
						}
					}

					if (onLateralLimit)
					{//La pelota toca los limites de la cancha y se mete punto
						switch (static_cast<SIDE>(whichLateralLimit))
						{
						case pong::SIDE::LEFT:
							if (!p2->JustScored())
								p2->AddOneToScore();
							break;
						case pong::SIDE::RIGHT:
							if (!p1->JustScored())
								p1->AddOneToScore();
							break;
						default:
							break;
						}

						Score();

					}

				}
				else
				{
					p1->Hitted(false);
					p2->Hitted(false);
				}

				if (onSideLimit)
				{//La pelota toca arriba o abajo
					switch (static_cast<SIDE>(whichSideLimit))
					{
					case pong::SIDE::UP:
						ball->SetBallAcceleration(Vec2(ball->GetBallAcceleration().x, 0 - ball->GetBallAcceleration().y));
						ball->SetBallSpeed(Vec2(ball->GetBallSpeed().x, 0 - ball->GetBallSpeed().y));
						break;
					case pong::SIDE::DOWN:
						ball->SetBallSpeed(Vec2(ball->GetBallSpeed().x, 0 - ball->GetBallSpeed().y));
						ball->SetBallAcceleration(Vec2(ball->GetBallAcceleration().x, 0 - ball->GetBallAcceleration().y));
						break;
					default:
						break;
					}

				}

				p1->MovePlayer();
				p2->MovePlayer();

			}

		}
		void Draw() 
		{
			if (!winScreen.isActive)
			{
				table.Draw();
				if (ball != nullptr)
					ball->Draw();

#if  _DEBUG
				if (ball != nullptr)
					DrawRectangleLinesEx(ball->GetBallRectangle(), 1, RED);
				DrawRectangleLinesEx(gameplayRec, 2, RED);
				DrawRectangleLinesEx(lowerRec, 2, GREEN);
				DrawRectangleLinesEx(lateralViewRec, 2, BLACK);
				DrawRectangleLinesEx(menuRec, 2, PINK);
				DrawRectangleLinesEx(scoreRec, 2, DARKBLUE);
				limit.Draw();
#endif //  DEBUG


				if (p1 != nullptr)
				{
					p1->DrawPlayer();
					p1->DrawLabel();
				}
				if (p2 != nullptr)
				{
					p2->DrawPlayer();
					p2->DrawLabel();
				}

				lateralTable.Draw();

			}
			else
			{
				DrawWinScreen();
				DrawTextEx(scoreFont, &winText.tx[0], winText.pos.ToVector2(), fontSize, spacing, winText.color);
			}

			if (p1 != nullptr)
			{
				p1->DrawLetter();
			}
			if (p2 != nullptr)
			{
				p2->DrawLetter();
			}

			DrawButtons();

		}
		void Deinit() 
		{
			UnloadSound(buttonBeep);
			UnloadMusicStream(gameMusic);
			if (ball != nullptr)
			{ 
				ball->Deinit();
				ball = nullptr;
				delete ball;
			}
			table.Deinit();
			lateralTable.Deinit();
			if (p1 != nullptr)
			{
				p1 = nullptr;
				delete p1;
			}
			if (p2 != nullptr)
			{
				p2 = nullptr;
				delete p2;
			}

		}

		void ResetGame() 
		{
			BallInit();
			PlayersInit();
			winScreen.isActive = false;
			p1->Won(false);
			p2->Won(false);
			isPaused = false;
		}

		void Score()
		{
			ball->SetBallSpeed(Vec2(100, 40));
			ball->SetBallAcceleration(Vec2(30, 25));
			ball->SetPosition(gameplayRec.GetCenter());
			
			p1->SetSpeed(Vec2(200, 200));
			p2->SetSpeed(Vec2(200, 200));
			p1->Scored(false);
			p2->Scored(false);

		}

		void PlayersInit()
		{
			if (p1 == nullptr)
				p1 = new Player();
			p1->SetColor(PINK);
			if (p2 == nullptr)
				p2 = new Player();
			p2->SetColor(WHITE);
			p1->SetScore(0);
			p2->SetScore(0);
			p1->SetText("Player 1");
			p2->SetText("Player 2");
			p1->SetTextColor(WHITE);
			p2->SetTextColor(WHITE);
			p1->SetTextSize(fontSize);
			p2->SetTextSize(fontSize);
			Vec2 aux = MeasureTextEx(scoreFont, &p1->GetText()[0], fontSize, spacing);
			p1->SetTextPosition(Vec2(limit.GetLimit(SIDE::LEFT).width / 2-aux.x/2, aux.y/2));
			aux = MeasureTextEx(scoreFont, &p2->GetText()[0], fontSize, spacing);
			p2->SetTextPosition(Vec2(limit.GetLimit(SIDE::RIGHT).x + limit.GetLimit(SIDE::RIGHT).width / 2-aux.x/2, aux.y/2));
			p1->SetLetterWidth((scoreRec.width - lateralViewRec.width) / 2);
			p1->SetLetterHeight(MeasureTextEx(scoreFont, &p1->GetLetterText()[0], fontSize, spacing).y);
			p1->SetLetterPos(Vec2(scoreRec.GetPos().x, lateralViewRec.y + 20));
			p2->SetLetterWidth((scoreRec.width - lateralViewRec.width) / 2);
			p2->SetLetterHeight(MeasureTextEx(scoreFont, &p2->GetLetterText()[0], fontSize, spacing).y);
			p2->SetLetterPos(Vec2(scoreRec.GetPos().x + scoreRec.width - p2->GetLetterWidth(), lateralViewRec.y + 20));
			p1->SetLetterColors(BLACK, WHITE, PINK, 3);
			p2->SetLetterColors(BLACK, WHITE, PINK, 3);
			p1->SetAxis(AXIS::VERTICAL);
			p2->SetAxis(AXIS::VERTICAL);
			p1->Setside(SIDE::LEFT);
			p2->Setside(SIDE::RIGHT);
			p1->SetColor(BLUE);
			p2->SetColor(RED);
			p1->SetActionKey(ACTIONKEYS::UP, KEY_W);
			p1->SetActionKey(ACTIONKEYS::DOWN, KEY_S);
			p2->SetActionKey(ACTIONKEYS::UP, KEY_I);
			p2->SetActionKey(ACTIONKEYS::DOWN, KEY_K);
			p1->SetWidth(20);
			p2->SetWidth(20);
			p1->SetHeight(120);
			p2->SetHeight(120);
			p1->SetPosition(Vec2(table.position.x - p1->GetWidth() / 2, gameplayRec.GetCenter().y - p1->GetHeight() / 2));
			p2->SetPosition(Vec2(table.position.x + table.texture.width - p2->GetWidth() / 2, gameplayRec.GetCenter().y - p2->GetHeight() / 2));
			p1->SetSpeed(Vec2(200, 200));
			p2->SetSpeed(Vec2(200, 200));
		}
		void MusicInit()
		{
			gameMusic = LoadMusicStream("res/assets/Music/gameplay.mp3");
			PlayMusicStream(gameMusic);
			SetMusicVolume(gameMusic, 0.1f);

			buttonBeep = LoadSound("res/assets/Sounds/buttonClic.ogg");
			SetSoundVolume(buttonBeep, 0.3f);
		}
		void ButtonsInit()
		{
			std::string btn_text[howManyButtons] = { "Main Menu", "Reset", "Pause" };
			
			buttons::Selector btn_type[howManyButtons] = { buttons::Selector::PAUSE, buttons::Selector::MENU, buttons::Selector::RESET };
			for (short i = 0; i < howManyButtons; i++)
			{
				button[i].MakeStandardButton();
				button[i].SetButtonType(static_cast<buttons::Selector>(i));
				button[i].SetText(btn_text[i]);
			}

			button[static_cast<int>(buttons::Selector::RESET)].SetButtonPosition({ menuRec.x + menuRec.width / 4 - (button[static_cast<int>(buttons::Selector::RESET)].GetButtonSize().x) / 2  ,   menuRec.y + menuRec.height / 4 - (button[static_cast<int>(buttons::Selector::RESET)].GetButtonSize().y) / 2/* + (menuRec.height / 4)*/});
			button[static_cast<int>(buttons::Selector::PAUSE)].SetButtonPosition({ menuRec.x + menuRec.width * 3 / 4 - (button[static_cast<int>(buttons::Selector::PAUSE)].GetButtonSize().x) / 2  ,   menuRec.y + menuRec.height / 4 - (button[static_cast<int>(buttons::Selector::PAUSE)].GetButtonSize().y) / 2});
			button[static_cast<int>(buttons::Selector::MENU)].SetButtonPosition({ menuRec.x + menuRec.width / 2 - (button[static_cast<int>(buttons::Selector::MENU)].GetButtonSize().x) / 2  ,   menuRec.y + menuRec.height * 3 / 4 - (button[static_cast<int>(buttons::Selector::MENU)].GetButtonSize().y) / 2});

		}
		void TimersInit()
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
		void BackgroundInit()
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
		void ZonesInit()
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
		void BallInit()
		{
			if(ball==nullptr)
				ball = new Ball();
			ball->Init();
			ball->SetRadius(16);
			ball->SetBallSpeed(Vec2(100, 40));
			ball->SetBallAcceleration(Vec2(30, 25));
#if _DEBUG	
			ball->SetBallSpeed(Vec2(120, 40));
			ball->SetBallAcceleration(Vec2(40, 25));
#endif			
			ball->SetTexture(LoadTexture("res/assets/Ball/ball_blue.png"));
			ball->SetColor(BLACK);
			ball->SetPosition(Vec2(gameplayRec.x + gameplayRec.width/2,gameplayRec.y + gameplayRec.height/2));
		}

		void CheckButtons()
		{
			Vec2 mousePos = GetMousePosition();
			for (short i = 0; i < howManyButtons; i++)
			{
				if (CheckCollisionPointRec(mousePos.ToVector2(), button[i].GetRec()))
				{
					if (!button[i].IsHovered())
					{
						if (playSounds)
						{
							PlaySound(buttonBeep);
						}
						button[i].Hover();
					}
					if (button[i].GetButtonType()==elements::buttons::Selector::MENU)
					{
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
						{
							config::scenes::next_scene = config::scenes::SCENE::MENU;
						}
					}
					if (button[i].GetButtonType() == elements::buttons::Selector::PAUSE)
					{
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
						{
							isPaused = !isPaused;
						}
					}
					if (button[i].GetButtonType() == elements::buttons::Selector::RESET)
					{
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
						{
							ResetGame();
						}
					}
				}
				else
				{
					if (button[i].IsHovered())
					{
						button[i].UnHover();
					}
				}

			}
		}
		void CheckWinConditions() 
		{
			if (p1->GetScore() == pointLimit) 
			{
				p1->Won(true);
				isPaused = true;
			}

			if (p2->GetScore() == pointLimit) 
			{
				p2->Won(true);
				isPaused = true;
			}

			if (!winScreen.isActive)
			{
				if (p1->JustWon() || p2->JustWon())
				{
					WinScreenInit();
				}
			}

		}

		void DrawButtons()
		{
			for (short i = 0; i < howManyButtons; i++)
			{
				button[i].Draw();
			}
		}

		void DeinitButtons()
		{

		}

		void Score::SetScoreAsText()
		{
			text.tx = std::to_string(score);
		}

		void WinScreenInit() 
		{
			Color aux = Color();
			winScreen.isActive = true;
			if (p1->JustWon()) 
			{
				winScreen.Init(p1->GetText());
				aux = p1->GetColor();
			}
			if (p2->JustWon()) 
			{
				winScreen.Init(p2->GetText());
				aux = p2->GetColor();
			}

			winScreen.pos = Vec2(gameplayRec.x, gameplayRec.y);
			winScreen.width = gameplayRec.width;
			winScreen.height = gameplayRec.height;

			winScreen.backgroundColor = CreateColor(aux.r, aux.g, aux.b, 40);
			winScreen.frameColor = CreateColor(aux.r, aux.g, aux.b);
			winScreen.text.color = WHITE;

			winText.tx = "Wins";
			winText.size = fontSize;
			winText.color = WHITE;

			Vec2 a = MeasureTextEx(scoreFont, &winScreen.text.tx[0], fontSize, spacing);
			Vec2 b = MeasureTextEx(scoreFont, &winText.tx[0], fontSize, spacing);

			winScreen.text.pos = Vec2(gameplayRec.width / 2 - a.x / 2, gameplayRec.height / 2 - a.y / 2);
			winText.pos = Vec2(gameplayRec.width / 2 - b.x / 2, gameplayRec.height / 2 + b.y / 2);


		}
		void CheckWinScreenButtons()
		{

		}
		void DrawWinScreen()
		{
			DrawRectangleRec(winScreen.GetRec(), winScreen.backgroundColor);
			DrawRectangleLinesEx(winScreen.GetRec(), winScreen.frameWidth, winScreen.frameColor);
			winScreen.CenterText();
			DrawTextEx(scoreFont, &winScreen.text.tx[0], winScreen.text.pos.ToVector2(), fontSize, spacing, winScreen.text.color);

		}

	}

}