#ifndef AREA_H
#define AREA_H

#include "extern.h"

namespace pong
{
	class Area
	{
	private:
		Rectangle _rec;
		int _lineThickness;
		Color _color;
		const int lowAlpha = 40;
		const int highAlpha = 255;
	public:
		Area();
		~Area();
		
		void SetRec(Rectangle rec);
		void SetRec(int x, int y, int width, int height);
		void SetDim(Vec2 dim);
		void SetDim(int width, int height);
		void SetPos(Vec2 pos);
		void SetPos(int x, int y);
		void SetX(int x);
		void SetY(int y);
		void SetWidth(int width);
		void SetHeight(int heigth);
		void SetThickness(int t);
		void SetColor(Color c);
		void SetColor(int r, int g, int b, int a);
		void SetColor(int r, int g, int b);		

		Rectangle GetRec();
		Vec2 GetDim();
		Vec2 GetPos();
		int GetThicness();
		Color GetColor();

		void DrawAreaLines();
		void DrawArea();
		void DrawAreaTransparent();
		void DrawAreaTransparentWithLines();
	};
}

#endif // !AREA_H
