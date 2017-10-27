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
        glTranslatef(0, -10 ,0);
        body.draw();
        glTranslated(0, -6, 5);
        rightFoot.draw();
        glTranslated(0, 0, -15);
        leftFoot.draw();
    }
};