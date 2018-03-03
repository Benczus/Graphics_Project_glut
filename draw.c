#include "draw.h"
#include <GL/glut.h>
#include <SOIL/SOIL.h>

double wind_speed=0;
double skybox_size = 1000;
double skybox_half= 500;
double UNIT=50;
GLuint displayList1 = 0;
GLuint displayList2 = 1;
typedef GLubyte Pixel;

void draw_model(const struct Model* model)
{
	draw_triangles(model);
	
}

void draw_triangles(const struct Model* model)
{
	int i, k;
	int vertex_index, texture_index, normal_index;
	double x, y, z, normal_x, normal_y, normal_z, u, v;

	glBegin(GL_TRIANGLES);

	for (i = 0; i < model->n_triangles; ++i) {
		for (k = 0; k < 3; ++k) {
			normal_index = model->triangles[i].points[k].normal_index;
			normal_x = model->normals[normal_index].x;
			normal_y = model->normals[normal_index].y;
			normal_z = model->normals[normal_index].z;
			glNormal3d(normal_x, normal_y, normal_z);

			vertex_index = model->triangles[i].points[k].vertex_index;
			x = model->vertices[vertex_index].x;
			y = model->vertices[vertex_index].y;
			z = model->vertices[vertex_index].z;
            switch(k){
            case 0:
                glTexCoord2f(0, 0);
                break;
            case 1:
                glTexCoord2f(0.1*z, 0);
                break;
            case 2:
                glTexCoord2f(0, 0.01);
                break;
            }
			glVertex3d(x, y, z);

		}
	}

	glEnd();
}

void draw_normals(const struct Model* model, double length)
{
	int i;
	double x1, y1, z1, x2, y2, z2;

	glColor3f(0, 0, 1);

	glBegin(GL_LINES);

	for (i = 0; i < model->n_vertices; ++i) {
		x1 = model->vertices[i].x;
		y1 = model->vertices[i].y;
		z1 = model->vertices[i].z;
		x2 = x1 + model->normals[i].x * length;
		y2 = y1 + model->normals[i].y * length;
		z2 = z1 + model->normals[i].z * length;
		glVertex3d(x1, y1, z1);
		glVertex3d(x2, y2, z2);
	}
	glEnd();
}

void draw_ground(int ground) {
	glBindTexture(GL_TEXTURE_2D, ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBegin(GL_QUADS);
	int x, z;
	for (x = -skybox_size; x < skybox_size; x += 50) {
		for (z = -skybox_size; z < skybox_size; z += 50) {
			glTexCoord2f(0.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z);
			glTexCoord2f(1.0, 0.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z);
			glTexCoord2f(1.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x + 50, 0, z + 50);
			glTexCoord2f(0.0, 1.0);
			glNormal3f(0, -1, 0);
			glVertex3f(x, 0, z + 50);
		}
	}
	glEnd();
}

void draw_wall(int walltex, int x, int y) {
    glBindTexture(GL_TEXTURE_2D, walltex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0, 0.0);
//	glNormal3f(0, -1, 0);
//	glVertex3f(x, 0, y);
//
//	glTexCoord2f(0.0, 1.0);
//	glNormal3f(0, -1, 0);
//	glVertex3f(x , 0, y+50);
//
//	glTexCoord2f(1.0, 1.0);
//	glNormal3f(0, -1, 0);
//	glVertex3f(x+50, 0, y+50);
//
//	glTexCoord2f(1.0, 0.0);
//	glNormal3f(0, -1, 0);
//	glVertex3f(x+50, 0, y);
//
//	glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x, 0, y);

    glTexCoord2f(0.0, 1.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x , 100, y);

    glTexCoord2f(1.0, 1.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x+50,100, y);

    glTexCoord2f(1.0, 0.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x+50, 0, y);

    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x, 0, y);

    glTexCoord2f(0.0, 1.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x , 100,y);

    glTexCoord2f(1.0, 1.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x, 100,y+50);

    glTexCoord2f(1.0, 0.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x, 0, y+50);

    glEnd();

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x+50, 0, y);

    glTexCoord2f(0.0, 1.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x+50, 100,y);

    glTexCoord2f(1.0, 1.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x+50, 100, y+50);

    glTexCoord2f(1.0, 0.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x+50, 0, y+50);

    glEnd();

//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0, 0.0);
//    glNormal3f(0, -1, 0);
//    glVertex3f(x, 100, y);
//
//    glTexCoord2f(0.0, 1.0);
//    glNormal3f(0, -1, 0);
//    glVertex3f(x+50, 100,y);
//
//    glTexCoord2f(1.0, 1.0);
//    glNormal3f(0, -1, 0);
//    glVertex3f(x+50, 100, y+50);
//
//    glTexCoord2f(1.0, 0.0);
//    glNormal3f(0, -1, 0);
//    glVertex3f(x, 100, y+50);
//
//    glEnd();


    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 0.0);
    glNormal3f(0, -1, 0);
    glVertex3f(x, 0,y+50);
    glTexCoord2f(0.0, 0.0);

    glNormal3f(0, -1, 0);
    glVertex3f(x+50, 0,y+50);
    glTexCoord2f(0.0, 1.0);

    glNormal3f(0, -1, 0);
    glVertex3f(x+50, 100, y+50);
    glTexCoord2f(1.0, 1.0);

    glNormal3f(0, -1, 0);
    glVertex3f(x, 100, y+50);

    glEnd();





}

