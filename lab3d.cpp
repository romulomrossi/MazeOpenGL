#include <GL/gl.h>     
#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "Robot.cpp"
//DEFINES--------------------------------------------

#define TAM_BLOCO 100
#define PASSO	1

#define NORTE  0
#define LESTE  1
#define SUL    2
#define OESTE  3

//GLOBALS--------------------------------------------

GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_shininess[] = { 50.0 };
GLfloat mat_amarelo[] = {0,.128,0, 1.0};
GLfloat mat_verde[] = {.169,.169,.169, 1.0 };
GLfloat mat_vermelho[] = { 0.7, 0.1, 0.1, 1.0 };
GLfloat light_position[] = { 0.0, 500.0, 0.0, 1.0 };
GLfloat luz_branca[] = {1.0,1.0,1.0,1.0};
GLfloat lmodel_ambient[] = {0.6,0.6,0.6,1.0};


GLfloat jog_x = TAM_BLOCO * 2.5 ;
GLfloat jog_z = TAM_BLOCO ;
GLfloat jog_y = 25;
GLfloat mov_x = PASSO;
GLfloat mov_z=0;
GLint angle = 0;
GLint increaseAngle = 0;
GLint wire = 0;
GLint mode = 0;


GLint mapa[15][15] = {
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,0,1,1,0,1,0,0,0,1,0,1,1,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,
	1,0,0,0,1,1,1,1,1,0,1,0,0,0,1,
	1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,
	1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,
	1,1,1,1,0,0,0,0,0,0,0,1,0,1,1,
	1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,
	1,0,1,0,1,0,0,0,0,0,1,0,1,0,1,
	1,0,0,0,1,0,1,1,1,0,1,0,0,0,1,
	1,0,1,0,0,0,0,1,0,0,0,0,1,0,1,
	1,0,1,1,1,1,0,0,0,1,0,1,1,0,1,
	1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};


double GetTickCount(void) 
{
  struct timespec now;
  if (clock_gettime(CLOCK_MONOTONIC, &now))
    return 0;
  return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}   

class Robot{

public:
    GLint coordinateX;
    GLint coordinateZ;
    GLint direction;
    Robot_ robot;

    void draw()
    {
        glPushMatrix();
        
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_vermelho);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    
        glTranslatef(coordinateX, 10,coordinateZ);

        increaseAngle = (angle+increaseAngle)%360;
        glRotatef(increaseAngle, 0, 1, 0);


        robot.draw();
        glPopMatrix();
    }
};

Robot robot = Robot();

//FUNCOES--------------------------------------------
int pode_mover(float pos_x, float pos_z, float vet_x, float vet_z)
{
	float mundo_x = pos_x + vet_x ;
	float mundo_z = pos_z + vet_z ;

	int ind_x = (int) ((mundo_x + TAM_BLOCO/2) / TAM_BLOCO);
	int ind_z = (int) ((mundo_z + TAM_BLOCO/2) / TAM_BLOCO);

	if(mapa[ind_x][ind_z]) return 0;
	else return 1;
}

void display(void)
{
  int x, z;
  int x_mun, z_mun;


  //limpa todos os pixels
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);										
 
  glLoadIdentity();
 
  if(mode)
  	gluLookAt(jog_x,jog_y,jog_z, robot.coordinateX,jog_y,robot.coordinateZ, 0,1,0);	
  else
  	gluLookAt(jog_x,jog_y*10,jog_z, robot.coordinateX,jog_y,robot.coordinateZ, 0,1,0);

	
  glPushMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_verde);

  glBegin ( GL_QUADS);

	 glVertex3f(-10000, -TAM_BLOCO/2, -10000);
 	 glVertex3f(-10000, -TAM_BLOCO/2, 10000);
	 glVertex3f(10000, -TAM_BLOCO/2, 10000);
	 glVertex3f(10000, -TAM_BLOCO/2, -10000);

  glEnd();

 glPopMatrix();

 //desenha Robot
    robot.draw();

  for(x=0; x < 15; x++)
  {
	for(z=0; z < 15; z++)
	{
	  if(mapa[x][z]) //tem um bloco
	  {
  	     x_mun = x * TAM_BLOCO;
		 z_mun = z * TAM_BLOCO;

		 //cubo grande
		glPushMatrix();

		 glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_amarelo);
		 glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		 glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
		
		 glTranslatef(x_mun, 5 ,z_mun);

		 if(wire) glutWireCube(TAM_BLOCO);
		 else glutSolidCube(TAM_BLOCO);
			
		glPopMatrix();

	  }//if(mapa[x][z]) 
	}//for
  }//for

 glutSwapBuffers();            
}

