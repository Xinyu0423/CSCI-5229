
#include "hw2.h"

void Vertex(double th, double ph)
{
    glColor3f(.25, .5, .25);
    glVertex3d(Sin(th) * Cos(ph), Sin(ph), Cos(th) * Cos(ph));
}

void sphere1(double x, double y, double z, double r)
{
    const int d = 5;
    int th, ph;

    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(x, y, z);
    glScaled(r, r, r);

    //  South pole cap
    glBegin(GL_TRIANGLE_FAN);
    Vertex(0, -90);
    for (th = 0; th <= 360; th += d)
    {
        Vertex(th, d - 90);
    }
    glEnd();

    //  Latitude bands
    for (ph = d - 90; ph <= 90 - 2 * d; ph += d)
    {
        glBegin(GL_QUAD_STRIP);
        for (th = 0; th <= 360; th += d)
        {
            Vertex(th, ph);
            Vertex(th, ph + d);
        }
        glEnd();
    }

    //  North pole cap
    glBegin(GL_TRIANGLE_FAN);
    Vertex(0, 90);
    for (th = 0; th <= 360; th += d)
    {
        Vertex(th, 90 - d);
    }
    glEnd();

    //  Undo transformations
    glPopMatrix();
}

void draw_cone(double height, double radius, double r, double g, double b)
{
   int k = 0;
    //sides
    glColor3f(r,g,b);
    glBegin(GL_TRIANGLES);
    for (k=0;k<=360;k+=5){
      
      glVertex3f(0,0,height);
      glVertex3f(Cos(k),Sin(k),0);
      glVertex3f(Cos(k+5),Sin(k+5),0);
    }
    glEnd();
}


void drawBall(double R, double x, double y, double z) {
    glPushMatrix();
    glTranslated(x, y, z);
    glutSolidSphere(R, 20, 20);

    glPopMatrix();
}


void drawHalfBall(double R, double x, double y, double z) {
    glPushMatrix();
    glTranslated(x, y, z);
    GLdouble eqn[4] = { 0.0, 1.0, 0.0, 0.0 };
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glEnable(GL_CLIP_PLANE0);
    glutSolidSphere(R, 20, 20);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}


void drawSkewed(double l, double w, double h, double x, double y, double z) {
    glPushMatrix();
    glScaled(l, w, h);
    glTranslated(x, y, z);

    glutSolidCube(1);
 
    glPopMatrix();
}

void drawRobot(void) {
    glPushMatrix();
    drawBall(2, 0, 1, 0);
    drawSkewed(5, 4.4, 4, 0, -0.75, 0);
    drawHalfBall(1, 3.5, -2.1, 0);
    drawHalfBall(1, -3.5, -2.1, 0);
    drawSkewed(1, 3, 1, 3.5, -1.3, 0);
    drawSkewed(1, 3, 1, -3.5, -1.3, 0);
    drawBall(1, 3.5, -6.4, 0);
    drawBall(1, -3.5, -6.4, 0);
    drawSkewed(1.2, 3, 2, 1, -2.4, 0);
    drawSkewed(1.2, 3, 2, -1, -2.4, 0);
    drawSkewed(1.5, 1, 3, 0.9, -9.2, 0);
    drawSkewed(1.5, 1, 3, -0.9, -9.2, 0);
    glPopMatrix();

}

void groundroad()                   //GroundRoad
{
    glPushMatrix();
    glColor3ub(128, 128, 128);
    glBegin(GL_QUADS);
    glVertex3d(4.5, 0.01, 15);
    glVertex3d(0.5, 0.01, 15);
    glVertex3d(0.5, 0.01, -15);
    glVertex3d(4.5, 0.01, -15);
    glEnd();

    glColor3ub(255, 255, 255);
    glBegin(GL_QUADS);
    glVertex3d(2.6, 0.02, 15);
    glVertex3d(2.2, 0.02, 15);
    glVertex3d(2.2, 0.02, -15);
    glVertex3d(2.6, 0.02, -15);
    glEnd();
    glPopMatrix();

}

void DrawCar() {
    glPushMatrix();
    glPushMatrix();                   // body
    glScalef(2, .5, 1);
    glutSolidCube(.5);
    glPopMatrix();
    glTranslatef(0, 0, .25);
    glPushMatrix();
    glTranslatef(-.4, -.2, 0);
    glutSolidTorus(.05, .1, 8, 8);       // wheel
    glTranslatef(.8, 0, 0);
    glutSolidTorus(.05, .1, 8, 8);       // wheel
    glPopMatrix();
    glTranslatef(0, 0, -.5);
    glPushMatrix();
    glTranslatef(-.4, -.2, 0);
    glutSolidTorus(.05, .1, 8, 8);       // wheel
    glTranslatef(.8, 0, 0);
    glutSolidTorus(.05, .1, 8, 8);       // wheel
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
}


