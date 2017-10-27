#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "Robot.cpp"
//sudo g++ lab3d.cpp -o lab -lGL -lGLU -lglut
//DEFINES--------------------------------------------

#define BLOCKSIZE 100
#define PASSO 5

#define NORTE 0
#define LESTE 1
#define SUL 2
#define OESTE 3

//GLOBALS--------------------------------------------

GLfloat getSpecularMaterial[] = {1.0, 1.0, 1.0, 1.0};
GLfloat getShininessMaterial[] = {50.0};
GLfloat material1[] = {0, .128, 0, 1.0};
GLfloat material2[] = {.169, .169, .169, 1.0};
GLfloat material3[] = {0.7, 0.1, 0.1, 1.0};
GLfloat material4[] = {0.7, 0.4, 0.5, 1};
GLfloat getLightPosition[] = {0.0, 500.0, 0.0, 1.0};
GLfloat whiteLight[] = {1.0, 1.0, 1.0, 1.0};
GLfloat ambientModel[] = {0.6, 0.6, 0.6, 1.0};

GLfloat cameraCoordinateX = BLOCKSIZE * 2.5;
GLfloat cameraCoordinateZ = BLOCKSIZE;
GLfloat cameraCoordinateY = 25;
GLint angle = 0;
GLint increaseAngle = 0;
GLint wire = 0;
GLint mode = 0;

class Robot
{
  public:
	GLint coordinateX;
	GLint coordinateZ;
	GLint direction;
	Robot_ robot;

	void draw()
	{
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material3);
		glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecularMaterial);
		glMaterialfv(GL_FRONT, GL_SHININESS, getShininessMaterial);

		glTranslatef(coordinateX, 10, coordinateZ);

		increaseAngle = (angle + increaseAngle) % 360;
		glRotatef(increaseAngle, 0, 1, 0);

		robot.draw();
		glPopMatrix();
	}
};

GLint maze[15][15] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1,
	1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
	1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

Robot robot = Robot();

double GetTickCount(void)
{
	struct timespec now;
	if (clock_gettime(CLOCK_MONOTONIC, &now))
		return 0;
	return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	if (mode)
	{
		gluLookAt(cameraCoordinateX,
				  cameraCoordinateY,
				  cameraCoordinateZ,
				  robot.coordinateX,
				  cameraCoordinateY,
				  robot.coordinateZ, 0, 1, 0);
	}
	else
	{
		gluLookAt(700, 900, 1000,
				  700, -1500, 600, 0, 1, 0);
	}

	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material2);

	glBegin(GL_QUADS);

	glVertex3f(-10000, -BLOCKSIZE / 2, -10000);
	glVertex3f(-10000, -BLOCKSIZE / 2, 10000);
	glVertex3f(10000, -BLOCKSIZE / 2, 10000);
	glVertex3f(10000, -BLOCKSIZE / 2, -10000);

	glEnd();
	glPopMatrix();

	//desenha Robot
	robot.draw();

	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			if (maze[x][z]) //tem um bloco
			{
				int globalCoordinateX = x * BLOCKSIZE;
				int globalCoordinateZ = z * BLOCKSIZE;

				//cubo grande
				glPushMatrix();
				if(z%2 != x%2)
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material1);
				else
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material2);
				glMaterialfv(GL_FRONT, GL_SPECULAR, getSpecularMaterial);
				glMaterialfv(GL_FRONT, GL_SHININESS, getShininessMaterial);

				glTranslatef(globalCoordinateX, 5, globalCoordinateZ);

				if (wire)
					glutWireCube(BLOCKSIZE);
				else
					glutSolidCube(BLOCKSIZE);

				glPopMatrix();
			}
		}
	}

	glutSwapBuffers();
}

void Keyboard_Function(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 27:
		exit(0);
		break; //ESC -> encerra aplicativo...
	case 'w':
	case 'W':
		wire = !wire;
		glutPostRedisplay();
		break;
	case 'x':
	case 'X':
		mode = !mode;
		glutPostRedisplay();
		break;
	}
}

