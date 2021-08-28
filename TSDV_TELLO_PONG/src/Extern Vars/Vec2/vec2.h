#ifndef VEC2
#define VEC2

#include "raylib.h"

namespace pong {

	namespace elements {

		struct Vec2
		{
		public:

			float x;
			float y;
			
			float magnitude;

			Vec2();
			Vec2(Vector2 v);
			Vec2(int _x, int _y);
			Vec2(int _x, float _y);
			Vec2(float _x, int _y);
			Vec2(float _x, float _y);
			~Vec2();

			Vec2 Lerp(Vec2 a , Vec2 b, float t);
			float Angle(Vec2 a, Vec2 b);
			float Magnitude(Vec2 a);
			float Dot(Vec2 a, Vec2 b);
			float Distance(Vec2 a, Vec2 b);
			Vec2 Project(Vec2 v, Vec2 norm);
			Vec2 Reflect(Vec2 dirv, Vec2 norm);
			Vec2 Max(Vec2 a, Vec2 b);
			Vec2 Min(Vec2 a, Vec2 b);
			Vec2 Normalize(Vec2 a);

			void Set(Vector2 v);
			void Set(Vec2 v);
			void Set(int _x, int _y);
			void Set(int _x, float _y);
			void Set(float _x, int _y);
			void Set(float _x, float _y);

			Vector2 ToVector2();

			static Vec2 zero();
			static Vec2 one();

			Vec2 operator+(Vec2 b);
			Vec2 operator+=(Vec2 b);
			Vec2 operator+(float num);
			Vec2 operator+=(float num);
			//Vec2 operator++();
						 
			Vec2 operator-(Vec2 b);
			Vec2 operator-=(Vec2 b);
			Vec2 operator-(float num);
			Vec2 operator-=(float num);
			Vec2 operator-();

			Vec2 operator*(float b);
			Vec2 operator*(Vec2 b);
			Vec2 operator/(float b);

		};


		struct Int2
		{
		public:

			int x;
			int y;

			float magnitude;
			const float k = 0.000001f;

			Int2();
			Int2(Vector2 v);
			Int2(int _x, int _y);
			Int2(int _x, float _y);
			Int2(float _x, int _y);
			Int2(float _x, float _y);
			~Int2();

			Int2 Lerp(Int2 a, Int2 b, float t);
			float Angle(Int2 a, Int2 b);
			float Magnitude(Int2 a);
			float Dot(Int2 a, Int2 b);
			float Distance(Int2 a, Int2 b);
			Int2 Max(Int2 a, Int2 b);
			Int2 Min(Int2 a, Int2 b);
			Int2 Normalize(Int2 a);

			void Set(Vector2 v);
			void Set(Int2 v);
			void Set(int _x, int _y);
			void Set(int _x, float _y);
			void Set(float _x, int _y);
			void Set(float _x, float _y);

			static Int2 zero();
			static Int2 one();

			Int2 operator+(Int2& b);
			Int2 operator+(float num);

			Int2 operator-(Int2& b);
			Int2 operator-(float num);
			Int2 operator*(float b);
			Int2 operator/(float b);
			bool operator==(Int2& b);
			bool operator!=(Int2& b);

		};

	}

}

#endif