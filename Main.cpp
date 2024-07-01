#define NOMINMAX

#include "Windows.h"
#include <SFML/Graphics.hpp>

#include "Render.h"
#include "perspective.h"

#include "SpriteImage.h"

#include <vector>


int main() {

	const int SCREEN_WIDTH = 200;
	const int SCREEN_HEIGHT = 200;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "3D Renderer II");

	SpriteImage screen(SCREEN_WIDTH, SCREEN_HEIGHT);
	Perspective player(SpaceVector(0, -2, 0), Rotation(0.0, 0.0, 0.0));
	
	Render renderer(&screen);

	const Color BRICKS[] = {
	RED  , RED  , RED  , GREEN, RED  , RED  , RED  , GREEN,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
	GREEN, RED  , RED  , RED  , GREEN, RED  , RED  , RED  ,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
	RED  , GREEN, RED  , RED  , RED  , GREEN, RED  , RED  ,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN,
	RED  , RED  , GREEN, RED  , RED  , RED  , GREEN, RED  ,
	GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN
	};

	Image bricks(8, 8, BRICKS);

	Sculpture world = Sculpture::Cube(2, &bricks, SpaceVector(0, 0, 5), FORWARD);

	while (window.isOpen()) {

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
					player.turn(-0.01, 0, 0);
					break;
				case sf::Keyboard::L:
					player.turn(0.01, 0, 0);
					break;
				case sf::Keyboard::U:
					player.turn(0, 0, -0.01);
					break;
				case sf::Keyboard::O:
					player.turn(0, 0, 0.01);
					break;
				}
			}
		}
		screen.fill(Color(100, 200, 255));
		renderer.RenderWorld(player, world);
		
		window.draw(screen.getSprite());
		window.display();

	}

}