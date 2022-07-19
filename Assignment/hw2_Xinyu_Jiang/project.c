/*
 *  Set projection
 */
#include "hw2.h"

void Project(int mode, double fov,double asp,double dim)
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode == 1)
      gluPerspective(fov,asp,dim/4,20*dim);
   //  Orthogonal transformation
   else if (mode == 0)
      glOrtho(-asp*dim,asp*dim,-dim,+dim,-20,+20);
   else if (mode == 2)
      gluPerspective (fov, asp, 1.0, 1000.0);

   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

