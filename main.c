#include <GL/glut.h>
#include "model.h"
#include "draw.h"
#include "camera.h"

#define GROUND_LEVEL 20

int mouse_x, mouse_y;

struct Camera camera;

struct Action
{
	int move_forward;
	int move_backward;
	int step_left;
	int step_right;
	int move_up;
	int move_down;
    int jump;
    int crouch;
	int increase_light;
	int decrease_light;

	int light_on;
};
struct Action action;
int time;


int WINDOW_WIDTH;
int WINDOW_HEIGHT;

World world;


int help, help_on = 0;

float speed = 30;
float angle = 135;


int CAN_JUMP=1;

int CURRENTLY_JUMPING=0;


void update_camera_position(struct Camera* camera, double elapsed_time)
{
	double distance;

	distance = elapsed_time * CAMERA_SPEED*speed;

	if (action.move_forward == TRUE) {
        if(action.crouch==TRUE) {
            move_camera_forward(camera, distance / 3);
        }
        else
		move_camera_forward(camera, distance);
	}

	if (action.move_backward == TRUE) {
        if(action.crouch==TRUE) {
            move_camera_backward(camera, distance / 3);
        } else
		move_camera_backward(camera, distance);

	}

	if (action.step_left == TRUE) {
        if(action.crouch==TRUE) {
            step_camera_left(camera, distance / 3);
        } else
		step_camera_left(camera, distance);
	}

	if (action.step_right == TRUE) {
        if(action.crouch==TRUE) {
            step_camera_right(camera, distance / 3);
        } else
		step_camera_right(camera, distance);
	}

//	if (action.move_up == TRUE) {
//		move_camera_up(camera, distance);
//	}
//
//	if (action.move_down == TRUE) {
//		move_camera_down(camera, distance);
//	}

    if(((action.jump == TRUE) && CAN_JUMP==1)|| CURRENTLY_JUMPING==1){
CURRENTLY_JUMPING=1;
        printf("%d", CURRENTLY_JUMPING);
    move_camera_jump(camera,distance,&CAN_JUMP, &CURRENTLY_JUMPING);
    } else if(camera->position.y>GROUND_LEVEL ){
        if(camera->position.y>35)
            camera->position.y -= 1;
        else if (camera->position.y>30)
            camera->position.y-=2;
        else if (camera->position.y<=30)
            camera->position.y-=2.5;
        if (camera->position.y<21) {
            camera->position.y=20;
            CAN_JUMP = 1;
            CURRENTLY_JUMPING = 0;

        }
    }

    if((action.crouch==TRUE) && (CURRENTLY_JUMPING==0) ){
        move_camera_crouch(camera);
    }
 else if(camera->position.y<GROUND_LEVEL){
        camera->position.y+=3;
    if (camera->position.y>GROUND_LEVEL){
        camera->position.y=GROUND_LEVEL;

    }}


	if (action.increase_light == TRUE) {
		if (world.global_ambient[0] < 1)
			world.global_ambient[0] = world.global_ambient[1] = world.global_ambient[2] += 0.1;
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.global_ambient);
	}

	if (action.decrease_light == TRUE) {
		if (world.global_ambient[0] > 0)
			world.global_ambient[0] = world.global_ambient[1] = world.global_ambient[2] -= 0.1;
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.global_ambient);
	}

	if (action.light_on) {
        glEnable(GL_LIGHT5);
	}
	else {
		glDisable(GL_LIGHT5);
	}
}

double calc_elapsed_time()
{
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - time) / 1000.0;
	time = current_time;


	return elapsed_time;
}
/*
* Handles special keyboard buttons 
*/
void specialFunc(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F1:
		if (help_on) {
			help_on = 0;

			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, world.material_ambient);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.global_ambient);
		}
		else {
			help_on = 1;

			GLfloat ones[] = { 1, 1, 1, 1 };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ones);
			glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ones);
		}
	}

}
void reshape(GLsizei width, GLsizei height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!help_on)
		gluPerspective(50.0, (GLdouble)width / (GLdouble)height, 0.1, 20000.0);
	else
		gluOrtho2D(0, width, height, 0);
}
/*
* Draws the help menu
*/

void init_entities(World *world) {
    //TODO
    load_model("objects//portal.obj", &world->portal.model);
    world->portal.texture = load_texture("textures/darkcave.jpg");
    world->ground = load_texture("textures//groundtexture.png");
    world->walltexture = load_texture("textures//walltex.png");
    world->skybox = load_texture("textures//darkcave2.jpg");
}

