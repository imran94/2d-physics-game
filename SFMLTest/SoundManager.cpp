#include "SoundManager.h"


SoundManager::SoundManager()
{
	if (edgeBuffer.loadFromFile("Assets\\Audio\\EdgeHit.ogg"))
	{
		std::cout << "Audio 1 loaded\n";
	}
	else
	{
		std::cout << "Audio 1 not loaded\n";
	}
	if (playerBuffer.loadFromFile("Assets\\Audio\\PlayerHit.ogg"))
	{
		std::cout << "Audio 2 loaded\n";
	}
	else
	{
		std::cout << "Audio 2 not loaded\n";
	}
	if (goalBuffer.loadFromFile("Assets\\Audio\\Goal.ogg"))
	{
		std::cout << "Audio 3 loaded\n";
	}
	else
	{
		std::cout << "Audio 3 not loaded\n";
	}
}

void SoundManager::PlayEdgeSound()
{
	edgeSound.setBuffer(edgeBuffer);
	edgeSound.setVolume(100);
	edgeSound.play();
}

void SoundManager::PlayPlayerSound()
{
	playerSound.setBuffer(playerBuffer);
	playerSound.setVolume(100);
	playerSound.play();
}
void SoundManager::PlayGoalSound()
{
	goalSound.setBuffer(goalBuffer);
	goalSound.setVolume(200);
	goalSound.play();
}
