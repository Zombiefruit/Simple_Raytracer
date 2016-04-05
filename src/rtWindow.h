/* rtWindow.h
 */


#ifndef RTWINDOW_H
#define RTWINDOW_H

class RTwindow;


#include "arcballWindow.h"
#include "scene.h"


class RTwindow : public arcballWindow {

  Scene *scene;
  bool   viewpointChanged;

 public:

  RTwindow( int x, int y, int width, int height, const char *title, Scene *s )
    : arcballWindow( x, y, width, height, title ) {
    scene = s;
    viewpointChanged = true;
  }

  void draw() {
    viewpointChanged = true;
    scene->renderGL();
  }

  void raytrace() {
    scene->renderRT( viewpointChanged );
    viewpointChanged = false;
  }

  void mouseClick( float objX, float objY, int mouseX, int mouseY ) {

    scene->storedRays.clear();
    scene->storedRayColours.clear();
    scene->storingRays = true;
    scene->pixelColour( mouseX, ydim-1-mouseY );
    scene->storingRays = false;
    glutPostRedisplay();
  }

  void userKeyAction( unsigned char key ) {
    switch (key) {
    case 127:
      scene->storedRays.clear();
      scene->storedRayColours.clear();
      glutPostRedisplay();
      break;
    case 27:
      exit(0);
    case 'e':
      scene->outputEye();
      break;
    case '+':
    case '=':
      scene->maxDepth++;
      viewpointChanged = true;
      break;
    case '-':
    case '_':
      if (scene->maxDepth > 1) {
	scene->maxDepth--;
	viewpointChanged = true;
      }
      break;

    case 'G':			// increase glossiness
      cout << "g = " << scene->incGlossy() << endl;
      viewpointChanged = true;
      break;

    case 'g':			// decrease glossiness
      cout << "g = " << scene->decGlossy() << endl;
      viewpointChanged = true;
      break;

    case 'N':
      scene->glossyIterations += 2;
      cout << scene->glossyIterations << " glossy sampling rays" << endl;
      viewpointChanged = true;
      break;

    case 'n':
      scene->glossyIterations -= 2;
      if (scene->glossyIterations < 1)
	scene->glossyIterations = 1;
      cout << scene->glossyIterations << " glossy sampling rays" << endl;
      viewpointChanged = true;
      break;
    }
  }
};


#endif
