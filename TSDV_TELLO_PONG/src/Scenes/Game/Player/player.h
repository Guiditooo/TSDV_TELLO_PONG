#ifndef ELEMENT_PLAYER
#define ELEMENT_PLAYER

#include "raylib.h"
#include "Extern Vars/extern.h"
#include "Extern Vars/Vec2/vec2.h"

namespace pong {

	namespace game {

		class Player {
		public:

			Player();
			~Player();
			void SetPosition(Vec2 position);
			void SetSpeed(Vec2 speed);
			void SetAxis(Axis axis);
			void SetColor(Color color);
			void SetText(std::string text);
			void SetTextSize(int textSize);
			void SetTextColor(Color color);
			void SetTextPosition(Vec2 position);
			void SetHeight(float height);
			void SetWidth(float width);
			void SetLetterPos(Vec2 pos);
			void SetLetterWidth(int width);
			void SetLetterHeight(int height);
			void SetLetterBackgroundColor(Color background);
			void SetLetterFrameColor(Color frame);
			void SetLetterTextColor(Color text);
			void SetLetterFrameWidth(int frameWidth);
			void SetLetterParameters(Vec2 pos, int width, int height);
			void SetLetterColors(Color background, Color frame, Color text, int frameWidth);
			void SetActionKey(ACTIONKEYS index, KeyboardKey key);
			void SetScore(int score);
			void Setside(SIDE side);

			Vec2 GetPosition();
			Vec2 GetVelocity();
			Axis GetAxis();
			Color GetColor();
			std::string GetText();
			int GetTextSize();
			Color GetTextColor();
			Vec2 GetTextPosition();
			float GetHeight();
			float GetWidth();
			Vec2 GetLetterPos();
			int GetLetterWidth();
			int GetLetterHeight();
			Color GetLetterBackgroundColor();
			Color GetLetterFrameColor();
			Color GetLetterTextColor();
			int GetLetterFrameWidth();
			KeyboardKey GetKey(ACTIONKEYS index);
			int GetScore();
			Rectangle GetRectangle();
			SIDE GetSide();

			void MovePlayer();
			void ChargeTextValue();
			void AddOneToScore();
			void SubOneToScore();
			void DrawPlayer();
			void DrawLetter();

		private:
			Letter _scoreBoard;
			int _score;
			Rectangle _rec;
			Vec2 _speed;
			float _scale;
			Text _label;
			Color _color;
			Axis _axis;
			SIDE _side;
			KeyboardKey _keys[actionKeysCount];
		};

	}

}
#endif