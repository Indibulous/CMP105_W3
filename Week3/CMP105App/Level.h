#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Moving circle vars
	sf::CircleShape circle;
	float speedIncrement;
	float moveSpeed;
	float xSpeed;
	float ySpeed;
	float speedMultiplier;
	bool autoMove;

	sf::CircleShape circleTrail0;
	sf::CircleShape circleTrail1;
	sf::CircleShape circleTrail2;


	// Fonts
	sf::Font font;

	// Circle position display
	sf::Text circlePos;

	// Circle speed display
	sf::Text circleSpeed;
};