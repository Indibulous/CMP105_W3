#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	// Moving circle definition
	circle.setRadius(15);
	circle.setPosition(300, 300);
	circle.setFillColor(sf::Color(10, 200, 50));
	circle.setOutlineColor(sf::Color(30, 100, 70));
	circle.setOutlineThickness(2.f);

	speedIncrement = 50.f;
	moveSpeed = 200.f;
	xSpeed = 0.f;
	ySpeed = 0.f;
	speedMultiplier = 1.f;
	autoMove = false;

	// Circle Position Indicator
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	circlePos.setFont(font);
	circlePos.setPosition(0, 0);
	circlePos.setCharacterSize(24);
	circlePos.setFillColor(sf::Color(255, 255, 255, 255));

	// Circle Speed Indicator
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}
	circleSpeed.setFont(font);
	circleSpeed.setPosition(0, 24);
	circleSpeed.setCharacterSize(24);
	circleSpeed.setFillColor(sf::Color(255, 255, 255, 255));


}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	// auto move toggle
	if (input->isKeyDown(sf::Keyboard::M))
	{
		input->setKeyUp(sf::Keyboard::M);
		autoMove = !autoMove;
		xSpeed = moveSpeed;
		ySpeed = moveSpeed;
	}

	// movement controls
	if (!autoMove)
	{
		if (input->isKeyDown(sf::Keyboard::Down) && !input->isKeyDown(sf::Keyboard::Up))
		{
			ySpeed = moveSpeed;
		}
		else if (input->isKeyDown(sf::Keyboard::Up) && !input->isKeyDown(sf::Keyboard::Down))
		{
			ySpeed = -moveSpeed;
		}
		else ySpeed = 0.f;

		if (input->isKeyDown(sf::Keyboard::Right) && !input->isKeyDown(sf::Keyboard::Left))
		{
			xSpeed = moveSpeed;
		}
		else if (input->isKeyDown(sf::Keyboard::Left) && !input->isKeyDown(sf::Keyboard::Right))
		{
			xSpeed = -moveSpeed;
		}
		else xSpeed = 0.f;

		if ((input->isKeyDown(sf::Keyboard::Down) || input->isKeyDown(sf::Keyboard::Up)) && (input->isKeyDown(sf::Keyboard::Right) || input->isKeyDown(sf::Keyboard::Left)))
		{
			speedMultiplier = 0.75f;
		}
		else speedMultiplier = 1.f;
	}

	// speed controls
	if (input->isKeyDown(sf::Keyboard::Equal))
	{
		input->setKeyUp(sf::Keyboard::Equal);
		moveSpeed += speedIncrement;

		if (xSpeed < 0)
		{
			xSpeed = -moveSpeed;
		}
		else xSpeed = moveSpeed;
		if (ySpeed < 0)
		{
			ySpeed = -moveSpeed;
		}
		else ySpeed = moveSpeed;
	}

	if (input->isKeyDown(sf::Keyboard::Hyphen))
	{
		input->setKeyUp(sf::Keyboard::Hyphen);
		if (moveSpeed > speedIncrement)
		{
			moveSpeed -= speedIncrement;
		}

		if (xSpeed < 0)
		{
			xSpeed = -moveSpeed;
		}
		else xSpeed = moveSpeed;
		if (ySpeed < 0)
		{
			ySpeed = -moveSpeed;
		}
		else ySpeed = moveSpeed;
	}

}

// Update game objects
void Level::update(float dt)
{
	// Update circle
	if (circle.getPosition().x > window->getSize().x - 30)
	{
		circle.setPosition(window->getSize().x - 30, circle.getPosition().y);
		if (autoMove)
		{
			xSpeed = -moveSpeed;
		}
	}
	else if (circle.getPosition().x < 0.f)
	{
		circle.setPosition(0, circle.getPosition().y);
		if (autoMove)
		{
			xSpeed = moveSpeed;
		}
	}

	if (circle.getPosition().y > window->getSize().y - 30)
	{
		circle.setPosition(circle.getPosition().x, window->getSize().y - 30);
		if (autoMove)
		{
			ySpeed = -moveSpeed;
		}
	}
	else if (circle.getPosition().y < 0.f)
	{
		circle.setPosition(circle.getPosition().x, 0);
		if (autoMove)
		{
			ySpeed = moveSpeed;
		}
	}

	circle.move(speedMultiplier * xSpeed * dt, speedMultiplier * ySpeed * dt);

	// Update circle position indicator
	circlePos.setString("Position: " + std::to_string(int(circle.getPosition().x)) + ", " + std::to_string(int(circle.getPosition().y)));

	// Update circle speed indicator
	circleSpeed.setString("Speed: " + std::to_string(int(moveSpeed)));
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circle);
	window->draw(circlePos);
	window->draw(circleSpeed);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(0, 0, 0));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}