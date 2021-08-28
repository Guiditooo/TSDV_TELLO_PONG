#include "area.h"

namespace pong
{
	Area::Area()
	{
		_rec = Rectangle();
		_lineThickness = 1;
		_color = BLACK;
	}
	Area::~Area(){}

	void Area::SetRec(Rectangle rec)
	{
		_rec.height = rec.height;
		_rec.width = rec.width;
		_rec.x = rec.x;
		_rec.y = rec.y;
	}
	void Area::SetRec(int x,  int y, int width, int height)
	{
		_rec.height =height;
		_rec.width = width;
		_rec.x = x;
		_rec.y = y;
	}
	void Area::SetDim(Vec2 dim)
	{
		_rec.width = dim.x;
		_rec.height = dim.y;
	}
	void Area::SetDim(int width, int height)
	{
		_rec.width = width;
		_rec.height = height;
	}
	void Area::SetPos(Vec2 pos)
	{
		_rec.x = pos.x;
		_rec.y = pos.y;
	}
	void Area::SetPos(int x, int y)
	{
		_rec.y = y;
		_rec.x = x;
	}
	void Area::SetX(int x)
	{
		_rec.x = x;
	}
	void Area::SetY(int y)
	{
		_rec.y = y;
	}
	void Area::SetWidth(int width)
	{
		_rec.width = width;
	}
	void Area::SetHeight(int heigth)
	{
		_rec.height = heigth;
	}
	void Area::SetThickness(int t)
	{
		_lineThickness = t;
	}
	void Area::SetColor(Color c)
	{
		_color = c;
	}
	void Area::SetColor(int r, int g, int b, int a)
	{
		_color = CreateColor(r, g, b, a);
	}
	void Area::SetColor(int r, int g, int b)
	{
		_color = CreateColor(r, g, b);
	}

	Rectangle Area::GetRec()
	{
		return _rec;
	}
	Vec2 Area::GetDim() 
	{
		return Vec2(_rec.width, _rec.height);
	}
	Vec2 Area::GetPos()
	{
		return Vec2(_rec.x, _rec.y);
	}
	int Area::GetThicness()
	{
		return _lineThickness;
	}
	Color Area::GetColor()
	{
		return _color;
	}

	void Area::DrawAreaLines()
	{
		DrawRectangleLinesEx(_rec, _lineThickness, _color);
	}
	void Area::DrawArea()
	{
		DrawRectangleRec(_rec, _color);
	}
	void Area::DrawAreaTransparent()
	{
		Color aux = _color;
		aux.a = lowAlpha;
		DrawRectangleRec(_rec, aux);
	}
	void Area::DrawAreaTransparentWithLines()
	{
		DrawAreaTransparent();
		DrawAreaLines();
	}
}