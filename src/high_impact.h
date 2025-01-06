#ifndef HIGH_IMPACT_H
#define HIGH_IMPACT_H

// -----------------------------------------------------------------------------
// High Impact configuration

// These defines are ALL optional. They overwrite the defaults set by 
// high_impact and configure aspects of the library

// The values here (particularly resource limits) have been dialed in to this
// particular game. Increase them as needed. Allocating a few GB and thousands
// of entities is totally fine.

#define ALLOC_SIZE (32 * 1024 * 1024)
#define ALLOC_TEMP_OBJECTS_MAX 8

#define WINDOW_TITLE "Drop"
#define WINDOW_WIDTH (64*5)
#define WINDOW_HEIGHT (96*5)

#define GAME_VENDOR "phoboslab"
#define GAME_NAME "drop"

#define RENDER_WIDTH 64
#define RENDER_HEIGHT 96
#define RENDER_RESIZE_MODE RENDER_RESIZE_NONE
#define RENDER_SCALE_MODE RENDER_SCALE_DISCRETE

#define ENTITIES_MAX 64
#define ENTITY_MAX_SIZE 64
#define ENTITY_MIN_BOUNCE_VELOCITY 10

#define SOUND_MAX_UNCOMPRESSED_SAMPLES (64 * 1024)
#define SOUND_MAX_SOURCES 4
#define SOUND_MAX_NODES 8

#define IMAGE_MAX_SOURCES 64

#define RENDER_ATLAS_SIZE 64
#define RENDER_ATLAS_GRID 8
#define RENDER_ATLAS_BORDER 0
#define RENDER_BUFFER_CAPACITY 2048
#define RENDER_TEXTURES_MAX 64

#define ENGINE_MAX_TICK 0.1
#define ENGINE_MAX_BACKGROUND_MAPS 4

#include "../high_impact/src/alloc.h"
#include "../high_impact/src/animation.h"
#include "../high_impact/src/camera.h"
#include "../high_impact/src/entity_def.h"
#include "../high_impact/src/font.h"
#include "../high_impact/src/engine.h"
#include "../high_impact/src/image.h"
#include "../high_impact/src/input.h"
#include "../high_impact/src/map.h"
#include "../high_impact/src/noise.h"
#include "../high_impact/src/platform.h"
#include "../high_impact/src/render.h"
#include "../high_impact/src/sound.h"
#include "../high_impact/src/trace.h"
#include "../high_impact/src/types.h"
#include "../high_impact/src/utils.h"

// Careful, before we can include "../high_impact/src/entity.h", we need to set
// up our entity types.


// -----------------------------------------------------------------------------
// Entities

// This X-Macro will get called by ENTITY_DEFINE() and defines the entity_type_t
// enum, as well as the entity_vtab_t for each listed type.

// Each TYPE() must have a TYPE_NAME that can be used with e.g. 
// entity_spawn(ENTITY_TYPE_PLAYER, ...), and a SHORT_NAME that can be used for 
// the stringified name with e.g. entity_type_by_name("player")

// Every entity is also expected to have a global entity_vtab_t with the name
// entity_vtab_SHORT_NAME, e.g. entity_vtab_t entity_vtab_player = {...};

#define ENTITY_TYPES(TYPE) \
	TYPE(ENTITY_TYPE_COIN, coin) \
	TYPE(ENTITY_TYPE_PLAYER, player) \


// All entity types share the same struct. Calling ENTITY_DEFINE() defines that
// struct with the fields required by high_impact and the additional fields
// specified here.

ENTITY_DEFINE();


// The entity_message_t is used with the entity_message() function. You can
// extend this as you wish. 

typedef enum {
	EM_INVALID,
} entity_message_t;

// Now that we have all the prerequisites, we can include entity.h
#include "../high_impact/src/entity.h"

#endif