#define NOMINMAX

#include "Windows.h"
#include <SFML/Graphics.hpp>

#include "Render.h"
#include "perspective.h"

#include "SpriteImage.h"

#include <vector>

// Color arrays used to create images
const Color BRICKS[] = {
	RED  , RED  , RED  , WHITE, RED  , RED  , RED  , WHITE,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
	WHITE, RED  , RED  , RED  , WHITE, RED  , RED  , RED  ,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
	RED  , WHITE, RED  , RED  , RED  , WHITE, RED  , RED  ,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
	RED  , RED  , WHITE, RED  , RED  , RED  , WHITE, RED  ,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE
};

const Color MOSS_BRICKS[] = {
	RED  , RED  , RED  , GREEN, RED  , RED  , RED  , GREEN,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
	GREEN, RED  , RED  , RED  , GREEN, RED  , RED  , RED  ,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
	RED  , GREEN, RED  , RED  , RED  , GREEN, RED  , RED  ,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
	RED  , RED  , GREEN, RED  , RED  , RED  , GREEN, RED  ,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
};

const Color GEL_BRICKS[] = {
	RED , RED , RED , BLUE, RED , RED , RED , BLUE,
	BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
	BLUE, RED , RED , RED , BLUE, RED , RED , RED ,
	BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
	RED , BLUE, RED , RED , RED , BLUE, RED , RED ,
	BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE,
	RED , RED , BLUE, RED , RED , RED , BLUE, RED  ,
	BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE, BLUE
};

const Color BLUE_BRICKS[] = {
	BLUE , BLUE , BLUE , WHITE, BLUE , BLUE , BLUE , WHITE,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
	WHITE, BLUE , BLUE , BLUE , WHITE, BLUE , BLUE , BLUE ,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
	BLUE , WHITE, BLUE , BLUE , BLUE , WHITE, BLUE , BLUE ,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
	BLUE , BLUE , WHITE, BLUE , BLUE , BLUE , WHITE, BLUE ,
	WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE
};

int main() {
	// Define how large the window is
	const int SCREEN_WIDTH = 200;
	const int SCREEN_HEIGHT = 200;

	// Create Image objects for the sculptures
	Image bricks(8, 8, BRICKS);
	Image blueBricks(8, 8, BLUE_BRICKS);
	Image mossBricks(8, 8, MOSS_BRICKS);
	Image gelBricks(8, 8, GEL_BRICKS);

	// Create the SFML window
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "3D Renderer II");

	// Create a SpriteImage which works as the screen
	// It can be used by the renderer and can also
	// Create a Sprite object for SFML
	SpriteImage screen(SCREEN_WIDTH, SCREEN_HEIGHT);

	// Define the users perspective
	Perspective player(SpaceVector(0, 0, 0), Rotation(0.0, 0.0, 0.0));
	
	// Create the renderer connected to the SpriteImage
	Render renderer(&screen);

	// Build the world
	Sculpture world;

	world.addChild(world.Cube(2, &bricks, SpaceVector(0, 0, 5), FORWARD));
	world.addChild(world.Cube(2, &gelBricks, SpaceVector(0, 0, -5), Rotation(0, 0, 0)));
	world.addChild(world.Cube(2, &mossBricks, SpaceVector(5, 0, 0), Rotation(0, 0, 0)));
	world.addChild(world.Cube(2, &blueBricks, SpaceVector(-5, 0, 0), Rotation(0, 0, 0)));

	// The main loop
	while (window.isOpen()) {
		// Handle events such as exits and key presses
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::W:
					player.moveRel(KVECTOR * 0.01);
					break;
				case sf::Keyboard::S:
					player.moveRel(KVECTOR * -0.01);
					break;
				case sf::Keyboard::A:
					player.moveRel(IVECTOR * 0.01);
					break;
				case sf::Keyboard::D:
					player.moveRel(IVECTOR * -0.01);
					break;
				case sf::Keyboard::Space:
					player.moveAbs(JVECTOR * 0.01);
					break;
				case sf::Keyboard::X:
					player.moveAbs(JVECTOR * -0.01);
					break;
				case sf::Keyboard::I:
					player.turn(0, 0.01, 0);
					break;
				case sf::Keyboard::K:
					player.turn(0, -0.01, 0);
					break;
				case sf::Keyboard::J:
					player.turn(0.01, 0, 0);
					break;
				case sf::Keyboard::L:
					player.turn(-0.01, 0, 0);
					break;
				case sf::Keyboard::U:
					player.turn(0, 0, 0.01);
					break;
				case sf::Keyboard::O:
					player.turn(0, 0, -0.01);
					break;
				}
			}
		}
		// Fill the screen with background color
		screen.fill(Color(100, 200, 255));

		// Have the renderer draw the world onto the screen it screen
		renderer.RenderWorld(player, world);
		
		// Draw the screen representation used by the renderer
		// onto the window and display it
		window.draw(screen.getSprite());
		window.display();

	}

}