void draw_help() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, help);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(WINDOW_WIDTH, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glTexCoord2f(0, 1);
	glVertex3f(0, WINDOW_HEIGHT, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutSwapBuffers();
}
void display() {
	if (!help_on) {
		double elapsed_time;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		elapsed_time = calc_elapsed_time();
		update_camera_position(&camera, elapsed_time);

        GLfloat light_position[] = { 0.0, 500.0, 0.0, 0.0 };
        GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 0 };
        GLfloat light_diffuse[] = { 0.5, 0.5, 0.5, 0 };
        GLfloat light_specular[] = { 1, 1, 1, 0 };

        glLightfv(GL_LIGHT5, GL_POSITION, light_position);
        glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);
        glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
        glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
        if(action.light_on)
            glEnable(GL_LIGHT5);

		
		glEnable(GL_LIGHT0);
		draw_environment(world);
        draw_entities(world);


		reshape(WINDOW_WIDTH, WINDOW_HEIGHT);
		glutSwapBuffers();
		set_view_point(&camera);
	}
	else {
		draw_help();
	}
}

void mouse_handler(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

void motion_handler(int x, int y)
{
	double horizontal, vertical;

	horizontal = mouse_x - x;
	vertical = mouse_y - y;

	rotate_camera(&camera, horizontal, vertical);

	mouse_x = x;
	mouse_y = y;

	glutPostRedisplay();
}

void key_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = TRUE;
		break;
	case 's':
		action.move_backward = TRUE;
		break;
	case 'a':
		action.step_left = TRUE;
		break;
	case 'd':
		action.step_right = TRUE;
		break;
	case 'c':
		action.crouch = TRUE;
		break;
	case 32:
		action.jump = TRUE;
		break;

	case '+':
		action.increase_light = TRUE;
		break;
	case '-':
		action.decrease_light = TRUE;
		break;
	case 27:
		exit(0);
	}

	glutPostRedisplay();
}

void key_up_handler(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		action.move_forward = FALSE;
		break;
	case 's':
		action.move_backward = FALSE;
		break;
	case 'a':
		action.step_left = FALSE;
		break;
	case 'd':
		action.step_right = FALSE;
		break;
	case 'c':
		action.crouch = FALSE;
		break;
		case 32:
		action.jump = FALSE;
		break;
	case '+':
		action.increase_light = FALSE;
		break;
	case '-':
		action.decrease_light = FALSE;
		break;
	case 27:
		exit(0);
	}

	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay();
}

void set_callbacks() {
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key_handler);
	glutKeyboardUpFunc(key_up_handler);
	glutMouseFunc(mouse_handler);
	glutMotionFunc(motion_handler);
	glutIdleFunc(idle);
	glutSpecialFunc(specialFunc);
}
void init_world(World* world) {
	world->global_ambient[0] = 0.7;
	world->global_ambient[1] = 0.7;
	world->global_ambient[2] = 0.7;
	world->global_ambient[3] = 1.0;

	world->material_ambient[0] = 0.7;
	world->material_ambient[1] = 0.7;
	world->material_ambient[2] = 0.7;
	world->material_ambient[3] = 1.0;

	world->diffuse_light_emission[0] = 0.7;
	world->diffuse_light_emission[1] = 0.7;
	world->diffuse_light_emission[2] = 0.7;
	world->diffuse_light_emission[3] = 1;

	init_entities(world);
}
void init_difuse_light() {
GLfloat light_position[] = { 100.0, 100.0, 100.0, 0.0 };
    GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 0 };
    GLfloat light_diffuse[] = { 0.5, 0.5, 0, 0 };
    GLfloat light_specular[] = { 1, 1, 1, 0 };

    glLightfv(GL_LIGHT5, GL_POSITION, light_position);
    glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
    glEnable(GL_LIGHT5);

}
void init_lighting() {
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, world.global_ambient);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	init_difuse_light();
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
}

void init_material() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, world.material_ambient);
}
void init() {
	set_callbacks();

	init_camera(&camera);
	init_world(&world);

	init_lighting();
	init_material();

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
//TODO HELP IMGAGE
	help = load_texture("textures//helpimage.png");

}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	//glutInitWindowSize(2560, 1080);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	int wnd = glutCreateWindow("Pyramid Escape");
	glutSetWindow(wnd);

	init();

	glutMainLoop();

	return 0;
}

