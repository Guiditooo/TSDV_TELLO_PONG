#include "button.h"

namespace pong {

	namespace elements {

		Button::Button() {
			_square = Rectangle();
			_selected = false;
			_active = false;
			_hovered = false;
			_scale = 1;
			_txt.tx = "idle";
			_color = WHITE;
		}
		Button::~Button() {}

#pragma region GET
		Rectangle Button::GetRec() { return _square; }
		Vec2 Button::GetButtonPosition() { return { _square.x,_square.y }; }
		Vec2 Button::GetTextPos() { return _txt.pos; }
		Vec2 Button::GetButtonSize() { return { _square.width,_square.height }; }
		std::string Button::GetText() { return _txt.tx; }
		int Button::GetTextSize() { return _txt.size; }
		Texture2D Button::GetBackgroundTexture() { return _backgroundTexture; }
		Texture2D Button::GetBorderTexture() { return _borderTexture; }
		bool Button::IsActive() { return _active; }
		bool Button::IsHovered() { return _hovered; }
		bool Button::IsSelected() { return _selected; }
		buttons::Selector Button::GetButtonType() { return _buttonType; }
#pragma endregion

#pragma region SET
		void Button::SetButtonType(buttons::Selector type) { _buttonType = type; }
		void Button::SetActive(bool active) { _active = active; }
		void Button::SetScale(float scale) { _scale = scale; }
		void Button::SetButtonColor(Color color) { _color = color; }
		void Button::SetTextColor(Color color) { _txt.color = color; }
		void Button::SetHovered(bool hover) { _hovered = hover; }
		void Button::SetTextSize(int size) { _txt.size = size; }
		void Button::SetBackgroundTexture(Texture2D texture) { _backgroundTexture = texture; }
		void Button::SetBorderTexture(Texture2D texture) { _borderTexture = texture; }
		void Button::SetText(std::string txt) 
		{ 
			_txt.tx = txt;
			AdjustAll();
		}
		void Button::SetTextPos(Vec2 pos)
		{
			_txt.pos = pos;
		}
		void Button::SetButtonPosition(Vec2 pos)
		{
			_square.x = pos.x;
			_square.y = pos.y;

			AdjustTextPos();
			AdjustTextureSize();

		}
		void Button::SetButtonSize(float width, float height)
		{
			_square.width = width;
			_square.height = height;
		}
#pragma endregion

#pragma region OTHER
		void Button::UnloadTx() 
		{ 
			UnloadTexture(GetBackgroundTexture()); 
			UnloadTexture(GetBorderTexture()); 
		}
		void Button::LoadTx()
		{
			std::cout << "\n";
			_backgroundTexture = LoadTexture("res/assets/Buttons/Button.png");
			AdjustAll();
		}
		void Button::AdjustButtonSize()
		{
			Vec2 aux = MeasureTextEx(font, &_txt.tx[0], _txt.size, spacing);
			_square.width = aux.x * buttons::padding.x;
			_square.height = aux.y * buttons::padding.y;
		}
		void Button::AdjustTextPos()
		{
			Vec2 aux = MeasureTextEx(font, &_txt.tx[0], _txt.size, spacing);
			Vec2 buttonPos = GetButtonPosition();
			_txt.pos.x = buttonPos.x + GetButtonSize().x / 2 - aux.x / 2;
			_txt.pos.y = buttonPos.y + GetButtonSize().y / 2 - aux.y * 4 / 10;
		}
		void Button::AdjustTextureSize()
		{
			_backgroundTexture.width = _square.width;
			_backgroundTexture.height = _square.height;

			_borderTexture.width = _square.width;
			_borderTexture.height = _square.height;
		}
		void Button::AdjustAll()
		{
			AdjustButtonSize();
			AdjustTextPos();
			AdjustTextureSize();
		}
		void Button::Draw()
		{
			DrawTextureEx(_backgroundTexture, { _square.x,_square.y }, 0, _scale, _color);
			DrawTextureEx(_borderTexture, { _square.x,_square.y }, 0, _scale, _color);
			DrawTextEx(font, &_txt.tx[0], _txt.pos.ToVector2(), _txt.size, spacing, _txt.color);
		}
		void Button::Hover()
		{
			SetTextSize(GetTextSize() + 5);
			AdjustAll();
			_hovered = true;
		}
		void Button::UnHover()
		{
			SetTextSize(GetTextSize() - 5);
			AdjustAll();
			_hovered = false;
		}

		void Button::MakeStandardButton()
		{
			_square.width = 120;
			_square.height = 40;
			_square.x = 0;
			_square.y = 0; 

			_txt.tx = "idle";
			SetTextSize(_square.height);

			_borderTexture = LoadTexture("res/assets/Buttons/border.png");
			_backgroundTexture = LoadTexture("res/assets/Buttons/background.png");

			AdjustTextureSize();
			AdjustTextPos();

			_color = WHITE;
		}
		void Button::Select()
		{
			_selected = true;
		}
		void Button::DeSelect()
		{
			_selected = false;
		}

#pragma endregion

	}

}