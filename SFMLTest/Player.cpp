#include "Player.h"
#include <string>

Player::Player(sf::RenderWindow &w)
{
	score = 0;
	velocity = Vector2d();
	window = &w;

	sf::Texture* texture = new sf::Texture();
	if (texture->loadFromFile("Assets\\Texture\\Paddle.png"))
	{
		std::cout << "File loaded\n";
	}
	else
	{
		std::cout << "File not loaded\n";
	}

	sprite = sf::Sprite(*texture);

	x = 0;
	y = 0;
}

void Player::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f(x, y);
}

void Player::draw()
{
	sprite.setPosition(x - radius, y - radius);
	window->draw(sprite);

	/*sf::Texture t;
	t.loadFromFile("Assets\\Texture\\Paddle.png");
	sf::Sprite sp(t);
	sp.setPosition(x - radius, y - radius);
	window->draw(sp);*/
}

void Player::update(float x, float y)
{
	velocity.i = x - this->x;
	velocity.j = y - this->y;

	this->x = x;
	this->y = y;
}

void Player::updateScore()
{

}