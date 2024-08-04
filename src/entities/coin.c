#include "../main.h"

static anim_def_t *anim_idle;
static sound_source_t *sound_collect;

static void load(void) {
	image_t *sheet = image("assets/coin.qoi");
	anim_idle = anim_def(sheet, vec2i(4, 4), 0.1, {0,1});
	sound_collect = sound_source("assets/coin.qoa");
}

static void init(entity_t *self) {
	self->anim = anim(anim_idle);
	self->size = vec2(6, 6);
	self->offset = vec2(-1, -1);

	self->check_against = ENTITY_GROUP_PLAYER;
}

static void update(entity_t *self) {
	if (self->pos.y - engine.viewport.y < -32) {
		entity_kill(self);
	}
}

static void touch(entity_t *self, entity_t *other) {
	g.score += 500;
	sound_play(sound_collect);
	entity_kill(self);
}

entity_vtab_t entity_vtab_coin = {
	.load = load,
	.init = init,
	.touch = touch,
	.update = update,
};
