//
//  hw1.c
//
//
//  Created by Xinyu Jiang on 2021/6/5.
//

#include "hw1.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//Global Variables
int th=0;
int ph=0;
int mode=0;
double dim=2;
const char* text[] = {"Use 1, 2, 3 button to change parameter s, b, r or 0 to reset","s=","b=","r="};

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

#define LEN 8192  // Maximum length of text string

void Print(const char* format , ...){
    char    buf[LEN];
    char*   ch=buf;
    va_list args;
    //  Turn the parameters into a character string
    va_start(args,format);
    vsnprintf(buf,LEN,format,args);
    va_end(args);
    //  Display the characters one at a time at the current raster position
    while (*ch)
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void display(){
    //  Clear the image
    glClear(GL_COLOR_BUFFER_BIT);
    //  Reset previous transforms
    glLoadIdentity();
    //  Set view angle
    glRotated(ph,1,0,0);
    glRotated(th,0,1,0);
    glColor3f(1,1,0);
    glPointSize(10);
    
    //from assignment write up
    int i;
    /*  Coordinates  */
    double x = 1;
    double y = 1;
    double z = 1;
    /*  Time step  */
    double dt = 0.001;
    
    printf("%5d %8.3f %8.3f %8.3f\n",0,x,y,z);
    /*
     *  Integrate 50,000 steps (50 time units with dt = 0.001)
     *  Explicit Euler integration
     */
    glBegin(GL_LINE_STRIP);
    for (i=0;i<50000;i++){
        double dx = s*(y-x);
        double dy = x*(r-z)-y;
        double dz = x*y - b*z;
        x += dt*dx;
        y += dt*dy;
        z += dt*dz;
        printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);
        if(i<20000){
            glColor3f(1, 0, 0);
        }else if(i>=20000 && i<50000){
            glColor3f(1, 1, 0);
        }
        glVertex3d(x*0.04, y*0.04, z*0.04);
        
    }
    glEnd();
    
    //  Draw axes in white
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(1,0,0);
    glVertex3d(0,0,0);
    glVertex3d(0,1,0);
    glVertex3d(0,0,0);
    glVertex3d(0,0,1);
    glEnd();
    //  Label axes
    glRasterPos3d(1,0,0);
    Print("X");
    glRasterPos3d(0,1,0);
    Print("Y");
    glRasterPos3d(0,0,1);
    Print("Z");
    
    //  Display parameters
    glWindowPos2i(5,5);
    Print("View Angle=%d,%d  %s",th,ph,text[mode]);
    glWindowPos2i(5, 30);
    Print("Parameters s=%f, b=%f ,r=%f",s,b,r);
    glFlush();
    glutSwapBuffers();
    
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y){
    if (ch == 27)
       exit(0);
    //  Reset view angle
    else if (ch=='0'){
        th = ph = 0;
        s=10;
        b=2.6666;
        r=28;
    }else if(ch=='1'){
        mode=1;
    }else if(ch=='2'){
        mode=2;
    }else if(ch=='3'){
        mode=3;
    }else if(ch=='+'){
        if(mode==1){
            s=s+2;
        }else if(mode==2){
            b=b+2;
        }else if(mode==3){
            r=r+2;
        }
    }else if(ch=='-'){
        if(mode==1){
            s=s-2;
        }else if(mode==2){
            b=b-2;
        }else if(mode==3){
            r=r-2;
        }
    }
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char * argv[]) {
    // insert code here...
    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    //  Request double buffered, true color window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    //  Request 500 x 500 pixel window
    glutInitWindowSize(500,500);
    //  Create the window
    glutCreateWindow("Hw1_Xinyu_Jiang");
#ifdef USEGLEW
    //  Initialize GLEW
    if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
    //  Tell GLUT to call "display" when the scene should be drawn
    glutDisplayFunc(display);
    //  Tell GLUT to call "reshape" when the window is resized
    glutReshapeFunc(reshape);
    //  Tell GLUT to call "special" when an arrow key is pressed
    glutSpecialFunc(special);
    //  Tell GLUT to call "key" when a key is pressed
    glutKeyboardFunc(key);
    //  Pass control to GLUT so it can interact with the user
    glutMainLoop();
    //  Return code

    return 0;
}
