#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Vector2d.h"

enum MoveState {
	MS_STOP,
	MS_LEFT,
	MS_RIGHT
};

class Player 
{
public:
	const int radius = 35.f;

	int score;
	Vector2d velocity;
	double x, y;

	sf::RenderWindow* window;
	sf::Sprite sprite;

public:
	Player(sf::RenderWindow &w);

	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void draw();
	void update(float x, float y);
	void updateScore();
};

#endif // !PLAYER_H
