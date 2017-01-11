#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "Player.h"
#include "Puck.h"

class AIPlayer : public Player
{
	const int offset = 70;

public:
	AIPlayer(sf::RenderWindow &w);
	void move(Puck puck);
	~AIPlayer();
};


#endif