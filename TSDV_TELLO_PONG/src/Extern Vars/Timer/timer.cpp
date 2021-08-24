#include "timer.h"

namespace pong {

	namespace elements {

		namespace timer {
			int timeLimit = 120;
		}

		Timer::Timer() {
			_square = { 0,0,0,0 };
			_selected = false;
			_active = false;
			_hovered = false;
			_scale = 1;
			_txt.tx = "idle";
			_color = WHITE;
		}
		Timer::~Timer() {}

#pragma region GET
		Rectangle Timer::GetRec() { return _square; }
		Vec2 Timer::GetTimerPosition() { return { _square.x,_square.y }; }
		Vec2 Timer::GetTimerSize() { return { _square.width,_square.height }; }
		int Timer::GetTextSize() { return _txt.size; }
		Texture2D Timer::GetTextureBack() { return _textureBack; }
		Texture2D Timer::GetTextureFront() { return _textureFront; }
		bool Timer::isActive() { return _active; }
		bool Timer::isHovered() { return _hovered; }
#pragma endregion

#pragma region SET
		void Timer::SetActive(bool active) { _active = active; }
		void Timer::SetScale(float scale) { _scale = scale; }
		void Timer::SetTimerColor(Color color) { _color = color; }
		void Timer::SetTextColor(Color color) { _txt.color = color; }
		void Timer::SetTextSize(int size) { _txt.size = size; }
		void Timer::SetTextureBack(Texture2D texture) { _textureBack = texture; }
		void Timer::SetTextureFront(Texture2D texture) { _textureFront = texture; }
		void Timer::SetText(std::string txt) { _txt.tx = txt; }
		void Timer::SetTimerPosition(Vec2 pos)
		{
			_square.x = pos.x;
			_square.y = pos.y;

			AdjustTextPos();
			AdjustTextureSize();

		}
		void Timer::SetTimerSize(float width, float height)
		{
			_square.width = width;
			_square.height = height;
		}
#pragma endregion

#pragma region OTHER
		void Timer::UnloadTx()
		{
			UnloadTexture(_textureBack);
			UnloadTexture(_textureFront);
		}
		void Timer::LoadTx()
		{
			std::cout << "\n";
			_textureBack = LoadTexture("res/assets/Timer/back.png");
			_textureFront = LoadTexture("res/assets/Timer/front.png");
			std::cout << "\n";
			AdjustAll();
		}
		void Timer::AdjustTimerSize()
		{
			_square.width = config::screen::width / 7;
			_square.height = config::screen::height / 10;
		}
		void Timer::AdjustTextPos()
		{
			Vec2 aux = MeasureTextEx(font, &_txt.tx[0], _txt.size, spacing);
			Vec2 buttonPos = GetTimerPosition();
			_txt.pos.x = buttonPos.x + GetTimerSize().x / 2 - aux.x / 2 + 5;
			_txt.pos.y = buttonPos.y + GetTimerSize().y / 2 - aux.y * 4 / 10;
		}
		void Timer::AdjustTextureSize()
		{
			_textureFront.width = _square.width;
			_textureBack.width = _square.width;
			_textureFront.height = _square.height;
			_textureBack.height = _square.height;
		}
		void Timer::AdjustAll()
		{
			AdjustTimerSize();
			AdjustTextPos();
			AdjustTextureSize();
		}
		void Timer::Draw()
		{
			DrawTextureEx(_textureBack, { _square.x,_square.y }, 0, _scale, _color);
			DrawTextureEx(_textureFront, { _square.x,_square.y }, 0, _scale, _color);
			DrawTextEx(font, &_txt.tx[0], _txt.pos.ToVector2(), _txt.size, spacing, _txt.color);
		}

#pragma endregion

	}

}