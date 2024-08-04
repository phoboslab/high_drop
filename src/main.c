#include "main.h"

global_t g;

void main_init(void) {
	// Gamepad
	input_bind(INPUT_GAMEPAD_DPAD_LEFT, A_LEFT);
	input_bind(INPUT_GAMEPAD_DPAD_RIGHT, A_RIGHT);
	input_bind(INPUT_GAMEPAD_L_STICK_LEFT, A_LEFT);
	input_bind(INPUT_GAMEPAD_L_STICK_RIGHT, A_RIGHT);
	input_bind(INPUT_GAMEPAD_X, A_START);

	// Keyboard
	input_bind(INPUT_KEY_LEFT, A_LEFT);
	input_bind(INPUT_KEY_RIGHT, A_RIGHT);
	input_bind(INPUT_KEY_RETURN, A_START);

	g.font = font("assets/font_04b03.qoi", "assets/font_04b03.json");
	g.font->color = rgba(75, 84, 0, 255);
	
	sound_set_global_volume(0.75);
	engine_set_scene(&scene_game);
}

void main_cleanup(void) {

}
