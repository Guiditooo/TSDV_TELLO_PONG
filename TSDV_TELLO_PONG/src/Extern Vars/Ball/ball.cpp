#include "ball.h"

namespace pong {

	namespace elements {

		Ball::Ball()
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
		Ball::~Ball() {}

		int Ball::GetRotation() { return _rotation; }
		float Ball::GetRadius() { return _radius; }
		Vec2 Ball::GetBallAcceleration() { return _acceleration; }
		Vec2 Ball::GetBallSpeed() { return _speed; }
		Vec2 Ball::GetPosition() { return _position; }
		Vec2 Ball::GetBallCenter() 
		{
			return GetPosition()+GetRadius();
		}
		Texture2D Ball::GetTexture() { return _texture; }
		Color Ball::GetColor() { return _color; }
		Rectangle Ball::GetBallRectangle() { return { _position.x,_position.y,_radius*2,_radius*2 }; }


		void Ball::SetRotation(int rotation) { _rotation = rotation; }
		void Ball::SetRadius(float radius) 
		{
			_radius = radius; 
		
			_texture.height = _radius*2;
			_texture.width = _radius*2;
		
		}
		void Ball::SetBallAcceleration(Vec2 acceleration) { _acceleration.Set(acceleration); }
		void Ball::SetBallSpeed(Vec2 speed) { _speed.Set(speed); }
		void Ball::SetPosition(Vec2 position) { _position.Set(position); }
		void Ball::SetTexture(Texture2D texture) 
		{ 
			_texture = texture;

			_texture.height = _radius * 2;
			_texture.width = _radius * 2;
		}
		void Ball::SetColor(Color color) { _color = color; };

		void Ball::Init()
		{
			//_texture = Texture2D();
			_texture.height = _radius*2;
			_texture.width = _radius*2;
		}
		void Ball::Draw() 
		{
			DrawCircle(GetBallCenter().x, GetBallCenter().y, _radius -1, _color);
			DrawTextureEx(_texture, _position.ToVector2(), _rotation, _scale, WHITE);
		}
		void Ball::Deinit() 
		{
			UnloadTexture(_texture);
		}
		
		void Ball::Move(float time)
		{
			SetPosition(_position + _speed * time);
		}

		void Ball::ApplyAcceleration(float time)
		{
			SetBallSpeed(_speed + (_acceleration * time));
			//std::cout << "\nSpeed: " << _speed.x << "|" << _speed.y << "\n";
		}

	}

}