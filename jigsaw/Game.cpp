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
	m_window{ sf::VideoMode{ 800U, 1000U, 32U }, "JigSaw twelve piece array" },
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
		switch (newEvent.type)
		{
		case sf::Event::Closed:
			m_exitGame = true;
			break;
		case sf::Event::KeyPressed :
			processKeys(newEvent);
			break;
		case sf::Event::MouseButtonPressed :
			processMousePress(newEvent);
			break;
		case sf::Event::MouseButtonReleased:
			processMouseRelease(newEvent);
			break;
		case sf::Event::MouseMoved:
			processMouseMove(newEvent);
			break;
		case sf::Event::MouseWheelMoved :
			processMouseWheel(newEvent);
			break;
		}		
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	switch (t_event.key.code)
	{
		case sf::Keyboard::Escape:
			m_exitGame = true;
			break;
		case sf::Keyboard::R:
			reset();
			break;
		case sf::Keyboard::S:
			randomise();
			break;
		case sf::Keyboard::N:
			nextPicture();
			break;
		case sf::Keyboard::Add:
			rotate(5);
			break;
		case sf::Keyboard:: Equal:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				rotate(5);
			}
			break;

		case sf::Keyboard::Subtract:
			rotate(-5);
			break;
		case sf::Keyboard::Dash  :
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
			{
				rotate(-5);
			}
			break;


	}

}

