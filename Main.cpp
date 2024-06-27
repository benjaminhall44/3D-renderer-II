#define NOMINMAX

#include "Windows.h"
#include <SFML/Graphics.hpp>

#include "Graphics.h"
#include "perspective.h"

#include <vector>


int main() {

	const int SCREEN_WIDTH = 200;
	const int SCREEN_HEIGHT = 200;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "3D Renderer II");

	Image screen(SCREEN_WIDTH, SCREEN_HEIGHT);
	Perspective player(SpaceVector(0, -2, 0), 0.0, 0.0, 0.0);
	
	Render renderer(&screen);

	Image bricks(8, 8);
	bricks.setPixel(0, 0, pixel(255, 0, 0));
	bricks.setPixel(1, 0, pixel(255, 0, 0));
	bricks.setPixel(2, 0, pixel(255, 0, 0));
	bricks.setPixel(3, 0, pixel(0, 255, 0));
	bricks.setPixel(4, 0, pixel(255, 0, 0));
	bricks.setPixel(5, 0, pixel(255, 0, 0));
	bricks.setPixel(6, 0, pixel(255, 0, 0));
	bricks.setPixel(7, 0, pixel(0, 255, 0));

	bricks.setPixel(0, 1, pixel(0, 255, 0));
	bricks.setPixel(1, 1, pixel(0, 255, 0));
	bricks.setPixel(2, 1, pixel(0, 255, 0));
	bricks.setPixel(3, 1, pixel(0, 255, 0));
	bricks.setPixel(4, 1, pixel(0, 255, 0));
	bricks.setPixel(5, 1, pixel(0, 255, 0));
	bricks.setPixel(6, 1, pixel(0, 255, 0));
	bricks.setPixel(7, 1, pixel(0, 255, 0));

	bricks.setPixel(0, 2, pixel(0, 255, 0));
	bricks.setPixel(1, 2, pixel(255, 0, 0));
	bricks.setPixel(2, 2, pixel(255, 0, 0));
	bricks.setPixel(3, 2, pixel(255, 0, 0));
	bricks.setPixel(4, 2, pixel(0, 255, 0));
	bricks.setPixel(5, 2, pixel(255, 0, 0));
	bricks.setPixel(6, 2, pixel(255, 0, 0));
	bricks.setPixel(7, 2, pixel(255, 0, 0));

	bricks.setPixel(0, 3, pixel(0, 255, 0));
	bricks.setPixel(1, 3, pixel(0, 255, 0));
	bricks.setPixel(2, 3, pixel(0, 255, 0));
	bricks.setPixel(3, 3, pixel(0, 255, 0));
	bricks.setPixel(4, 3, pixel(0, 255, 0));
	bricks.setPixel(5, 3, pixel(0, 255, 0));
	bricks.setPixel(6, 3, pixel(0, 255, 0));
	bricks.setPixel(7, 3, pixel(0, 255, 0));

	bricks.setPixel(0, 4, pixel(255, 0, 0));
	bricks.setPixel(1, 4, pixel(0, 255, 0));
	bricks.setPixel(2, 4, pixel(255, 0, 0));
	bricks.setPixel(3, 4, pixel(255, 0, 0));
	bricks.setPixel(4, 4, pixel(255, 0, 0));
	bricks.setPixel(5, 4, pixel(0, 255, 0));
	bricks.setPixel(6, 4, pixel(255, 0, 0));
	bricks.setPixel(7, 4, pixel(255, 0, 0));

	bricks.setPixel(0, 5, pixel(0, 255, 0));
	bricks.setPixel(1, 5, pixel(0, 255, 0));
	bricks.setPixel(2, 5, pixel(0, 255, 0));
	bricks.setPixel(3, 5, pixel(0, 255, 0));
	bricks.setPixel(4, 5, pixel(0, 255, 0));
	bricks.setPixel(5, 5, pixel(0, 255, 0));
	bricks.setPixel(6, 5, pixel(0, 255, 0));
	bricks.setPixel(7, 5, pixel(0, 255, 0));

	bricks.setPixel(0, 6, pixel(255, 0, 0));
	bricks.setPixel(1, 6, pixel(255, 0, 0));
	bricks.setPixel(2, 6, pixel(0, 255, 0));
	bricks.setPixel(3, 6, pixel(255, 0, 0));
	bricks.setPixel(4, 6, pixel(255, 0, 0));
	bricks.setPixel(5, 6, pixel(255, 0, 0));
	bricks.setPixel(6, 6, pixel(0, 255, 0));
	bricks.setPixel(7, 6, pixel(255, 0, 0));

	bricks.setPixel(0, 7, pixel(0, 255, 0));
	bricks.setPixel(1, 7, pixel(0, 255, 0));
	bricks.setPixel(2, 7, pixel(0, 255, 0));
	bricks.setPixel(3, 7, pixel(0, 255, 0));
	bricks.setPixel(4, 7, pixel(0, 255, 0));
	bricks.setPixel(5, 7, pixel(0, 255, 0));
	bricks.setPixel(6, 7, pixel(0, 255, 0));
	bricks.setPixel(7, 7, pixel(0, 255, 0));

	Sculpture world = Sculpture::Cube(2, &bricks, SpaceVector(0, 0, 5), MAINAXIS);

	sf::Texture texture;

	texture.create(SCREEN_WIDTH, SCREEN_HEIGHT);

	sf::Uint8* pixels = new sf::Uint8[SCREEN_WIDTH * SCREEN_HEIGHT * 4];

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
					player.turnAbs(0, 0.01, 0);
					break;
				case sf::Keyboard::K:
					player.turnAbs(0, -0.01, 0);
					break;
				case sf::Keyboard::J:
					player.turnAbs(-0.01, 0, 0);
					break;
				case sf::Keyboard::L:
					player.turnAbs(0.01, 0, 0);
					break;
				case sf::Keyboard::U:
					player.turnAbs(0, 0, -0.01);
					break;
				case sf::Keyboard::O:
					player.turnAbs(0, 0, 0.01);
					break;
				}
			}
		}
		screen.fill(pixel(100, 200, 255));
		renderer.RenderWorld(player, world);
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++){
				pixels[y * SCREEN_WIDTH * 4 + x * 4 + 0] = screen.getPixel(x, y).red;
				pixels[y * SCREEN_WIDTH * 4 + x * 4 + 1] = screen.getPixel(x, y).green;
				pixels[y * SCREEN_WIDTH * 4 + x * 4 + 2] = screen.getPixel(x, y).blue;
				pixels[y * SCREEN_WIDTH * 4 + x * 4 + 3] = 255;
			}
		}
		texture.update(pixels);

		sf::Sprite sprite(texture);

		window.draw(sprite);
		window.display();

	}

}