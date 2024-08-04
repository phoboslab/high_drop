#ifndef MAIN_H
#define MAIN_H

#include "high_impact.h"


// -----------------------------------------------------------------------------
// Button actions

typedef enum {
	A_LEFT,
	A_RIGHT,
	A_START,
} action_t;


// -----------------------------------------------------------------------------
// Global data

typedef struct {
	font_t *font;
	float score;
	float speed;
} global_t;

extern global_t g;


// -----------------------------------------------------------------------------
// Scenes

extern scene_t scene_game;

#endif