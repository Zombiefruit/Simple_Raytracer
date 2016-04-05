/* window.h
 */


#include "headers.h"


#ifndef WINDOW_H
#define WINDOW_H

#include "vector.h"


void GLUTdisplay();
void GLUTreshape( int x, int y );
void GLUTmouseAction( int button, int state, int x, int y );
void GLUTmouseMotion( int x, int y );
void GLUTkeyAction( unsigned char c, int x, int y );


typedef enum { PERSPECTIVE, ORTHOGRAPHIC } ProjectionType;


class window {

  void registerWindow( int windowId );

public:

  int windowId;
  int xdim, ydim;

  ProjectionType projection;

  vector eye, lookat, updir;	// model transformation

  float  fovy;			// perspective projection
  float  zNear;
  float  zFar;

  float orthoScale;		// orthographic projection
  float left, bottom;		//   right = left + orthoScale
  float nnear, ffar;		//   top   = bottom + orthoScale * ydim/xdim

  virtual void display() = 0;
  virtual void mouseAction( int button, int state, int x, int y ) {};
  virtual void mouseMotion( int x, int y ) {};
  virtual void keyAction( unsigned char key, int x, int y ) {};
  virtual void userReshape( int w, int h ) {};

  virtual void reshape( int width, int height ) {

    userReshape(width,height);

    xdim = width;
    ydim = height;
    glViewport( 0, 0, width, height );
    glutPostRedisplay();
  }

  void setupProjection() {

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if (projection == PERSPECTIVE)
      gluPerspective( fovy, (float) xdim / (float) ydim, zNear, zFar );
    else 
      glOrtho( left, left + orthoScale,
	       bottom, bottom + orthoScale * (float) ydim / (float) xdim,
	       nnear, ffar );

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( eye.x, eye.y, eye.z,
	       lookat.x, lookat.y, lookat.z,
	       updir.x, updir.y, updir.z );
  }

  void setupModelview() {
    gluLookAt( eye.x, eye.y, eye.z,
	       lookat.x, lookat.y, lookat.z,
	       updir.x, updir.y, updir.z );
  }

  window( int x, int y, int width, int height, const char *title ) {

    xdim = width;
    ydim = height;

    eye = vector(0,0,50);	// model view
    lookat = vector(0,0,0);
    updir = vector(0,1,0);

    projection = PERSPECTIVE; // perspective params
    fovy = 30;
    zNear = 1;
    zFar = 1000;

    orthoScale = 1;		// orthographic params
    left = 0; bottom = 0; 
    nnear = 0; ffar = 1000;

    glutInitWindowPosition( x, y );
    glutInitWindowSize( xdim, ydim );
    windowId = glutCreateWindow( title );
    registerWindow( windowId );
    glutSetWindow( windowId );
    glutDisplayFunc( GLUTdisplay );
    glutReshapeFunc( GLUTreshape );
    glutMouseFunc( GLUTmouseAction );
    glutMotionFunc( GLUTmouseMotion );
    glutKeyboardFunc( GLUTkeyAction );
  }

  void redraw() {
    glutSetWindow( windowId );
    glutPostRedisplay();
  }
};

#define MAX_NUM_WINDOWS 20

extern window * windows[ MAX_NUM_WINDOWS ];

#endif
