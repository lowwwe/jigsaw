/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Matrix.h"
#include "MyVector3.h"

const int COLS = 4;
const int ROWS = 4;
const int NO_OF_PIECES = ROWS * COLS;
const int NO_OF_VERTECIES = NO_OF_PIECES * 4;

const sf::Vector2f TOP_LEFT{ 100.0f,100.0f };
const float WIDTH = 400.0f;
const float HEIGHT = 600.0f;
const float PIECE_WIDTH = WIDTH / COLS;
const float PIECE_HEIGHT = HEIGHT / ROWS;


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_pictureTexture; // texture used for sfml logo
	
	sf::VertexArray m_lines{ sf::Lines };
	sf::VertexArray m_pieces{ sf::Quads };
	MyVector3 m_startingPoints[NO_OF_VERTECIES];
	MyVector3 m_currentPoint[NO_OF_VERTECIES];
	bool m_exitGame; // control exiting game


};

#endif // !GAME_HPP

