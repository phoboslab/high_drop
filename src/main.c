#include "main.h"

global_t g;


// Music (c) by Andy Lösch no-fate.net

pl_synth_song_t song = {
	.row_len = 8481,
	.num_tracks = 4,
	.tracks = (pl_synth_track_t[]){
		{
			.synth = {7,0,0,0,121,1,7,0,0,0,91,3,0,100,1212,5513,100,0,6,19,3,121,6,21,0,1,1,29},
			.sequence_len = 12,
			.sequence = (uint8_t[]){1,2,1,2,1,2,0,0,1,2,1,2},
			.patterns = (pl_synth_pattern_t[]){
				{.notes = {138,145,138,150,138,145,138,150,138,145,138,150,138,145,138,150,136,145,138,148,136,145,138,148,136,145,138,148,136,145,138,148}},
				{.notes = {135,145,138,147,135,145,138,147,135,145,138,147,135,145,138,147,135,143,138,146,135,143,138,146,135,143,138,146,135,143,138,146}}
			}
		},
		{
			.synth = {7,0,0,0,192,1,6,0,9,0,192,1,25,137,1111,16157,124,1,982,89,6,25,6,77,0,1,3,69},
			.sequence_len = 12,
			.sequence = (uint8_t[]){0,0,1,2,1,2,3,3,3,3,3,3},
			.patterns = (pl_synth_pattern_t[]){
				{.notes = {138,138,0,138,140,0,141,0,0,0,0,0,0,0,0,0,136,136,0,136,140,0,141}},
				{.notes = {135,135,0,135,140,0,141,0,0,0,0,0,0,0,0,0,135,135,0,135,140,0,141,0,140,140}},
				{.notes = {145,0,0,0,145,143,145,150,0,148,0,146,0,143,0,0,0,145,0,0,0,145,143,145,139,0,139,0,0,142,142}}
			}
		},
		{
			.synth = {7,0,0,1,255,0,7,0,0,1,255,0,0,100,0,3636,174,2,500,254,0,27},
			.sequence_len = 12,
			.sequence = (uint8_t[]){1,1,1,1,0,0,1,1,1,1,1,1},
			.patterns = (pl_synth_pattern_t[]){
				{.notes = {135,135,0,135,139,0,135,135,135,0,135,139,0,135,135,135,0,135,139,0,135,135,135,0,135,139,0,135,135,135,0,135}}
			}
		},
		{
			.synth = {8,0,0,1,200,0,7,0,0,0,211,3,210,50,200,6800,153,4,11025,254,6,32,5,61,0,1,4,60},
			.sequence_len = 12,
			.sequence = (uint8_t[]){1,1,1,1,0,0,1,1,1,1,1,1},
			.patterns = (pl_synth_pattern_t[]){
				{.notes = {0,0,0,0,140,0,0,0,0,0,0,0,140,0,0,0,0,0,0,0,140,0,0,0,0,0,0,0,140}}
			}
		}
	}
};

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
	
	engine_set_scene(&scene_game);

	sound_t ss = sound(sound_source_synth_song(&song));
	sound_set_volume(ss, 0.8);
	sound_set_loop(ss, true);
	sound_unpause(ss);
}

void main_cleanup(void) {

}
