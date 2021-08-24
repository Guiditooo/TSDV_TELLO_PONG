#include <string>
#include "Scenes/Game/Player/player.h"

namespace pong {

	namespace game {

		const int palettePadding = 4;

		Player::Player() 
		{
			_rec = { 0 };
			_label = Text();
			_scale = 0;
			_axis = Axis::NONE;
			_scoreBoard = Letter();
		}
		Player::~Player(){}
		void Player::SetPosition(Vec2 position) 
		{ 
			_rec.x = position.x; 
			_rec.y = position.y; 
		}
		void Player::SetSpeed(Vec2 speed) { _speed = speed; }
		void Player::SetAxis(Axis axis) { _axis = axis; }
		void Player::SetColor(Color color) { _color = color; }
		void Player::SetText(std::string text) { _label.tx = text; }
		void Player::SetTextSize(int textSize) { _label.size = textSize; }
		void Player::SetTextColor(Color color) { _label.color = color; }
		void Player::SetTextPosition(Vec2 position) { _label.pos = position; }
		void Player::SetHeight(float height) { _rec.height = height; }
		void Player::SetWidth(float width) { _rec.width = width; }

		void Player::SetLetterPos(Vec2 pos) { _scoreBoard.pos = pos; }
		void Player::SetLetterWidth(int width) { _scoreBoard.width = width; }
		void Player::SetLetterHeight(int height) { _scoreBoard.height = height; }
		void Player::SetLetterBackgroundColor(Color background) { _scoreBoard.backgroundColor = background; }
		void Player::SetLetterFrameColor(Color frame) { _scoreBoard.frameColor = frame; }
		void Player::SetLetterTextColor(Color text) { _scoreBoard.text.color = text; }
		void Player::SetLetterFrameWidth(int frameWidth) { _scoreBoard.frameWidth = frameWidth; }
		void Player::SetLetterParameters(Vec2 pos, int width, int height)
		{
			_scoreBoard.height = height;
			_scoreBoard.width = width;
			_scoreBoard.pos = pos;
		}
		void Player::SetLetterColors(Color background, Color frame, Color text, int frameWidth)
		{
			_scoreBoard.text.color = text;
			_scoreBoard.frameColor = frame;
			_scoreBoard.backgroundColor = background;
			_scoreBoard.frameWidth = frameWidth;
		}

		void Player::SetActionKey(ACTIONKEYS index, KeyboardKey key) { _keys[static_cast<int>(index)] = key; }
		void Player::SetScore(int score) { _score = score; }
		void Player::Setside(SIDE side) { _side = side; }

		Vec2 Player::GetPosition() { return Vec2(_rec.x, _rec.y); }
		Vec2 Player::GetVelocity() { return _speed; }
		Axis Player::GetAxis() { return _axis; }
		Color Player::GetColor() { return _color; }
		std::string Player::GetText() { return _label.tx; }
		int Player::GetTextSize() { return _label.size; }
		Color Player::GetTextColor() { return _label.color; }
		Vec2 Player::GetTextPosition() { return _label.pos; }
		float Player::GetHeight() { return _rec.height; }
		float Player::GetWidth() { return _rec.width; }
		KeyboardKey Player::GetKey(ACTIONKEYS index) { return _keys[static_cast<int>(index)]; }
		int Player::GetScore() { return _score; }

		Vec2 Player::GetLetterPos() { return _scoreBoard.pos; }
		int Player::GetLetterWidth() { return _scoreBoard.width; }
		int Player::GetLetterHeight() { return _scoreBoard.height; }
		Color Player::GetLetterBackgroundColor() { return _scoreBoard.backgroundColor; }
		Color Player::GetLetterFrameColor() { return _scoreBoard.frameColor; }
		Color Player::GetLetterTextColor() { return _scoreBoard.text.color; }
		int Player::GetLetterFrameWidth() { return _scoreBoard.frameWidth; }
		Rectangle Player::GetRectangle() { return _rec; }
		SIDE Player::GetSide() { return _side; }

		void Player::MovePlayer() 
		{ 
			switch (_axis)
			{
			case pong::Axis::HORIZONTAL:
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::LEFT)])))
				{
					_rec.x -= _speed.x * GetFrameTime();
				}
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::RIGHT)])))
				{
					_rec.x += _speed.x * GetFrameTime();
				}
				break;
			case pong::Axis::VERTICAL:
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::UP)])))
				{
					_rec.y -= _speed.y * GetFrameTime();
				}
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::DOWN)])))
				{
					_rec.y += _speed.y * GetFrameTime();
				}
				break;
			case pong::Axis::BOTH:
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::LEFT)])))
				{
					_rec.x -= _speed.x * GetFrameTime();
				}
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::RIGHT)])))
				{
					_rec.x += _speed.x * GetFrameTime();
				}
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::UP)])))
				{
					_rec.y -= _speed.y * GetFrameTime();
				}
				if (IsKeyDown(static_cast<int>(_keys[static_cast<int>(ACTIONKEYS::DOWN)])))
				{
					_rec.y += _speed.y * GetFrameTime();
				}
				break;
			default:
				break;
			}
			//SetPosition(GetPosition() + _speed);
		}

		void Player::ChargeTextValue()
		{
			_scoreBoard.text.tx = std::to_string(_score);
		}

		void Player::AddOneToScore() { _score++; }

		void Player::SubOneToScore() { _score--; }

		void Player::DrawPlayer()
		{
			Rectangle aux = _rec;
			aux.width += palettePadding;
			aux.height += palettePadding;
			aux.x -= palettePadding/2;
			aux.y -= palettePadding/2;
			DrawRectangleRec(aux, _color);
			DrawRectangleRec(_rec, RAYWHITE);
		}

		void Player::DrawLetter()
		{
			ChargeTextValue();
			DrawRectangleRec(_scoreBoard.GetRec(), _scoreBoard.backgroundColor);
			DrawRectangleLinesEx(_scoreBoard.GetRec(), _scoreBoard.frameWidth, _scoreBoard.frameColor);
			_scoreBoard.CenterText();
			DrawTextEx(scoreFont, &_scoreBoard.text.tx[0], _scoreBoard.text.pos.ToVector2(), fontSize, spacing, _scoreBoard.text.color);
		}

	}

}