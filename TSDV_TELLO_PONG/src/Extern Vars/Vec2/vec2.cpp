#include "vec2.h"
#include <math.h>


namespace pong 
{

	namespace elements
	{

		#pragma region Vec2
		Vec2::Vec2()
		{
			x = 0;
			y = 0;
			magnitude = 0;
		}
		Vec2::Vec2(Vector2 v)
		{
			x = v.x;
			y = v.y;
			magnitude = sqrt(pow(x, 2) + pow(y, 2));
		}
		Vec2::Vec2(int _x, int _y)
		{
			x = _x;
			y = _y;
			magnitude = sqrt(pow(x, 2) + pow(y, 2));
		}
		Vec2::Vec2(int _x, float _y)
		{
			x = _x;
			y = _y;
			magnitude = sqrt(pow(x, 2) + pow(y, 2));
		}
		Vec2::Vec2(float _x, int _y)
		{
			x = _x;
			y = _y;
			magnitude = sqrt(pow(x, 2) + pow(y, 2));
		}
		Vec2::Vec2(float _x, float _y)
		{
			x = _x;
			y = _y;
			magnitude = sqrt(pow(x, 2) + pow(y, 2));
		}
		Vec2::~Vec2() {}

		float Vec2::Magnitude(Vec2 a) { return sqrt(pow(a.x, 2) + pow(a.y, 2)); }
		float Vec2::Dot(Vec2 a, Vec2 b) { return (a.x * b.x + a.y * b.y); }
		float Vec2::Distance(Vec2 a, Vec2 b) { return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)); }
		float Vec2::Angle(Vec2 from, Vec2 to)//Return distance in angles between 2 vectors
		{
			return (acos(sqrt(pow(to.x + from.y, 2) + pow(to.y + from.y, 2))) * RAD2DEG);
		}
		Vec2 Vec2::Project(Vec2 v, Vec2 norm)
		{
			return Vec2(norm * (Dot(v, norm) / (norm.magnitude * norm.magnitude)));
		}
		Vec2 Vec2::Reflect(Vec2 dir, Vec2 norm) //Hay fotitos
		{
			norm = Normalize(norm);
			return Vec2(-Project(dir, norm) * 2 + dir);
		}
		Vec2 Vec2::Lerp(Vec2 a, Vec2 b, float t) //Returns a value between 2 values, depends on time.
		{
			Vec2 j;
			if (t < 1 && t>0)
			{
				j.x = a.x * (1.0f - t) + (b.x * t);
				j.y = a.y * (1.0f - t) + (b.y * t);
			}
			return j;
		}
		Vec2 Vec2::Max(Vec2 a, Vec2 b) //Returns the max parameters of 2 vectors
		{
			Vec2 j;
			j.x = a.x >= b.x ? a.x : b.x;
			j.y = a.y >= b.y ? a.y : b.y;
			return j;
		}
		Vec2 Vec2::Min(Vec2 a, Vec2 b) //Returns the min parameters of 2 vectors
		{
			Vec2 j;
			j.x = a.x <= b.x ? a.x : b.x;
			j.y = a.y <= b.y ? a.y : b.y;
			return j;
		}
		Vec2 Vec2::Normalize(Vec2 a) { return (a / Magnitude(a)); }

		Vec2 Vec2::zero() { return { 0,0 }; }
		Vec2 Vec2::one() { return { 1,1 }; }

		void Vec2::Set(Vector2 v)
		{
			x = v.x;
			y = v.y;
		}
		void Vec2::Set(Vec2 v)
		{
			x = v.x;
			y = v.y;
		}
		void Vec2::Set(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
		void Vec2::Set(int _x, float _y)
		{
			x = _x;
			y = _y;
		}
		void Vec2::Set(float _x, int _y)
		{
			x = _x;
			y = _y;
		}
		void Vec2::Set(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		Vector2 Vec2::ToVector2()
		{
			return { x,y };
		}

		Vec2 Vec2::operator+(Vec2 b) { return Vec2(x + b.x, y + b.y); }
		Vec2 Vec2::operator+=(Vec2 b) { return Vec2(x + b.x, y + b.y); }
		Vec2 Vec2::operator+(float b) { return Vec2(x + b, y + b); }
		Vec2 Vec2::operator+=(float b) { return Vec2(x + b, y + b); }
		//Vec2 Vec2::operator++() { return Vec2(x + 1, y + 1); }

		Vec2 Vec2::operator-(Vec2 b) { return Vec2(x - b.x, y - b.y); }
		Vec2 Vec2::operator-() { return Vec2(-x, -y); }
		Vec2 Vec2::operator-=(Vec2 b) { return Vec2(x - b.x, y - b.y); }
		Vec2 Vec2::operator-(float b) { return Vec2(x - x, y - b); }
		Vec2 Vec2::operator-=(float b) { return Vec2(x - x, y - b); }
		//Vec2 Vec2::operator++() { return Vec2(x - 1, y - 1); }

		Vec2 Vec2::operator*(float b) { return Vec2(x * b, y * b); }
		Vec2 Vec2::operator*(Vec2 b) { return Vec2(x * b.x, y * b.y); }

		Vec2 Vec2::operator/(float b) { return Vec2(x / b, y / b); }	

#pragma endregion

		#pragma region Int2

		Int2::Int2()
		{
			x = 0;
			y = 0;
			magnitude = 0;
		}
		Int2::Int2(Vector2 v)
		{
			x = v.x;
			y = v.y;
			magnitude = Magnitude(Int2(x, y));
		}
		Int2::Int2(int _x, int _y)
		{
			x = _x;
			y = _y;
			magnitude = Magnitude(Int2(x, y));
		}
		Int2::Int2(int _x, float _y)
		{
			x = _x;
			y = _y;
			magnitude = Magnitude(Int2(x, y));
		}
		Int2::Int2(float _x, int _y)
		{
			x = _x;
			y = _y;
			magnitude = Magnitude(Int2(x, y));
		}
		Int2::Int2(float _x, float _y)
		{
			x = _x;
			y = _y;
			magnitude = Magnitude(Int2(x, y));
		}
		Int2::~Int2() {}

		float Int2::Magnitude(Int2 a) { return sqrt(pow(a.x, 2) + pow(a.y, 2)); }
		float Int2::Dot(Int2 a, Int2 b) { return (a.x * b.x + a.y * b.y); }
		float Int2::Distance(Int2 a, Int2 b) { return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)); }
		float Int2::Angle(Int2 from, Int2 to)//Return distance in angles between 2 vectors
		{
			return (acos(sqrt(pow(to.x + from.y, 2) + pow(to.y + from.y, 2))) * RAD2DEG);
		}
		Int2 Int2::Lerp(Int2 a, Int2 b, float t) //Returns a value between 2 values, depends on time.
		{
			Int2 j;
			if (t < 1 && t>0)
			{
				j.x = a.x * (1.0f - t) + (b.x * t);
				j.y = a.y * (1.0f - t) + (b.y * t);
			}
			return j;
		}
		Int2 Int2::Max(Int2 a, Int2 b) //Returns the max parameters of 2 vectors
		{
			Int2 j;
			j.x = a.x >= b.x ? a.x : b.x;
			j.y = a.y >= b.y ? a.y : b.y;
			return j;
		}
		Int2 Int2::Min(Int2 a, Int2 b) //Returns the min parameters of 2 vectors
		{
			Int2 j;
			j.x = a.x <= b.x ? a.x : b.x;
			j.y = a.y <= b.y ? a.y : b.y;
			return j;
		}
		Int2 Int2::Normalize(Int2 a) { return (a / Magnitude(a)); }

		Int2 Int2::zero() { return { 0,0 }; }
		Int2 Int2::one() { return { 1,1 }; }

		void Int2::Set(Vector2 v)
		{
			x = v.x;
			y = v.y;
		}
		void Int2::Set(Int2 v)
		{
			x = v.x;
			y = v.y;
		}
		void Int2::Set(int _x, int _y)
		{
			x = _x;
			y = _y;
		}
		void Int2::Set(int _x, float _y)
		{
			x = _x;
			y = _y;
		}
		void Int2::Set(float _x, int _y)
		{
			x = _x;
			y = _y;
		}
		void Int2::Set(float _x, float _y)
		{
			x = _x;
			y = _y;
		}

		Int2 Int2::operator+(Int2& b) { return Int2(x + b.x, y + b.y); }
		Int2 Int2::operator+(float b) { return Int2(x + b, y + b); }

		Int2 Int2::operator-(Int2& b) { return Int2(x - b.x, y - b.y); }
		Int2 Int2::operator-(float b) { return Int2(x - x, y - b); }

		Int2 Int2::operator*(float b) { return Int2(x * b, y * b); }

		Int2 Int2::operator/(float b) { return Int2(x / b, y / b); }

		bool Int2::operator==(Int2& b) { return (x == b.x && y == b.y); }
		bool Int2::operator!=(Int2& b) { return !(x == b.x && y == b.y); }

#pragma endregion

}

}