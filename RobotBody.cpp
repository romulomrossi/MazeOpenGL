
#define MEL matrixElementlength 

class RobotBody
{
    GLfloat matrixElementlength =  5.0;

    GLfloat v[8][3] = { 
        {-MEL,-MEL,-MEL}, 
        { MEL,-MEL,-MEL}, 
        { MEL, MEL,-MEL}, 
        {-MEL, MEL,-MEL},
        { MEL,-MEL, MEL}, 
        {-MEL,-MEL, MEL}, 
        {-MEL, MEL, MEL}, 
        { MEL, MEL, MEL}
    };

public:
    void draw()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glBegin(GL_QUADS);
        drawFront();
        drawBack();
        drawLeft();
        drawTop();
        drawRight();
        drawBase();
        glEnd();
    }

private:
    void drawFront()
    {
        glVertex3fv(v[0]);
        glVertex3fv(v[1]);
        glVertex3fv(v[2]);
        glVertex3fv(v[3]);
    }
  
    void drawBack()
    {
        glVertex3fv(v[4]);
        glVertex3fv(v[5]);
        glVertex3fv(v[6]);
        glVertex3fv(v[7]);
    }    

    void drawLeft()
    {
        glVertex3fv(v[0]);
        glVertex3fv(v[3]);
        glVertex3fv(v[6]);
        glVertex3fv(v[5]);
    }

    void drawTop()
    {
        glVertex3fv(v[3]);
        glVertex3fv(v[2]);
        glVertex3fv(v[7]);
        glVertex3fv(v[6]);
    }

    void drawRight()
    {
        glVertex3fv(v[1]);
        glVertex3fv(v[4]);
        glVertex3fv(v[7]);
        glVertex3fv(v[2]);
    }

    void drawBase()
    {
        glVertex3fv(v[1]); 
        glVertex3fv(v[0]);
        glVertex3fv(v[5]);
        glVertex3fv(v[4]);
    }
};