void DrawHouse2(float x, float y, float z, float s1, float s2, float s3, float a1) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glTranslatef(0, 1, 0);
    glRotatef(a1, 0, 1, 0);
    glScalef(s1, s2, s3);

    glColor3ub(34, 139, 34);
    glutSolidCube(2);                 // building

    glColor3ub(134, 130, 134);
    glTranslatef(0, 1, 0);
    glPushMatrix();                   // roof
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1.5, 1, 16, 8);
    glPopMatrix();

    glColor3ub(84, 39, 234);
    glTranslatef(.75, .5, -.75);
    glPushMatrix();                   // chimney
    glScalef(1, 3, 1);
    glutSolidCube(.25);
    glPopMatrix();
    glPopMatrix();
}


void tree(double x, double y, double z,
    double dx, double dy, double dz,
    double ux, double uy, double uz)
{
    // Dimensions used to size house
    const double wid = .2;
    //  Unit vector in direction of flght
    double D0 = sqrt(dx * dx + dy * dy + dz * dz);
    double X0 = dx / D0;
    double Y0 = dy / D0;
    double Z0 = dz / D0;
    //  Unit vector in "up" direction
    double D1 = sqrt(ux * ux + uy * uy + uz * uz);
    double X1 = ux / D1;
    double Y1 = uy / D1;
    double Z1 = uz / D1;
    //  Cross product gives the third vector
    double X2 = Y0 * Z1 - Y1 * Z0;
    double Y2 = Z0 * X1 - Z1 * X0;
    double Z2 = X0 * Y1 - X1 * Y0;
    //  Rotation matrix
    double mat[16];
    mat[0] = X0;   mat[4] = X1;   mat[8] = X2;   mat[12] = 0;
    mat[1] = Y0;   mat[5] = Y1;   mat[9] = Y2;   mat[13] = 0;
    mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
    mat[3] = 0;   mat[7] = 0;   mat[11] = 0;   mat[15] = 1;

    //  Save current transforms
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x, y, z);
    glMultMatrixd(mat);
    // draw a square tree
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.35f, 0.05f);
    //main tree

    glVertex3d(0, wid, 0);
    glVertex3d(1.2, wid, 0);
    glVertex3d(1.2, -wid, 0);
    glVertex3d(0, -wid, 0);

    glVertex3d(0, .2, 0);
    glVertex3d(1.2, .2, 0);
    glVertex3d(1.2, .2, -.4);
    glVertex3d(0, .2, -.4);

    glVertex3d(0, -.2, 0);
    glVertex3d(1.2, -.2, 0);
    glVertex3d(1.2, -.2, -.4);
    glVertex3d(0, -.2, -.4);


    glVertex3d(0, wid, -.4);
    glVertex3d(1.2, wid, -.4);
    glVertex3d(1.2, -wid, -.4);
    glVertex3d(0, -wid, -.4);

    //branch

    glVertex3d(.7, .2, 0);
    glVertex3d(1, .4, 0);
    glVertex3d(1, .5, 0);
    glVertex3d(.6, .2, 0);


    glVertex3d(.6, .2, 0);
    glVertex3d(1, .5, 0);
    glVertex3d(1, .5, -.3);
    glVertex3d(.6, .2, -.3);

    glVertex3d(.7, .2, 0);
    glVertex3d(1, .4, 0);
    glVertex3d(1, .4, -.3);
    glVertex3d(.7, .2, -.3);

    glVertex3d(.7, .2, -.3);
    glVertex3d(1, .4, -.3);
    glVertex3d(1, .5, -.3);
    glVertex3d(.6, .2, -.3);

    glEnd();
    sphere1(1.5, 0, -.2, .55);
    sphere1(1.1, .45, -.15, .25);
    // undo transformations
    glPopMatrix();
}

