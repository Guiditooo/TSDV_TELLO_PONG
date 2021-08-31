#ifndef ELEMENT_BUTTON
#define ELEMENT_BUTTON

#include "raylib.h"
#include "Extern Vars/extern.h"

namespace pong{

	namespace elements {

		namespace buttons {

			const Vec2 padding = Vec2(
				1.4f,//padding en X 
				1.5f //padding en Y
			);

			enum class Selector
			{
				MENU,
				RESET,
				PAUSE,
				GAME,
				CREDITS,
				CONFIG,
				MUSIC,
				SOUND,
			};

		}

		class Button {
		public:
			Button();
			~Button();
			Rectangle GetRec();
			Vec2 GetButtonPosition();
			Vec2 GetButtonSize();
			int GetTextSize();
			Vec2 GetTextPos();
			std::string GetText();
			bool IsActive();
			bool IsHovered();
			bool IsSelected();
			Texture2D GetBackgroundTexture();
			Texture2D GetBorderTexture();
			buttons::Selector GetButtonType();
			
			void SetButtonType(buttons::Selector type);
			void SetActive(bool active);
			void SetScale(float scale);
			void SetButtonColor(Color color);
			void SetTextColor(Color color);
			void SetTextSize(int size);
			void SetTextPos(Vec2 pos);
			void SetBackgroundTexture(Texture2D texture);
			void SetBorderTexture(Texture2D texture);
			void SetText(std::string txt);
			void SetHovered(bool hover);
			void SetButtonPosition(Vec2 pos);
			void SetButtonSize(float width, float height);

			void AdjustButtonSize();
			void AdjustTextPos();
			void AdjustTextureSize();
			void AdjustAll();
			void UnloadTx();
			void LoadTx();
			void Draw();
			void Hover();
			void UnHover();
			void MakeStandardButton();
			void Select();
			void DeSelect();
		private:
			Rectangle _square;
			bool _selected;
			bool _active;
			bool _hovered;
			float _scale;
			Text _txt;
			Color _color;
			Texture2D _backgroundTexture;
			Texture2D _borderTexture;
			buttons::Selector _buttonType;
		};

	}

}
#endif