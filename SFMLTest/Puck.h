#pragma once
#ifndef PUCK_H
#define PUCK_H

#include <SFML/Graphics.hpp>
#include "Vector2d.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "SoundManager.h"

class Puck
{
public:
	int WINDOW_WIDTH, WINDOW_HEIGHT;

	const int leftBound = 100;
	const int rightBound = 220;
	const int radius = 15;

	Vector2d velocity;
	double x, y;

	sf::RenderWindow* window;
	sf::Sprite sprite;
	
public:
	Puck(sf::RenderWindow &w);

	void setPosition(double x, double y);
	sf::Vector2f getPosition();
	
	void draw();
	void update();
	void reset();
	bool checkCollision(Player p);
	bool checkTopGoal();
	bool checkBottomGoal();

	~Puck();
};

#endif // !PUCK_HD
