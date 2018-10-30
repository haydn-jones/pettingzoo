#include <SFML/Graphics.hpp>
#include <defs.hpp>
#include <rendering.hpp>
#include <gamelogic.hpp>

int main(int argc, char **argv)
{
	int draw_overlay = 0;
	int input[BUTTON_COUNT] = {0};
	int ret = 0;
    sf::RenderWindow window(sf::VideoMode(800, 600), "PettingZoo");
	sf::Time time;
	sf::Clock clock;
	sf::Color bg_color(135, 206, 235);

	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);

	game_setup();
	render_load_assets();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) {
					input[BUTTON_JUMP] = 1;
				} else if (event.key.code == sf::Keyboard::Left) {
					input[BUTTON_LEFT] = 1;
				} else if (event.key.code == sf::Keyboard::Right) {
					input[BUTTON_RIGHT] = 1;
				} else if (event.key.code == sf::Keyboard::Escape) {
					return 0;
				} else if (event.key.code == sf::Keyboard::O) {
					draw_overlay ^= 1;
				} else if (event.key.code == sf::Keyboard::R) {
					game_setup();
					render_regen_map();
				}
			} else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Left) {
					input[BUTTON_LEFT] = 0;
				} else if (event.key.code == sf::Keyboard::Right) {
					input[BUTTON_RIGHT] = 0;
				} else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Space) {
					input[BUTTON_JUMP] = 0;
				}
			} else if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::Resized) {
				render_scale_window(window, event);
			}
		}

		//Update game state
		ret = game_update(input);
		if (ret == PLAYER_DEAD) {
			game_setup();
			render_regen_map();
		} else if (ret == REDRAW) {
			render_regen_map();
		} /* else if (ret > 0) {
			printf("PLAYER WON! FITNESS=%d\n", ret);
			game_setup();
			render_regen_map();
		} */

		// Update camera
		render_handle_camera(window);

		//Clear the screen
		window.clear(bg_color);

		//Draw background, tiles, and entities
		render_other(window);
		render_tiles(window);
		render_entities(window);

		//Draw debug overlay + fps
		time = clock.getElapsedTime();
		clock.restart();
		if (draw_overlay) {
			render_debug_overlay(window, time);
		}

		// Score and time
		render_hud(window, input);

		window.display();
	}

	return 0;
}
