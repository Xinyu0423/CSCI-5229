#ifndef hw2
#define hw2


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
#define PI 3.1415927

#ifdef __cplusplus
extern "C" {
#endif

void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
void Project(int mode, double fov,double asp,double dim);
void ErrCheck(const char* where);
int  LoadOBJ(const char* file);

void cube(double x,double y,double z,
         double dx,double dy,double dz,
         double th, double r, double g, double b);

void draw_cylinder(float radius,float height,
                   float R, float G,float B);

void draw_cone(double height, double radius, double r, double g, double b);
void Vertex(double th, double ph);
void drawRobot(void);
void DrawCar();
void groundroad();
void DrawHouse2(float x, float y, float z, float s1, float s2, float s3, float a1);
void tree(double x, double y, double z,
    double dx, double dy, double dz,
    double ux, double uy, double uz);
void Solidhouse(double x, double y, double z,
    double dx, double dy, double dz,
    double ux, double uy, double uz);

#ifdef __cplusplus
}
#endif

#endif
