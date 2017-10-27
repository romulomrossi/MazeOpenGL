class RobotHead
{

    GLint angle;
    double moveRobotHeadCoordinateY = 0;
    bool robotHeadMoveMode = true;

    bool compareDouble(double a, double b)
    {
        return fabs(a-b) < 0.00001;
    }

  public:
    void draw()
    {
        GLUquadricObj * quadratic=gluNewQuadric();         
        gluQuadricNormals(quadratic, GLU_SMOOTH);
        gluQuadricTexture(quadratic, GL_TRUE);
        gluQuadricDrawStyle(quadratic, GLU_LINE); // FILL or LINE
        glTranslated(0, moveRobotHeadCoordinateY/10, 0);
        glRotatef(angle++, 1, 0, 0);
        gluSphere(quadratic,5,25,32); 
        
        if(robotHeadMoveMode){
            moveRobotHeadCoordinateY+= 1;
            robotHeadMoveMode = !compareDouble(moveRobotHeadCoordinateY,35);
        }
        else {
            moveRobotHeadCoordinateY-= 1;
            robotHeadMoveMode = compareDouble(moveRobotHeadCoordinateY, 0);
        }
    }
};