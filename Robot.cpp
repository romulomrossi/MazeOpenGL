#include "RobotHead.cpp"
#include "RobotBody.cpp"
#include "RobotFoot.cpp"

class Robot_
{
public:
    RobotHead head = RobotHead();
    RobotBody body = RobotBody();
    RobotFoot rightFoot = RobotFoot();
    RobotFoot leftFoot = RobotFoot();

public:
    void draw()
    {
        glPushMatrix();
        head.draw();
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, -10 ,0);
        body.draw();
        glPopMatrix();
        glPushMatrix();
        glTranslated(0, -16, 5);
        rightFoot.draw();
        glPopMatrix();
        glPushMatrix();
        glTranslated(0, -16, 10);
        glutSolidCone(5, 2, 32, 25);
        glPopMatrix();
        glPushMatrix();
        glTranslated(0, -16, -10);
        leftFoot.draw();
        glRotatef(180, 1, 0, 0);
        glutSolidCone(5, 2, 32, 25);
        glPopMatrix();
  
    }
};