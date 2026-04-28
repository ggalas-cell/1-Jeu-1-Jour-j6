#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Vector2f.h"

class InputManager
{



private:
	InputManager();
	static InputManager* instance;
	bool mKeyboardState[sf::Keyboard::KeyCount] = { false };
	bool mPrevKeyboardState[sf::Keyboard::KeyCount] = { false };

	bool mMouseState[sf::Mouse::ButtonCount] = { false };
	bool mPrevMouseState[sf::Mouse::ButtonCount] = { false };

	bool mControllerState[sf::Joystick::ButtonCount] = { false };
	bool mPrevControllerState[sf::Joystick::ButtonCount] = { false };

	float mJoystickAxis[sf::Joystick::AxisCount] = { 0.f };

	int mDeltaWheel;



	Vector2f mPrevMousePosition;
	Vector2f mMouseDelta;

	Vector2f GetMousePosition()
	{
		sf::Vector2i pos = sf::Mouse::getPosition();
		return Vector2f((float)pos.x, (float)pos.y);
	}

public:
	static InputManager* Get();

	void Update(sf::RenderWindow* _window); // utiliser GetDeltaTime() de GameManager

	bool IsKeyDown(sf::Keyboard::Key key);

	bool IsKeyHeld(sf::Keyboard::Key key);

	bool IsKeyReleased(sf::Keyboard::Key key);

	bool IsMouseDown(sf::Mouse::Button button);

	bool IsMouseHeld(sf::Mouse::Button button);

	bool IsMouseReleased(sf::Mouse::Button button);

	bool IsControllerDown(int button);

	bool IsControllerHeld(int button);

	bool IsControllerReleased(int button);

	float GetJoystickAxis(sf::Joystick::Axis axis);

	bool IsWheelUp();

	bool IsWheelDown();

	Vector2f GetMousePos();

	Vector2f GetMouseDelta();

};