void draw_skybox(int texture) {
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-skybox_size, 0, -skybox_size);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-skybox_size, skybox_half, -skybox_size);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-skybox_size, skybox_half, skybox_size);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-skybox_size, 0, skybox_size);
	glEnd();

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(skybox_size, 0, skybox_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(skybox_size, skybox_half, skybox_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(skybox_size, skybox_half, -skybox_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(skybox_size, 0, -skybox_size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-skybox_size, 0, -skybox_size);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(skybox_size, 0, -skybox_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(skybox_size, skybox_half, -skybox_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-skybox_size, skybox_half, -skybox_size);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(-skybox_size, 0, skybox_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(-skybox_size, skybox_half, skybox_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(skybox_size, skybox_half, skybox_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(skybox_size, 0, skybox_size);
    glEnd();


    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_EXT_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex3f(skybox_size, skybox_half, skybox_size);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(skybox_size, skybox_half, -skybox_size);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-skybox_size, skybox_half, -skybox_size);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-skybox_size, skybox_half, skybox_size);


    glEnd();
}

void draw_environment(World world) {
	glEnable(GL_TEXTURE_2D);


    glNewList(displayList1, GL_COMPILE);
            GLfloat material_specular[] = {1, 1, 1, 1};
            glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
            GLfloat material_ambient_2[] = {0.5, 0.5, 0.5, 1};
            GLfloat material_diffuse_2[] = {0.7, 0.7, 0.7, 1};
            glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_2);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse_2);
            GLfloat material_shininess[] = { 50.0 };
            glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
    glBindTexture(GL_TEXTURE_2D, world.portal.texture);
    draw_model(&world.portal.model);
		glEndList();

//		displayList2 = glGenLists(1);
//		glNewList(displayList2, GL_COMPILE);
//            glRotatef(180,1,0,0);
//            glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
//            glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_2);
//            glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse_2);
//            glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
//		glBindTexture(GL_TEXTURE_2D, world.windmill2.texture);
//		draw_model(&world.windmill2.model);
//		glEndList();

	draw_ground(world.ground);


    glCallList(1);

	GLfloat zeros[] = { 0, 0, 0 };
	GLfloat ones[] = { 1, 1, 1 };

	glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ones);

    draw_skybox(world.skybox);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, world.material_ambient);

	glDisable(GL_TEXTURE_2D);
}



void draw_teapot_for_light(){
    glPushMatrix();
        GLfloat material_specular[] = {1, 1, 1, 1};
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        GLfloat material_ambient_2[] = {0.5, 0.5, 0.5, 1};
        GLfloat material_diffuse_2[] = {0.7, 0.7, 0.7, 1};
        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient_2);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse_2);
        GLfloat material_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);
        glTranslatef(500, 10,500);
        glScalef(10, 10, 10);
        glutSolidTeapot(1.0); 
    glPopMatrix();
}
void draw_entities(World world) {
	glEnable(GL_TEXTURE_2D);
    draw_teapot_for_light();
    draw_portal();
	glDisable(GL_TEXTURE_2D);
}

void draw_dungeon(int walltex) {


    glNewList(displayList2, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, walltex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    draw_start_area(walltex);

    draw_vertical_wall(walltex, 1, 1, 3);

    draw_horizontal_wall(walltex, 0, -5, 3);
    draw_vertical_wall(walltex, -5, 2, -2);
    draw_horizontal_wall(walltex, 1, -5, -5);
    draw_vertical_wall(walltex, -5, -6, -11);
    draw_horizontal_wall(walltex, 0, -5, -11);
    draw_vertical_wall(walltex, 0, -8, -11);
    draw_horizontal_wall(walltex, -2, 3, -8);
    draw_vertical_wall(walltex, 4, 0, -8);
    draw_horizontal_wall(walltex, 4, 1, 0);
    glEndList();

}

void draw_portal() {
    glPushMatrix();
    glCallList(displayList1);
    glPopMatrix();
}

void draw_horizontal_wall(int ground, int x1, int x2, int y) {


    if (x1 > x2)
        for (int i = x2; i <= x1; i++) {
            draw_wall(ground, i * UNIT, y * UNIT);
        }
    else
        for (int i = x1; i <= x2; i++) {
            draw_wall(ground, i * UNIT, y * UNIT);
        }


}

void draw_vertical_wall(int ground, int x, int y1, int y2) {


    if (y1 > y2)
        for (int i = y2; i <= y1; i++) {
            draw_wall(ground, x * UNIT, i * UNIT);
        }
    else
        for (int i = y1; i <= y2; i++) {
            draw_wall(ground, x * UNIT, i * UNIT);
        }

}

void draw_start_area(int ground) {
    draw_wall(ground, UNIT, 0);

    draw_wall(ground, UNIT, -UNIT);
    draw_wall(ground,UNIT, -2*UNIT);
    draw_wall(ground,0,-2*UNIT);
    draw_wall(ground,-UNIT,-2*UNIT);
    draw_wall(ground,-2*UNIT,-2*UNIT);
    draw_wall(ground,-2*UNIT,-1*UNIT);
    draw_wall(ground,-2*UNIT,0);
}

GLuint load_texture(const char *filename) {
    GLuint texture_name;
    Pixel *image;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    image = (Pixel *) SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGBA);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (Pixel *) image);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    SOIL_free_image_data(image);

    return texture_name;
}





