#include <SFML/Audio.hpp>
#include "Component.h"

class Music : public Component {
	sf::Music mMusic;

public:
	void Load(std::string fileName, bool isLoop);
	void Play();
	void Pause();
	void Stop();
	void SetVolume(int volume);

};