void Game::processMousePress(sf::Event t_event)
{
	MyVector3 mouse{ static_cast<float>(t_event.mouseButton.x), static_cast<float>(t_event.mouseButton.y), 0.0f };
	m_mouseStart = mouse;
	float dotProduct = 0.0f;
	float angle;
	MyVector3 A, B;
	bool inside = true;
	if (!m_selected)
	{
		for (int i = 0; i < NO_OF_PIECES && !m_selected; i++)
		{
			
			inside = true;
			for (int j = 0; j < 4; j++)
			{
				A = m_currentPoints[i * 4 + j] - m_currentPoints[i * 4 + (j + 1)%4];
				B = mouse -m_currentPoints[i * 4 + (j + 1) % 4] ;
				dotProduct = A.dot(B);
				if (dotProduct < 0.0f)
				{
					inside = false;
				}
				A = m_currentPoints[i * 4 + (j + 1) % 4] - m_currentPoints[i * 4 + j ];
				B = mouse - m_currentPoints[i * 4 + j ];
				dotProduct = A.dot(B);
				if (dotProduct < 0.0f)
				{
					inside = false;
				}

			}
		
				angle = 0.0f;
				for (int j = 0; j < 4; j++)
				{
					A = mouse - m_currentPoints[i * 4 + j] ;
					B = mouse - m_currentPoints[i * 4 + (j + 1) % 4];
					angle += A.angleBetween(B);
				}
				if (angle > 359.0f && angle < 361.0f)
				{
					inside = true;
				}
				else
				{
					inside = false;
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
	MyVector3 currentMouse= { static_cast<float>(t_event.mouseMove.x), static_cast<float>(t_event.mouseMove.y), 0.0f };
	if (m_selected)
	{
		m_translations[m_currentPiece] +=  currentMouse - m_mouseStart;
		m_mouseStart = currentMouse;
	}
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
	if (m_selected)
	{
		m_rotations[m_currentPiece] += t_event.mouseWheel.delta *5;		
	}
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
	int lastOne;
	for (int i = 0; i < NO_OF_VERTECIES; i++)
	{
		m_currentPoints[i] = m_startingPoints[i];
		
	}
	rotate();
	translate();

	for (int i = 0; i < NO_OF_VERTECIES; i++)
	{
		m_pieces[i].position = m_currentPoints[i];
		m_lines[i * 2].position = m_currentPoints[i];
		lastOne = i + 1 -((i+1)/4 - i/4 )*4;
		m_lines[i * 2 + 1].position = m_currentPoints[lastOne];
	}
}

void Game::updateCentres()
{
	MyVector3 centre{};
	for (int i = 0; i < NO_OF_PIECES; i++)
	{
		centre = { 0.0f,0.0f,0.0f };
		for (int j = 0; j < 4; j++)
		{
			centre += m_startingPoints[i * 4 + j];
		}
		m_centres[i] = centre / 4.0f;
	}
}

void Game::translate()
{
	MyMatrix translate;
	for (int i = 0; i < NO_OF_PIECES; i++)
	{
		if (m_translations[i].lengthSquared() < 10.9f)
		{
			m_translations[i] = { 0.0f,0.0f,0.0f };
		}
		translate = MyMatrix::translation(m_translations[i]);
		for (int j = 0; j < 4; j++)
		{
			m_currentPoints[i * 4 + j] = translate * m_currentPoints[i * 4 + j];
		}
	}
}

void Game::rotate()
{
	MyMatrix rotate;
	MyMatrix translate;
	MyMatrix translateback;
	MyMatrix compound;
	updateCentres();
	for (int i = 0; i < NO_OF_PIECES; i++)
	{
		rotate = MyMatrix::rotationClockwiseZ(m_rotations[i]);
		translate = MyMatrix::translation(-m_centres[i]);
		translateback = translate.getInverse();
		compound = translate * rotate * translateback;
		for (int j = 0; j < 4; j++)
		{
			m_currentPoints[i * 4 + j] = translate * m_currentPoints[i * 4 + j];
			m_currentPoints[i * 4 + j] = rotate * m_currentPoints[i * 4 + j];
			m_currentPoints[i * 4 + j] = translateback * m_currentPoints[i * 4 + j];
		}
		
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(GREEN);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_ouitline);
	m_window.draw(m_pieces,&m_pictureTexture);
	m_window.draw(m_lines);
	m_window.display();
}

void Game::reset()
{
	for (int i = 0; i < NO_OF_PIECES; i++)
	{
		m_rotations[i] = 0.0f;
		m_translations[i] = { 0.0f,0.0f,0.0f };
	}
}

void Game::randomise()
{
	for (int i = 0; i < NO_OF_PIECES; i++)
	{
		m_rotations[i] = static_cast<float>( (std::rand() % 36)*5);
		m_translations[i] = { std::rand() % 800 - m_centres[i].x,
							std::rand() % 1000 - m_centres[i].y, 1.0f };
			
	}
}

void Game::nextPicture()
{
	m_currentFile = (m_currentFile + 1) % 5;
	if (!m_pictureTexture.loadFromFile("ASSETS\\IMAGES\\" + m_fileNames[m_currentFile]))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Picture " << m_currentFile << std::endl;
	}
	float pixelsWide = static_cast<float>(m_pictureTexture.getSize().x);
	float pixelsTall = static_cast<float>(m_pictureTexture.getSize().y);
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			m_pieces[i*4*COLS + j * 4].texCoords = sf::Vector2f{ static_cast<float>(j) / COLS * pixelsWide, static_cast<float>(i) / ROWS * pixelsTall };
			m_pieces[i * 4 * COLS + j * 4 +1].texCoords = sf::Vector2f{ static_cast<float>(j + 1) / COLS * pixelsWide, static_cast<float>(i) / ROWS * pixelsTall };
			m_pieces[i * 4 * COLS + j * 4 +2].texCoords = sf::Vector2f{ static_cast<float>(j + 1) / COLS * pixelsWide, static_cast<float>(i + 1) / ROWS * pixelsTall };
			m_pieces[i * 4 * COLS + j * 4 +3].texCoords = sf::Vector2f{ static_cast<float>(j) / COLS * pixelsWide, static_cast<float>(i + 1) / ROWS * pixelsTall };
		}
	}
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
	m_welcomeMessage.setString("Drag pieces to correct location \nUse mouse wheel to rotate or (+,-)\nS to start puzzle\nN for a new puzzle\nR to reset puzzle");
	
	m_welcomeMessage.setPosition(20.0f, 20.0f);
	m_welcomeMessage.setCharacterSize(20U);	
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
	sf::Vertex vertexOutline{ sf::Vector2f{0.0f,0.0f}, DARKGREEN };
	float pixelsWide = 0.0f;;
	float pixelsTall = 0.0f ;

	
	m_pieces.clear();
	if (!m_pictureTexture.loadFromFile("ASSETS\\IMAGES\\bloodrage.jpg"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading Picture" << std::endl;
	}

	 pixelsWide = static_cast<float>(m_pictureTexture.getSize().x);
	 pixelsTall = static_cast<float>(m_pictureTexture.getSize().y);


	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			topLeft = sf::Vector2f{ TOP_LEFT.x + j * PIECE_WIDTH, TOP_LEFT.y + i * PIECE_HEIGHT };			
			vertexPiece.position = topLeft;
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j) / COLS * pixelsWide, static_cast<float>(i) / ROWS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			vertexOutline.position = vertexPiece.position;
			m_ouitline.append(vertexOutline);
			m_lines.append(vertexLine);
			lineStart = vertexLine;
			m_startingPoints[currentVertex] = vertexPiece.position;
			m_startingPoints[currentVertex++].z = 1.0f;
			
			vertexPiece.position = topLeft + sf::Vector2f{PIECE_WIDTH,0.0f};
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j+1) / COLS * pixelsWide, static_cast<float>(i) / ROWS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			vertexOutline.position = vertexPiece.position;
			m_ouitline.append(vertexOutline);
			m_ouitline.append(vertexOutline);
			m_startingPoints[currentVertex] = vertexPiece.position;
			m_startingPoints[currentVertex++].z = 1.0f;

			
			vertexPiece.position = topLeft + sf::Vector2f{PIECE_WIDTH, PIECE_HEIGHT };
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j + 1) / COLS * pixelsWide, static_cast<float>(i+1) / ROWS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			vertexOutline.position = vertexPiece.position;
			m_ouitline.append(vertexOutline);
			m_ouitline.append(vertexOutline);
			m_startingPoints[currentVertex] = vertexPiece.position;
			m_startingPoints[currentVertex++].z = 1.0f;

			vertexPiece.position = topLeft + sf::Vector2f{ 0.0f, PIECE_HEIGHT };
			vertexPiece.texCoords = sf::Vector2f{ static_cast<float>(j)  / COLS * pixelsWide, static_cast<float>(i + 1) / ROWS * pixelsTall };
			m_pieces.append(vertexPiece);
			vertexLine.position = vertexPiece.position;
			m_lines.append(vertexLine);
			m_lines.append(vertexLine);
			vertexOutline.position = vertexPiece.position;
			m_ouitline.append(vertexOutline);
			m_ouitline.append(vertexOutline);
			m_lines.append(lineStart);
			vertexOutline.position = lineStart.position;
			m_ouitline.append(vertexOutline);
			m_startingPoints[currentVertex] = vertexPiece.position;
			m_startingPoints[currentVertex++].z = 1.0f;

		}
	}

	
}

void Game::rotate(int t_angle)
{
	if (m_selected)
	{
		m_rotations[m_currentPiece] += t_angle;
	}
}
