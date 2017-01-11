#pragma once
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;

class SoundManager
{
private:
	sf::SoundBuffer edgeBuffer;
	sf::SoundBuffer playerBuffer;
	sf::SoundBuffer goalBuffer;
	sf::Sound edgeSound;
	sf::Sound playerSound;
	sf::Sound goalSound;

public:
	SoundManager();
	void PlayEdgeSound();
	void PlayPlayerSound();
	void PlayGoalSound();
};