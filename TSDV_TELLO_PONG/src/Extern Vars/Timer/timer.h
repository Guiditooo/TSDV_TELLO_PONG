#ifndef ELEMENT_TIMER
#define ELEMENT_TIMER

#include "raylib.h"
#include "Extern Vars/extern.h"
#include <string>

namespace pong {

	namespace elements {

		namespace timer {

			const Vec2 padding = {
				2,//padding en X 
				2 //padding en Y
			};

			extern int timeLimit;

		}

		class Timer {
		public:
			Timer();
			~Timer();
			Rectangle GetRec();
			Vec2 GetTimerPosition();
			Vec2 GetTimerSize();
			int GetTextSize();
			bool isActive();
			bool isHovered();
			Texture2D GetTextureBack();
			Texture2D GetTextureFront();
			void SetActive(bool active);
			void SetScale(float scale);
			void SetTimerColor(Color color);
			void SetTextColor(Color color);
			void SetTextSize(int size);
			void SetTextureBack(Texture2D texture);
			void SetTextureFront(Texture2D texture);
			void SetText(std::string txt);
			void SetTimerPosition(Vec2 pos);
			void SetTimerSize(float width, float height);
			void AdjustTimerSize();
			void AdjustTextPos();
			void AdjustTextureSize();
			void AdjustAll();
			void UnloadTx();
			void LoadTx();
			void Draw();
		private:
			Rectangle _square;
			bool _selected;
			bool _active;
			bool _hovered;
			float _scale;
			Text _txt;
			Color _color;
			Texture2D _textureBack;
			Texture2D _textureFront;
		};

	}

}

#endif