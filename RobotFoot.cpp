class RobotFoot
{
    
    GLint angle;

public:
    void draw()
    {
        GLUquadricObj *quadratic = gluNewQuadric();
        gluQuadricNormals(quadratic, GLU_SMOOTH);
        gluQuadricTexture(quadratic, GL_TRUE);
        gluQuadricDrawStyle(quadratic, GLU_FILL); // FILL or LINE
        glRotatef(angle++, 0, 0, 1);
        gluCylinder(quadratic, 5, 5, 5, 25, 15);
    }
};
