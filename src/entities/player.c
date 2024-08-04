#include "../main.h"

static anim_def_t *anim_idle;
static image_t *hints;
static sound_source_t *sound_bounce;

static void load(void) {
	image_t *sheet = image("assets/player.qoi");
	anim_idle = anim_def(sheet, vec2i(4, 4), 1.0, {0});
	sound_bounce = sound_source("assets/bounce.qoa");
	hints = image("assets/hints.qoi");
}

static void init(entity_t *self) {
	self->anim = anim(anim_idle);
	self->size = vec2(4, 4);
	self->friction = vec2(4, 0);
	self->restitution = 0.5;

	self->group = ENTITY_GROUP_PLAYER;
	self->physics = ENTITY_PHYSICS_WORLD;
}

static void update(entity_t *self) {
	if (input_state(A_LEFT)) {
		self->accel.x = -300;
	}
	else if (input_state(A_RIGHT)) {
		self->accel.x = 300;
	}
	else {
		self->accel.x = 0;
	}
	entity_base_update(self);
}

static void draw(entity_t *self, vec2_t viewport) {
	entity_base_draw(self, viewport);

	// Draw arrows when player is off-screen
	if (self->pos.y < viewport.y - 4) {
		image_draw_tile(hints, 1, vec2i(4,4), vec2(self->pos.x, 0));
	}
	else if (self->pos.x < -4) {
		image_draw_tile(hints, 0, vec2i(4,4), vec2(0, self->pos.y - viewport.y));
	}
	else if (self->pos.x > render_size().x) {
		image_draw_tile(hints, 2, vec2i(4,4), vec2(render_size().x - 4, self->pos.y - viewport.y));
	}
}

static void collide(entity_t *self, vec2_t normal, trace_t *trace) {
	if (normal.y == -1 && self->vel.y > 32) {
		sound_play(sound_bounce);
	}
}

entity_vtab_t entity_vtab_player = {
	.load = load,
	.init = init,
	.update = update,
	.draw = draw,
	.collide = collide,
};
