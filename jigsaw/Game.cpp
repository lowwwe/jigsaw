/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 600U, 800U, 32U }, "JigSaw" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Green);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_pieces,&m_pictureTexture);
	m_window.draw(m_lines);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("JigSaw");
	
	m_welcomeMessage.setPosition(20.0f, 20.0f);
	m_welcomeMessage.setCharacterSize(30U);	
	m_welcomeMessage.setFillColor(sf::Color::Black);
	

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	int currentVertex = 0;
	sf::Vector2f  topLeft{};
	float textureX;
	float textureY;
	sf::Vertex vertexPiece{ sf::Vector2f{0.0f,0.0f}, sf::Color::White };
	sf::Vertex vertexLine{ sf::Vector2f{0.0f,0.0f}, sf::Color::Black };
	sf::Vertex lineStart;
	float pixelsWide = 0.0f;;
	float pixelsTall = 0.0f ;

	
	m_pieces.clear();
	if (!m_pictureTexture.loadFromFile("ASSETS\\IMAGES\\bloodrage.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}

	 pixelsWide = static_cast<float>(m_pictureTexture.getSize().x);
	 pixelsTall = static_cast<float>(m_pictureTexture.getSize().y);


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			topLeft = sf::Vector2f{ TOP_LEFT.x + j * PIECE_WIDTH, TOP_LEFT.y + i * PIECE_HEIGHT };
			std::cout << topLeft.x << "," << topLeft.y << std::endl;
			vertexPiece.position = topLeft;
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j) / ROWS * pixelsWide, static_cast<float>(i) / COLS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			lineStart = vertexLine;
			vertexPiece.position = topLeft + sf::Vector2f{PIECE_WIDTH,0.0f};
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j+1) / ROWS * pixelsWide, static_cast<float>(i) / COLS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			vertexPiece.position = topLeft + sf::Vector2f{PIECE_WIDTH, PIECE_HEIGHT };
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j + 1) / ROWS * pixelsWide, static_cast<float>(i+1) / COLS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			vertexPiece.position = topLeft + sf::Vector2f{ 0.0f, PIECE_HEIGHT };
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j)  / ROWS * pixelsWide, static_cast<float>(i + 1) / COLS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			m_lines.append(lineStart);

		}
	}

	
}
