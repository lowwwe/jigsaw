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
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMousePress(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseRelease(newEvent);
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

void Game::processMousePress(sf::Event t_event)
{
	MyVector3 mouse{ static_cast<float>(t_event.mouseButton.x), static_cast<float>(t_event.mouseButton.y), 0.0f };
	float dotProduct = 0.0f;
	MyVector3 A, B;
	bool inside = true;
	if (!m_selected)
	{
		for (int i = 0; i < NO_OF_PIECES; i++)
		{
			
			inside = true;
			for (int j = 0; j < 4; j++)
			{
				A = m_currentPoint[i * 4 + j] - m_currentPoint[i * 4 + (j + 1)%4];
				B = mouse -m_currentPoint[i * 4 + (j + 1) % 4] ;
				dotProduct = A.dot(B);
				if (dotProduct < 0.0f)
				{
					inside = false;
				}
				A = m_currentPoint[i * 4 + (j + 1) % 4] - m_currentPoint[i * 4 + j ];
				B = mouse - m_currentPoint[i * 4 + j ];
				dotProduct = A.dot(B);
				if (dotProduct < 0.0f)
				{
					inside = false;
				}

			}
			if (inside)
			{
				m_currentPiece = i;
				m_selected = true;
				for (int j = 0; j < 4; j++)
				{
					m_pieces[i * 4 + j].color = GRAY;
				}
				for (int j = 0; j < 8; j++)
				{
					m_lines[i * 8 + j].color = sf::Color::Yellow;
				}

			}			
			
		}
	}
}

void Game::processMouseMove(sf::Event t_event)
{
}

void Game::processMouseRelease(sf::Event t_event)
{
	if (m_selected)
	{
		for (int j = 0; j < 8; j++)
		{
			m_lines[m_currentPiece * 8 + j].color = sf::Color::Black;
		}
		for (int j = 0; j < 4; j++)
		{
			m_pieces[m_currentPiece * 4 + j].color = sf::Color::White;
		}
		m_currentPiece = -1;
		m_selected = false;
	}
}

void Game::processMouseWheel(sf::Event t_event)
{
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	updateVectors();
	if (m_exitGame)
	{
		m_window.close();
	}
}

void Game::updateVectors()
{
	for (int i = 0; i < NO_OF_VERTECIES; i++)
	{
		m_currentPoint[i] = m_startingPoints[i];
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(GREEN);
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
			m_startingPoints[currentVertex++] = vertexPiece.position;

			vertexPiece.position = topLeft + sf::Vector2f{PIECE_WIDTH,0.0f};
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j+1) / ROWS * pixelsWide, static_cast<float>(i) / COLS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			m_startingPoints[currentVertex++] = vertexPiece.position;
			
			vertexPiece.position = topLeft + sf::Vector2f{PIECE_WIDTH, PIECE_HEIGHT };
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j + 1) / ROWS * pixelsWide, static_cast<float>(i+1) / COLS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			m_startingPoints[currentVertex++] = vertexPiece.position;
			
			vertexPiece.position = topLeft + sf::Vector2f{ 0.0f, PIECE_HEIGHT };
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j)  / ROWS * pixelsWide, static_cast<float>(i + 1) / COLS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			m_lines.append(lineStart);
			m_startingPoints[currentVertex++] = vertexPiece.position;

		}
	}

	
}