void Move_Robot(void)
{
	GLint maze_x, maze_z;

	GLint front, left, right;
	GLint num_rnd, currentDirection;

	double inicio_clock;

	inicio_clock = GetTickCount();

	switch (robot.direction)
	{
	case NORTE:
		robot.coordinateZ -= PASSO;
		cameraCoordinateZ -= PASSO;
		break;
	case LESTE:
		robot.coordinateX += PASSO;
		cameraCoordinateX += PASSO;
		break;
	case SUL:
		robot.coordinateZ += PASSO;
		cameraCoordinateZ += PASSO;
		break;
	case OESTE:
		robot.coordinateX -= PASSO;
		cameraCoordinateX -= PASSO;
		break;
	}
	glRotatef(90, 0, 1, 0);

	if ((robot.coordinateX % BLOCKSIZE == 0) &&
		(robot.coordinateZ % BLOCKSIZE == 0))
	{
		front = 0;
		left = 0;
		right = 0;

		maze_x = (int)((robot.coordinateX + BLOCKSIZE / 2) / BLOCKSIZE);
		maze_z = (int)((robot.coordinateZ + BLOCKSIZE / 2) / BLOCKSIZE);

		switch (robot.direction)
		{
		case NORTE:
			if (maze[maze_x][maze_z - 1] == 0)
				front = 1;
			if (maze[maze_x + 1][maze_z] == 0)
				right = 1;
			if (maze[maze_x - 1][maze_z] == 0)
				left = 1;
			break;

		case LESTE:
			if (maze[maze_x + 1][maze_z] == 0)
				front = 1;
			if (maze[maze_x][maze_z + 1] == 0)
				right = 1;
			if (maze[maze_x][maze_z - 1] == 0)
				left = 1;
			break;

		case SUL:
			if (maze[maze_x][maze_z + 1] == 0)
				front = 1;
			if (maze[maze_x - 1][maze_z] == 0)
				right = 1;
			if (maze[maze_x + 1][maze_z] == 0)
				left = 1;
			break;

		case OESTE:
			if (maze[maze_x - 1][maze_z] == 0)
				front = 1;
			if (maze[maze_x][maze_z - 1] == 0)
				right = 1;
			if (maze[maze_x][maze_z + 1] == 0)
				left = 1;
			break;
		}

		currentDirection = robot.direction;

		if (front)
		{
			if (left && right)
			{
				num_rnd = rand() % 10;

				if (num_rnd < 4)
					robot.direction = currentDirection;
				else if (num_rnd > 6)
					robot.direction = (currentDirection + 1) & 3;
				else
					robot.direction = (currentDirection - 1) & 3;
			}
			else if (left)
			{
				if (!(rand() % 2))
					robot.direction = currentDirection;
				else
					robot.direction = (currentDirection - 1) & 3;
			}
			else if (right)
			{
				if (!(rand() % 2))
					robot.direction = currentDirection;
				else
					robot.direction = (currentDirection + 1) & 3;
			}
			else
				robot.direction = currentDirection;
		}
		else
		{
			if (left && right)
			{
				if (!(rand() % 2))
					robot.direction = (currentDirection + 1) & 3;
				else
					robot.direction = (currentDirection - 1) & 3;
			}
			else if (left)
			{
				robot.direction = (currentDirection - 1) & 3;
			}
			else if (right)
			{
				robot.direction = (currentDirection + 1) & 3;
			}
			else{
				robot.direction = (currentDirection + 2) & 3;
				increaseAngle+=90;
			}
		}

		if (robot.direction != currentDirection)
		{
			increaseAngle += 90;
		}
	}

	while ((GetTickCount() - inicio_clock) < 25)
		;
	glutPostRedisplay();
}
//-----------------------------------------------------------------

void Inicializa(void)
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.3, 0.6, 0.8, 0.0);

	glLightfv(GL_LIGHT0, GL_POSITION, getLightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLight);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientModel);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 3000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	srand(GetTickCount());

	robot.coordinateX = 3 * BLOCKSIZE;
	robot.coordinateZ = BLOCKSIZE;
	robot.direction = LESTE;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Labirinto 3D");
	glutFullScreen();

	Inicializa();

	glutDisplayFunc(display);
	glutKeyboardFunc(Keyboard_Function);
	glutIdleFunc(Move_Robot);

	glutMainLoop();
}