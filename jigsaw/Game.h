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

const int COLS = 3;
const int ROWS = 4;
const int NO_OF_PIECES = ROWS * COLS;
const int NO_OF_VERTECIES = NO_OF_PIECES * 4;

const sf::Vector2f TOP_LEFT{ 200.0f,200.0f };
const float WIDTH = 400.0f;
const float HEIGHT = 600.0f;
const float PIECE_WIDTH = WIDTH / COLS;
const float PIECE_HEIGHT = HEIGHT / ROWS;

const sf::Color GRAY{ 176,176,176,255 };
const sf::Color GREEN{ 56,220,76,255 };
const sf::Color DARKGREEN{ 26,200,76,225 };


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
	void processMousePress(sf::Event t_event);
	void processMouseMove(sf::Event t_event);
	void processMouseRelease(sf::Event t_event);
	void processMouseWheel(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void updateVectors();
	void updateCentres();
	void translate();
	void rotate();
	void render();
	void reset();
	void randomise();
	void nextPicture();
	
	void setupFontAndText();
	void setupSprite();
	void rotate(int t_angle);

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_pictureTexture; // texture used for sfml logo
	
	sf::VertexArray m_lines{ sf::Lines };
	sf::VertexArray m_ouitline{ sf::Lines };
	sf::VertexArray m_pieces{ sf::Quads };
	MyVector3 m_startingPoints[NO_OF_VERTECIES];
	MyVector3 m_currentPoints[NO_OF_VERTECIES];
	MyVector3 m_translations[NO_OF_PIECES] = {{ 0.0f,0.0f,0.0f }};
	float m_rotations[NO_OF_PIECES] = {0.0f};
	MyVector3 m_centres[NO_OF_PIECES];
	bool m_exitGame; // control exiting game
	int m_currentPiece = -1;
	bool m_selected{ false };
	MyVector3 m_mouseStart;
	std::string m_fileNames[5] = { "bloodrage.jpg", "GalaxyTrucker.jpg", "patchwork.jpg","wingspan.jpg","takenoko.jpg"};
	int m_currentFile = 0;


};

#endif // !GAME_HPP

