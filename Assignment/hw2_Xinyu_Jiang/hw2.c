
#include "hw2.h"

int axes=0;       //  Display axes
int help_on = 0;  //  Toggle help menu
int mode=0;       //  Projection mode
int th=200;       //  Azimuth of view angle
int ph=30;        //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=12.5;  //  Size of world


int recent_press = 0;

double room_w = 8.0;
double room_h = 6.0;
double door_w = 1.6;
double door_h = 3.5;

double pillar1_w = 1.0;
double pillar2_w = 0.250;

double ground_w = 16.0;
double ground_h = 9.0;

char* mode_desc[] = {"Orthogonal", "Perspective", "First person"};

//angle of rotation
//initial view
float xpos = 0, ypos = 3, zpos = -9, xrot = 0, yrot = 180;
float xrot_d, yrot_d;






/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   const double len=1.5;  //  Length of axes
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode == 1)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else if (mode == 0)
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   // First person point of view
   // Reference: http://www.swiftless.com/tutorials/opengl/camera.html
   else if (mode == 2)
   {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on the x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
   }
  
   glEnable(GL_POLYGON_OFFSET_FILL);
   glPolygonOffset(1, 1);
   int groundSize = 15;
   glBegin(GL_QUADS);
   glColor3f(0, 1, .1);
   glVertex3d(groundSize, 0, groundSize);
   glVertex3d(-groundSize, 0, groundSize);
   glVertex3d(-groundSize, 0, -groundSize);
   glVertex3d(groundSize, 0, -groundSize);
   glEnd();
   glColor3f(1, 1, 1);

   glPushMatrix();
   groundroad();
   glPopMatrix();

   Solidhouse(8, 0, 8, 0, 1, 0, 1, 0, 0);
   Solidhouse(8, 0, 4, 0, 1, 0, 1, 0, 0);
   Solidhouse(8, 0, 0, 0, 1, 0, 1, 0, 0);
   Solidhouse(8, 0, -4, 0, 1, 0, 1, 0, 0);
   Solidhouse(8, 0, -8, 0, 1, 0, 1, 0, 0);

   for (int i = 0; i < 14; ++i) {
       tree(5, 0, i * 2 - 14, 0, 1, 0, 1, 0, 0);
       tree(0, 0, i * 2 - 14, 0, 1, 0, 1, 0, 0);
   }


   DrawHouse2(-4, 0, 8, 0.7, 0.7, 0.7, 0);
   DrawHouse2(-4, 0, 4, 0.7, 0.7, 0.7, 0);
   DrawHouse2(-4, 0, 0, 0.7, 0.7, 0.7, 0);
   DrawHouse2(-4, 0, -4, 0.7, 0.7, 0.7, 0);
   DrawHouse2(-4, 0, -8, 0.7, 0.7, 0.7, 0);

   DrawHouse2(-8, 0, 8, 1.0, 1.0, 1.0, 0);
   DrawHouse2(-8, 0, 4, 1.0, 1.0, 1.0, 30);
   DrawHouse2(-8, 0, 0, 1.0, 1.0, 1.0, 60);
   DrawHouse2(-8, 0, -4, 1.0, 1.0, 1.0, 90);
   DrawHouse2(-8, 0, -8, 1.0, 1.0, 1.0, 120);

   glPushMatrix();
   glColor3ub(0, 0, 255);
   glTranslatef(1.8, 0.5, 0.);
   glRotatef(90., 0, 1, 0);
   DrawCar();
   glPopMatrix();

   glPushMatrix();
   glColor3ub(255, 0, 0);
   glTranslatef(3, 0.2, 5);
   glRotatef(-90, 0, 1, 0);
   DrawCar();
   glPopMatrix();

  

   glPushMatrix();
   glColor3ub(252, 0, 203);
   glTranslatef(6.5, 1, 5);
   glScalef(0.1, 0.1, 0.1);
   drawRobot();
   glPopMatrix();

   glPushMatrix();
   glColor3ub(252, 0, 203);
   glTranslatef(-6.5, 1, 1);
   glScalef(0.1, 0.1, 0.1);
   drawRobot();
   glPopMatrix();

   //  Draw axes
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
    // Display parameters
   // glWindowPos2i(5,25);
   // Print("Recently Rendered: %s",rendered_objs[recent_press]);
   if(mode <= 1){
    glWindowPos2i(5,5);
    Print("Angle=%d,%d  Dim=%.1f FOV=%d Projection=%s",th,ph,dim,fov,mode_desc[mode]);
   }
   else{
     glWindowPos2i(5,5);
     if(yrot == 0) yrot_d = 0;
     else yrot_d = yrot;

     if(xrot == 0) xrot_d = 0;
     else xrot_d = -xrot;

     Print("Position=%1.f,%1.f,%1.f, Head angle=%1.f,%1.f, Projection=%s",xpos,ypos,zpos,yrot_d,xrot_d,mode_desc[mode]);
   }
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(mode,fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);

   //  Reset all view (on startup)
   else if (ch == '0'){
      th = 200;
      ph = 30;
      dim = 12.5;

      xrot = 0;
      yrot = 180;
      xpos = 0;
      ypos = 3;
      zpos =-9; 
   }

   // Main view
   else if (ch == '.'){
      dim = 5.2;
      th = 180;
      ph = 15; 


      xrot = 0;
      yrot = 180;
      xpos = 0;
      ypos = 3;
      zpos =-9;  
   }
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Switch display mode
   else if (ch == 'm' || ch == 'M'){
      mode = (mode + 1)%3;
   }
    
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;


   // FP view
   else if (ch =='k' || ch=='K')
   {
      xrot += 1;
      if (xrot >360) xrot -= 360;
   }
   else if (ch =='i' || ch=='I')
   {
      xrot -= 1;
      if (xrot < -360) xrot += 360;
   }
   if (ch =='l' || ch=='L')
   {
      yrot += 1;
      if (yrot >360) yrot -= 360;
   }
   else if (ch =='j' || ch=='J')
   {
      yrot -= 1;
      if (yrot < -360) yrot += 360;
   }

   // FP movement
   else if (ch =='w' || ch =='W')
   {
      float xrotrad, yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f);
      xpos += (sin(yrotrad)) ;
      zpos -= (cos(yrotrad)) ;
      ypos -= (sin(xrotrad)) ;
   }

   else if (ch =='s' || ch =='S')
   {
      float xrotrad, yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f);
      xpos -= (sin(yrotrad));
      zpos += (cos(yrotrad)) ;
      ypos += (sin(xrotrad));
   }

   else if (ch =='d' || ch =='D')
   {
      float yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xpos += (cos(yrotrad)) * 0.2;
      zpos += (sin(yrotrad)) * 0.2;
   }

   else if (ch=='a' || ch =='A')
   {
      float yrotrad;
      yrotrad = (yrot / 180 * 3.141592654f);
      xpos -= (cos(yrotrad)) * 0.2;
      zpos -= (sin(yrotrad)) * 0.2;
   }
   //  Reproject
   Project(mode,fov,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(mode,fov,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("hw2_Xinyu_Jiang");
   //  Set callbacks
   glutDisplayFunc(display);
   glutIdleFunc (display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
