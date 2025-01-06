#include "../main.h"


map_t *map;
bool game_over;
entity_t *player;
sound_source_t *sound_game_over;

static pl_synth_sound_t sound_game_over_synth = {
	.synth = {8,0,0,1,160,1,6,0,0,1,160,3,0,226,0,13932,160,4,4523,199,3,47}, 
	.row_len = 5513, .note = 135
};

image_t *backdrop;

void generate_row(int row) {
	// Randomly generate a row of block for the map. This is a naive approach,
	// that sometimes leaves the player hanging with no block to jump to. It's
	// random after all.
	for (int col = 0; col < 8; col++) {
		map->data[row * map->size.x + col] = rand_float(0, 1) > 0.93 ? 1 : 0;
	}
}

void place_coin(int row) {
	// Randomly find a free spot for the coin, max 12 tries
	for (int i = 0; i < 12; i++) {
		int x = rand_int(0, 7);
		if(
			map->data[ row    * map->size.x + x] == 1 &&
			map->data[(row-1) * map->size.x + x] == 0
		) {
			vec2_t pos = vec2(
				x * map->tile_size + 1,
				(row-1) * map->tile_size + 2
			);
			entity_spawn(ENTITY_TYPE_COIN, pos);
			return;
		}
	}
}

static void init(void) {
	rand_seed((uint64_t)(engine.time_real * 10000000.0));

	engine.gravity = 240;
	g.score = 0;
	g.speed = 1;
	game_over = false;
	backdrop = image("assets/backdrop.qoi");
	sound_game_over = sound_source_synth_sound(&sound_game_over_synth);

	map = map_with_data(8, vec2i(8, 18), NULL);
	map->tileset = image("assets/tiles.qoi");
	map->data[4 * map->size.x + 3] = 1;
	map->data[4 * map->size.x + 4] = 1;
	for (int i = 8; i < map->size.y; i++) {
		generate_row(i);
	}

	// The map is used as CollisionMap AND BackgroundMap
	engine_set_collision_map(map);
	engine_add_background_map(map);

	player = entity_spawn(ENTITY_TYPE_PLAYER, vec2(render_size().x / 2 - 2, 16));
}

static void update(void) {
	if (input_pressed(A_START)) {
		engine_set_scene(&scene_game);
	}
		
	if (game_over) {
		return;
	}
	
	g.speed += engine.tick * (10.0 / g.speed);
	g.score += engine.tick * g.speed;
	engine.viewport.y += engine.tick * g.speed;
	
	// Do we need a new row?
	if (engine.viewport.y > 40) {
		
		// Move screen and entities one tile up
		engine.viewport.y -= 8;
		player->pos.y -= 8;
		entity_list_t coins = entities_by_type(ENTITY_TYPE_COIN);
		for (int i = 0; i < coins.len; i++) {
			entity_t *c = entity_by_ref(coins.entities[i]);
			c->pos.y -= 8;
		}

		// Move all tiles up one row
		memmove(map->data, map->data + map->size.x, (map->size.y - 1) * map->size.x * sizeof(uint16_t));

		// Generate new last row
		generate_row(map->size.y - 1);
		if (rand_int(0, 1) == 1) {
			place_coin(map->size.y - 1);
		}
	}

	scene_base_update();
	
	// Check for gameover
	float pp = player->pos.y - engine.viewport.y;
	if (pp > render_size().y + 8 || pp < -32) {
		game_over = true;
		sound_play(sound_game_over);		
	}
}

static void draw(void) {
	image_draw_ex(backdrop, vec2(0, 0), vec2_from_vec2i(image_size(backdrop)), vec2(0, 0), vec2_from_vec2i(render_size()), rgba_white());

	if (game_over) {
		font_draw(g.font, vec2(render_size().x/2, 32), "Game Over!",  FONT_ALIGN_CENTER);
		font_draw(g.font, vec2(render_size().x/2, 48), "Press Enter", FONT_ALIGN_CENTER);
		font_draw(g.font, vec2(render_size().x/2, 56), "to Restart",  FONT_ALIGN_CENTER);
	}
	else {
		scene_base_draw();
	}
		
	font_draw(g.font, vec2(render_size().x - 2, 2), str_format("%d", (int)g.score), FONT_ALIGN_RIGHT);
}

scene_t scene_game = {
	.init = init,
	.update = update,
	.draw = draw
};
