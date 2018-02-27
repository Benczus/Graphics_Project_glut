#ifndef DRAW_H
#define DRAW_H

#include "model.h"
#include "AABB.h"

#ifndef GL_EXT_texture_edge_clamp
#define GL_EXT_CLAMP_TO_EDGE                 0x812F
#endif

typedef struct 
{
	 Vector2f position;
    double height;
            AABBbox boundingBox;
} Cuboid;

/**
* Draw the model.
*/
void draw_model(const struct Model* model);

/**
* Draw the triangles of the model.
*/
void draw_triangles(const struct Model* model);

/**
* Draws the ground
*/
void draw_ground(int ground);

/*
* Draws the left side of the skybox
*/
void draw_skybox_left(Skybox skybox);

/*
* Draws the right side of the skybox
*/
void draw_skybox_right(Skybox skybox);

/*
* Draws the front side of the skybox
*/
void draw_skybox_front(Skybox skybox);

/*
* Draws the back side of the skybox
*/
void draw_skybox_back(Skybox skybox);

/*
* Draws the top of the skybox
*/
void draw_skybox_top(Skybox skybox);

/*
* Calls the draw_skybox_* and draw_ground methodes, makes the display lists
*/
void draw_environment(World world);

/*
* Adds texture to the skybox
*/
void load_skybox(Skybox* skybox);


void draw_entities(World world);

void draw_wall(int ground, int x, int y);
void draw_labirynth(int ground);
void draw_horizontal_wall(int ground, int x1, int x2, int y);
void draw_vertical_wall(int ground, int x, int y1, int y2);
#endif // DRAW_H

