#include <SFML/Audio.hpp>
#include "Component.h"

class Sound : public Component {
	sf::SoundBuffer mBuffer;
	sf::Sound mSound;

public:
	void Load(std::string fileName);
	void Play();
	void SetVolume(int volume);
};