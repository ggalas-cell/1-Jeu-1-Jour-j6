#pragma once

namespace sf
{
	class RenderWindow;
}

class Drawable
{
public:
	virtual void Draw(sf::RenderWindow* _window) = 0;
};