void Solidhouse(double x, double y, double z,
    double dx, double dy, double dz,
    double ux, double uy, double uz)
{
    // Dimensions used to size house
    const double fence = -.7;
    const double wid = 0.5;
    const double nose = +2.0;
    const double cone = .98;
    const double chimtop = 2;
    const double chimbot = .8;
    //  Unit vector in direction of flght
    double D0 = sqrt(dx * dx + dy * dy + dz * dz);
    double X0 = dx / D0;
    double Y0 = dy / D0;
    double Z0 = dz / D0;
    //  Unit vector in "up" direction
    double D1 = sqrt(ux * ux + uy * uy + uz * uz);
    double X1 = ux / D1;
    double Y1 = uy / D1;
    double Z1 = uz / D1;
    //  Cross product gives the third vector
    double X2 = Y0 * Z1 - Y1 * Z0;
    double Y2 = Z0 * X1 - Z1 * X0;
    double Z2 = X0 * Y1 - X1 * Y0;
    //  Rotation matrix
    double mat[16];
    mat[0] = X0;   mat[4] = X1;   mat[8] = X2;   mat[12] = 0;
    mat[1] = Y0;   mat[5] = Y1;   mat[9] = Y2;   mat[13] = 0;
    mat[2] = Z0;   mat[6] = Z1;   mat[10] = Z2;   mat[14] = 0;
    mat[3] = 0;   mat[7] = 0;   mat[11] = 0;   mat[15] = 1;

    //  Save current transforms
    glPushMatrix();
    //  Offset, scale and rotate
    glTranslated(x, y, z);
    glMultMatrixd(mat);
    //  Nose (4 sided)
    glColor3f(0, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone, wid, wid);
    glVertex3d(cone, -wid, wid);

    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone, wid, -wid);
    glVertex3d(cone, -wid, -wid);

    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone, wid, wid);
    glVertex3d(cone, wid, -wid);

    glVertex3d(nose, 0.0, 0.0);
    glVertex3d(cone, -wid, wid);
    glVertex3d(cone, -wid, -wid);
    glEnd();
    glBegin(GL_QUADS);
    //back exterior wall
    glColor3f(1, 0, 0);
    glVertex3d(cone, -wid, wid);
    glVertex3d(0, -wid, wid);
    glVertex3d(0, wid, wid);
    glVertex3d(cone, wid, wid);
    //right exterior wall
    glColor3f(0, 0, 1);
    glVertex3d(cone, wid, -wid);
    glVertex3d(0, wid, -wid);
    glVertex3d(0, wid, wid);
    glVertex3d(cone, wid, wid);
    //front exterior wall
    glColor3f(1, 0, 0);
    glVertex3d(cone, -wid, -wid);
    glVertex3d(0, -wid, -wid);
    glVertex3d(0, wid, -wid);
    glVertex3d(cone, wid, -wid);
    //left exterior wall
    glColor3f(0, 0, 1);
    glVertex3d(cone, -wid, -wid);
    glVertex3d(0, -wid, -wid);
    glVertex3d(0, -wid, wid);
    glVertex3d(cone, -wid, wid);
    //floor
    glColor3f(0, .5, .5);
    glVertex3d(0, .5, 0.5);
    glVertex3d(0, .5, -0.5);
    glVertex3d(0, -.5, -0.5);
    glVertex3d(0, -.5, 0.5);
    //door
    glColor3f(.5, .35, .5);
    glVertex3d(0, 0.2, -.501);
    glVertex3d(0, -0.2, -.501);
    glVertex3d(.5, -0.2, -.501);
    glVertex3d(.5, 0.2, -.501);
    // window left
    //window right
    //chimney
    glColor3f(1, 1, 1);
    glVertex3d(chimbot, -.48, 0);
    glVertex3d(chimtop, -.48, 0);
    glVertex3d(chimtop, -0.2, 0);
    glVertex3d(chimbot, -0.2, 0);
    //chimney2
    glColor3f(1, 1, 1);
    glVertex3d(chimbot, -.48, .2);
    glVertex3d(chimtop, -.48, .2);
    glVertex3d(chimtop, -0.2, .2);
    glVertex3d(chimbot, -0.2, .2);
    //chimney3
    glColor3f(1, 1, 1);
    glVertex3d(chimbot, -0.48, 0);
    glVertex3d(chimbot, -0.48, 0.2);
    glVertex3d(chimtop, -0.48, .2);
    glVertex3d(chimtop, -0.48, 0);
    //chimney4
    glColor3f(1, 1, 1);
    glVertex3d(chimbot, -0.2, 0);
    glVertex3d(chimbot, -0.2, 0.2);
    glVertex3d(chimtop, -0.2, 0.2);
    glVertex3d(chimtop, -0.2, 0);
    //chimney topper
    glColor3f(1, 1, 0);
    glVertex3d(chimtop, -0.51, 0.21);
    glVertex3d(2.1, -0.51, 0.21);
    glVertex3d(2.1, -0.51, -0.01);
    glVertex3d(chimtop, -0.51, -0.01);
    //chimney topper2
    glColor3f(1, 1, 0);
    glVertex3d(chimtop, -0.51, 0.21);
    glVertex3d(chimtop, -0.19, 0.21);
    glVertex3d(2.1, -0.19, 0.21);
    glVertex3d(2.1, -0.51, 0.21);
    //chimney topper3
    glColor3f(1, 1, 0);
    glVertex3d(chimtop, -0.19, 0.21);
    glVertex3d(chimtop, -0.19, -0.01);
    glVertex3d(2.1, -0.19, -0.01);
    glVertex3d(2.1, -0.19, 0.21);
    //chimney topper4
    glColor3f(1, 1, 0);
    glVertex3d(chimtop, -0.19, -.01);
    glVertex3d(2.1, -0.19, -0.01);
    glVertex3d(2.1, -0.51, -0.01);
    glVertex3d(chimtop, -0.51, -0.01);
    //chimney topper base
    glColor3f(1, 1, 0);
    glVertex3d(chimtop, -0.51, 0.21);
    glVertex3d(chimtop, -0.51, -0.01);
    glVertex3d(chimtop, -0.19, -0.01);
    glVertex3d(chimtop, -0.19, 0.21);
    //chimney topper top
    glColor3f(1, 1, 0);
    glVertex3d(2.1, -0.51, 0.21);
    glVertex3d(2.1, -0.51, -0.01);
    glVertex3d(2.1, -0.19, -0.01);
    glVertex3d(2.1, -0.19, 0.21);
    //picket
    glColor3f(1, 1, 1);
    glVertex3d(.3, -0.5, fence);
    glVertex3d(0, -0.5, fence);
    glVertex3d(0, -0.4, fence);
    glVertex3d(.3, -0.4, fence);

    glColor3f(1, 1, 1);
    glVertex3d(.3, -0.3, fence);
    glVertex3d(0, -0.3, fence);
    glVertex3d(0, -0.2, fence);
    glVertex3d(.3, -0.2, fence);

    glColor3f(1, 1, 1);
    glVertex3d(.3, -.1, fence);
    glVertex3d(0, -.1, fence);
    glVertex3d(0, 0, fence);
    glVertex3d(.3, 0, fence);

    glColor3f(1, 1, 1);
    glVertex3d(.3, .1, fence);
    glVertex3d(0, .1, fence);
    glVertex3d(0, .2, fence);
    glVertex3d(.3, .2, fence);

    glColor3f(1, 1, 1);
    glVertex3d(.3, .3, fence);
    glVertex3d(0, .3, fence);
    glVertex3d(0, .4, fence);
    glVertex3d(.3, .4, fence);

    glColor3f(1, 1, 1);
    glVertex3d(.3, .5, fence);
    glVertex3d(0, .5, fence);
    glVertex3d(0, .6, fence);
    glVertex3d(.3, .6, fence);


    glColor3f(1, 1, 1);
    glVertex3d(.24, -wid, fence);
    glVertex3d(.2, -wid, fence);
    glVertex3d(.2, wid, fence);
    glVertex3d(.24, wid, fence);

    glColor3f(1, 1, 1);
    glVertex3d(.11, -wid, fence);
    glVertex3d(0.07, -wid, fence);
    glVertex3d(0.07, wid, fence);
    glVertex3d(.11, wid, fence);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 1);
    glVertex3d(.3, .5, fence);
    glVertex3d(.35, .55, fence);
    glVertex3d(.3, .6, fence);

    glVertex3d(.3, .3, fence);
    glVertex3d(.35, .35, fence);
    glVertex3d(.3, .4, fence);

    glVertex3d(.3, .1, fence);
    glVertex3d(.35, .15, fence);
    glVertex3d(.3, .2, fence);

    glVertex3d(.3, -.1, fence);
    glVertex3d(.35, -.05, fence);
    glVertex3d(.3, 0, fence);

    glVertex3d(.3, -.5, fence);
    glVertex3d(.35, -.45, fence);
    glVertex3d(.3, -.4, fence);

    glVertex3d(.3, -.3, fence);
    glVertex3d(.35, -.25, fence);
    glVertex3d(.3, -.2, fence);
    glEnd();
    // undo transformations
    glPopMatrix();
}
