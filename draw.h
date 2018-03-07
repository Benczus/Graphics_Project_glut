#ifndef DRAW_H
#define DRAW_H

#include <GL/gl.h>
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
void draw_skybox(int skybox);

void draw_environment(World world);

/*
* Adds texture to the skybox
*/

void draw_start_area(int ground);

void draw_entities(World world);

void draw_wall(int ground, int x, int y);

void draw_dungeon(int ground);
void draw_horizontal_wall(int ground, int x1, int x2, int y);
void draw_vertical_wall(int ground, int x, int y1, int y2);

void draw_static_elements(int groundtex, int walltex, int skyboxtex);

void draw_portal(World world);

void draw_portal_texture(int walltex, float x, float y);
GLuint load_texture(const char *filename);
#endif // DRAW_H

