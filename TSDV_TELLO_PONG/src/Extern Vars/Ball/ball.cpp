#include "ball.h"

namespace pong {

	namespace elements {

		Collision::Collision()
		{
			_rotation = 0;
			_radius = 5;
			_scale = 1;
			_acceleration.zero;
			_speed.zero;
			_position.Set(config::screen::width / 2,config::screen::height / 2);
			_color = WHITE;
			_texture = Texture2D();
		}
		Collision::~Collision() {}

		int Collision::GetRotation() { return _rotation; }
		float Collision::GetRadius() { return _radius; }
		Vec2 Collision::GetBallAcceleration() { return _acceleration; }
		Vec2 Collision::GetBallSpeed() { return _speed; }
		Vec2 Collision::GetPosition() { return _position; }
		Vec2 Collision::GetBallCenter() 
		{
			return GetPosition()+GetRadius();
		}
		Texture2D Collision::GetTexture() { return _texture; }
		Color Collision::GetColor() { return _color; }
		Rectangle Collision::GetBallRectangle() { return { _position.x,_position.y,_radius*2,_radius*2 }; }


		void Collision::SetRotation(int rotation) { _rotation = rotation; }
		void Collision::SetRadius(float radius) 
		{
			_radius = radius; 
		
			_texture.height = _radius*2;
			_texture.width = _radius*2;
		
		}
		void Collision::SetBallAcceleration(Vec2 acceleration) { _acceleration.Set(acceleration); }
		void Collision::SetBallSpeed(Vec2 speed) { _speed.Set(speed); }
		void Collision::SetPosition(Vec2 position) { _position.Set(position); }
		void Collision::SetTexture(Texture2D texture) 
		{ 
			_texture = texture;

			_texture.height = _radius * 2;
			_texture.width = _radius * 2;
		}
		void Collision::SetColor(Color color) { _color = color; };

		void Collision::Init()
		{
			_texture = Texture2D();
			_texture.height = _radius*2;
			_texture.width = _radius*2;
		}
		void Collision::Draw() 
		{
			DrawCircle(GetBallCenter().x, GetBallCenter().y, _radius -1, _color);
			DrawTextureEx(_texture, _position.ToVector2(), _rotation, _scale, WHITE);
		}
		void Collision::Deinit() 
		{
			UnloadTexture(_texture);
		}
		
		void Collision::Move(float time)
		{
			SetPosition(_position + _speed * time);
		}

		void Collision::ApplyAcceleration(float time)
		{
			SetBallSpeed(_speed + (_acceleration * time));
			//std::cout << "\nSpeed: " << _speed.x << "|" << _speed.y << "\n";
		}

	}

}