void Keyboard_Function(unsigned char key, int x, int y)
{
 switch (key) 
 {
  
  case  27: exit(0);break; //ESC -> encerra aplicativo... 
  case 'w':
  case 'W': wire =!wire;
			glutPostRedisplay();
			break;
	case 'x': mode = !mode;
	glutPostRedisplay();
	break;
 }

}

void Move_Robot(void)
{
	GLint mapa_x, mapa_z;
	
	GLint front, left, right;
	GLint num_rnd, currentDirection;

	double inicio_clock ;
	
	inicio_clock = GetTickCount() ;


	switch(robot.direction)
	{
		case NORTE : robot.coordinateZ -= PASSO; jog_z -=PASSO; break;
		case LESTE : robot.coordinateX += PASSO; jog_x += PASSO;break;
		case SUL   : robot.coordinateZ += PASSO; jog_z +=PASSO; break;
		case OESTE : robot.coordinateX -= PASSO; jog_x -= PASSO;break;
	}
    glRotatef(90, 0, 1, 0);
	
	if( (robot.coordinateX % TAM_BLOCO == 0) &&
		(robot.coordinateZ % TAM_BLOCO == 0) )
	{
		front = 0;
		left = 0;
		right = 0;

		mapa_x = (int) ((robot.coordinateX + TAM_BLOCO/2) / TAM_BLOCO);
		mapa_z = (int) ((robot.coordinateZ + TAM_BLOCO/2) / TAM_BLOCO);

        switch(robot.direction )
        {
            case NORTE :  
                if(mapa[mapa_x][mapa_z - 1] == 0)
                    front = 1;
                if(mapa[mapa_x + 1][mapa_z] == 0)
                    right = 1;
                if(mapa[mapa_x - 1][mapa_z] == 0)
                    left = 1;
                break;

            case LESTE :  
                if(mapa[mapa_x + 1][mapa_z] == 0)
                    front = 1;
                if(mapa[mapa_x][mapa_z + 1] == 0)
                    right = 1;
                if(mapa[mapa_x][mapa_z - 1] == 0)
                    left = 1;
                break;

            case SUL :  
                if(mapa[mapa_x][mapa_z + 1] == 0)
                    front = 1;
                if(mapa[mapa_x - 1][mapa_z] == 0)
                    right = 1;
                if(mapa[mapa_x + 1][mapa_z] == 0)
                    left = 1;
                break;

            case OESTE :  
                if(mapa[mapa_x - 1][mapa_z] == 0)
                    front = 1;
                if(mapa[mapa_x][mapa_z - 1] == 0)
                    right = 1;
                if(mapa[mapa_x][mapa_z + 1] == 0)
                    left = 1;
                break;
        }

		currentDirection = robot.direction;
            
		if(front)
		{
    		if(left && right)
			{
				num_rnd = rand() % 10;
				
				if(num_rnd < 4) robot.direction = currentDirection;
				else if(num_rnd > 6) robot.direction = (currentDirection + 1) & 3;
				else robot.direction = (currentDirection - 1) & 3;
			}
			else 
			if(left) 
			{
				if(!(rand()%2)) robot.direction = currentDirection ;
				else robot.direction = (currentDirection - 1) & 3;
			}
			else
			if(right)
			{
				if(!(rand()%2)) robot.direction = currentDirection ;
				else robot.direction = (currentDirection + 1) & 3;
			}
			else  robot.direction = currentDirection ;
		}
		else
		{
			if(left && right)
			{
				if(!(rand()%2)) robot.direction = (currentDirection + 1) & 3;
				else robot.direction = (currentDirection - 1) & 3;
			}
			else 
			if(left) 
			{
				robot.direction = (currentDirection - 1) & 3;
			}
			else
			if(right)
			{
				robot.direction = (currentDirection + 1) & 3;
			}
			else  robot.direction = (currentDirection + 2) & 3 ;
        }
        
        if(robot.direction != currentDirection){
            increaseAngle += 90;
        }
	}
	//esperar um pouco nos computadores mais rapidos
	while( (GetTickCount() - inicio_clock) < 25) ; 
    glutPostRedisplay();
}
//-----------------------------------------------------------------

void Inicializa(void)
{
    glShadeModel(GL_SMOOTH);

    glClearColor(0.3, 0.6, 0.8, 0.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_branca);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_branca);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //Especifica sistema de coordenadas de projecao
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

    //Especifica a projecao perspectiva
    gluPerspective(90,1,0.1,3000);

    //Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);

    // Inicializa sistema de coordenadas de projecao
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);			 

    // inicializa numeros aleatorios
    srand(GetTickCount());

    //posicao inicial da Robot
    robot.coordinateX = 3 * TAM_BLOCO;
    robot.coordinateZ = TAM_BLOCO;
    robot.direction = LESTE;
}

//--------------------------------------------------------------

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