#include "InputManager.h"
#include "Vector2f.h"
#include <SFML/Window.hpp>
#include <iostream>

InputManager* InputManager::instance = nullptr;

InputManager* InputManager::Get()
{
	if (instance == nullptr) {
		instance = new InputManager();
	}
	return instance;
}

InputManager::InputManager()
{
}

void InputManager::Update(sf::RenderWindow* _window)
{


	mMouseDelta = { 0.f,0.f };

	sf::Event event;
	while (_window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::JoystickConnected:
			std::cout << "Joystick Connected" << std::endl;
			break;
		case sf::Event::JoystickDisconnected:
			std::cout << "Joystick Disconnected" << std::endl;
			break;
		case sf::Event::Closed:
			_window->close();
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape) {
				_window->close();
			}
			break;

		case sf::Event::MouseWheelMoved:

			break;
		}


	}


	// sauvegarde clavier precedant
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		mPrevKeyboardState[i] = mKeyboardState[i];
		mKeyboardState[i] = sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i);
	}

	for (int i = 0; i < sf::Joystick::AxisCount; i++)
	{
		sf::Joystick::Axis a = (sf::Joystick::Axis)i;
		if (!sf::Joystick::hasAxis(0, a) || (sf::Joystick::getAxisPosition(0, a) >= -1.f && sf::Joystick::getAxisPosition(0, a) <= 1.f))
		{
			mJoystickAxis[i] = 0.f;
		}
		else
		{
			mJoystickAxis[i] = sf::Joystick::getAxisPosition(0, a);
		}
		
	}

	for (int i = 0; i < sf::Joystick::ButtonCount; i++)
	{
		mPrevControllerState[i] = mControllerState[i];
		mControllerState[i] = sf::Joystick::isButtonPressed(0, i);
	}

	mDeltaWheel = event.mouseWheelScroll.delta;
	if (mDeltaWheel > 1 || mDeltaWheel < -1) {
		mDeltaWheel = 0;
	}

	// savegarde souris precedante
	for (int i = 0; i < sf::Mouse::ButtonCount; i++)
	{
		mPrevMouseState[i] = mMouseState[i];
		mMouseState[i] = sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
	}

	// calcul du mouse delta
	Vector2f currentPos = { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y };
	mMouseDelta = Vector2f(
		(float)(currentPos.x - mPrevMousePosition.x),
		(float)(currentPos.y - mPrevMousePosition.y)
	);

	mPrevMousePosition = currentPos;
}

bool InputManager::IsKeyDown(sf::Keyboard::Key key)
{
	return mKeyboardState[key] && !mPrevKeyboardState[key];
}

bool InputManager::IsKeyHeld(sf::Keyboard::Key key)
{
	return mKeyboardState[key];
}

bool InputManager::IsKeyReleased(sf::Keyboard::Key key)
{
	return !mKeyboardState[key] && mPrevKeyboardState[key];
}

bool InputManager::IsMouseDown(sf::Mouse::Button button)
{
	return mMouseState[button] && !mPrevMouseState[button];
}

bool InputManager::IsMouseHeld(sf::Mouse::Button button)
{
	return mMouseState[button];
}

bool InputManager::IsMouseReleased(sf::Mouse::Button button)
{
	return !mMouseState[button] && mPrevMouseState[button];
}

bool InputManager::IsControllerDown(int button) {
	return mControllerState[button] && !mPrevControllerState[button];
}

bool InputManager::IsControllerHeld(int button){
	return mControllerState[button];
}

bool InputManager::IsControllerReleased(int button){
	return !mControllerState[button] && mPrevControllerState[button];
}

float InputManager::GetJoystickAxis(sf::Joystick::Axis axis) {
	return mJoystickAxis[axis] / 100.f;
}

Vector2f InputManager::GetMouseDelta()
{
	return mMouseDelta;
}

Vector2f InputManager::GetMousePos() {
	return mPrevMousePosition;
}

bool InputManager::IsWheelDown() { 
	return mDeltaWheel == -1; 
}

bool InputManager::IsWheelUp() { 
	return mDeltaWheel == 1; 
}