// SFMLTest.cpp : Defines the entry point for the console application.
//
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "AIPlayer.h"
#include "Puck.h"

void checkCollision(Player &player, Puck &puck)
{
	puck.checkCollision(player);

	double distance = std::sqrt(std::pow(puck.x - player.x, 2) + std::pow(puck.y - player.y, 2));
	if (distance<std::sqrt(std::pow(puck.radius + player.radius, 2)))
	{
		puck.x = (puck.x - player.x)*(puck.radius + player.radius) / distance + player.x;
		puck.y = (puck.y - player.y)*(puck.radius + player.radius) / distance + player.y;
	}
}

void update(sf::RenderWindow &window, Player &player1, AIPlayer &player2, Puck &puck)
{
		
	if (puck.checkBottomGoal())
	{
		puck.reset();
		player2.score++;
	}
	else if (puck.checkTopGoal())
	{
		puck.reset();
		player1.score++;
	}

	puck.update();
	player2.move(puck);

	if (window.hasFocus())
	{
		int x = sf::Mouse::getPosition(window).x;
		int y = sf::Mouse::getPosition(window).y;

		if (y >= window.getSize().y / 2)
		{
			player1.update(x, y);
		}
	}
	checkCollision(player1, puck);
	checkCollision(player2, puck);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(320, 480, 32), "Air Hockey");

	window.setFramerateLimit(60);

	Player player1(window);
	AIPlayer player2(window);
	Puck puck(window);

	sf::Texture texture;
	texture.loadFromFile("Assets\\Texture\\Board2.png");
	sf::Sprite background(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					if (event.type == sf::Event::Closed)
						window.close();
					break;
				case sf::Event::Resized:
					std::cout << "Resized x:" << event.size.width << " y: " << event.size.height << "\n";
					break;
			}
		}

		update(window, player1, player2, puck);

		window.clear();

		window.draw(background);
		player1.draw();
		player2.draw();
		puck.draw();
		window.display();
	}
    return 0;
}
