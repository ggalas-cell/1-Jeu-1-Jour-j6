#pragma once
#include <SFML/Graphics.hpp>
#include "Vector2f.h"
namespace sf
{
	class Transformable;
}

enum Flip
{
	FLIP_NONE = 0,
	FLIP_HORIZONTAL,
	FLIP_VERTICAL

};

class Transformable : public sf::Transformable
{
protected:
	Flip mFlip;
	Vector2f m_rotationCenter = { -1, -1 };
public:
	Transformable(Vector2f _pos)
	{
		setPosition(_pos.x, _pos.y);
		mFlip = FLIP_NONE;
	}

	Vector2f GetOrigin() { return { getOrigin().x, getOrigin().y }; }
	void SetOrigin(int _x, int _y) { setOrigin(_x, _y); }
	void SetOrigin(Vector2f _pos) { setOrigin(_pos); }

	Vector2f GetPos() { return { getPosition().x, getPosition().y } ; }
	void SetPos(float _x, float _y) { SetPos(Vector2f{ _x, _y }); }
	void SetPos(Vector2f _pos) { setPosition(_pos); }

	Vector2f GetScale() { return {getScale().x, getScale().y  }; }
	void SetScale(float _x, float _y) { setScale(_x, _y); }
	void SetScale(Vector2f _pos) { setScale(_pos); }

	Flip GetFlip() { return mFlip; }
	void SetFlip(Flip _flip)
	{
		mFlip = _flip;

		Vector2f scale = GetScale();

		if (_flip == FLIP_HORIZONTAL)
			setScale(-abs(scale.x), abs(scale.y));
		else if (_flip == FLIP_VERTICAL)
			setScale(abs(scale.x), -abs(scale.y));
		else
			setScale(abs(scale.x), abs(scale.y));
	}

	float GetRotation() { return getRotation(); }
	void SetRotation(float _angle) { setRotation(_angle); }
	void AddRotation(float _angle) { rotate(_angle); }

	Vector2f GetRotationCenter() { return m_rotationCenter; }
	void SetRotationCenter(float _x, float _y) { m_rotationCenter = { _x, _y }; }
	void SetRotationCenter(Vector2f _vect) { m_rotationCenter = _vect; }

	void Translate(float _dx, float _dy) { move(_dx, _dy); }
	void Translate(Vector2f _vect) { move(_vect); }

	void ResetTransform()
	{
		setPosition(0, 0);
		setRotation(0);
		setScale(1, 1);
		setOrigin(0, 0);
		mFlip = FLIP_NONE;
	}
};
