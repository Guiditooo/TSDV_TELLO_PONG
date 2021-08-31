#ifndef ELEMENT_BALL
#define ELEMENT_BALL

#include "Extern Vars/extern.h"
#include "Extern Vars/Vec2/vec2.h"

namespace pong {

	namespace elements {

		class Ball 
		{
		public:
			Ball();
			~Ball();

			int GetRotation();
			float GetRadius();
			Vec2 GetBallAcceleration();
			Vec2 GetBallSpeed();
			Vec2 GetPosition();
			Vec2 GetBallCenter();
			Texture2D GetTexture();
			Color GetColor();
			Rectangle GetBallRectangle();

			void SetRotation(int rotation);
			void SetRadius(float radius);
			void SetBallAcceleration(Vec2 acceleration);
			void SetBallSpeed(Vec2 speed);
			void SetPosition(Vec2 position);
			void SetTexture(Texture2D texture);
			void SetColor(Color color);

			void Init();
			void Draw();
			void Deinit();

			void Move(float time);
			void ApplyAcceleration(float time);
			void CorrectBallPosition();

		private:
			int _rotation;
			float _radius;
			float _scale;
			Vec2 _acceleration;
			Vec2 _speed;
			Vec2 _position;
			Texture2D _texture;
			Color _color;
		};

	}

}

#endif