// The standard headers included by all files


#ifdef WIN32
  #include <windows.h>

// Uncomment the next two lines if using the CasLab machines
//
//  #undef WINGDIAPI
//  #define WINGDIAPI

  #define M_PI 3.14159
  #define MAXFLOAT 9999999
  #define rint(x) (floor((x)+0.5))
  #pragma warning(disable : 4244 4305 4996)
#endif

#ifdef LINUX
  #include <sys/timeb.h>	// includes ftime (to return current time)
  #include <unistd.h>		// includes usleep (to sleep for some time)
  #include <values.h>
  #ifndef MAXFLOAT
    #define MAXFLOAT 9.9e99
  #endif
#endif

#ifdef __APPLE_CC__
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
  #include <GLUT/glut.h>
#else
  #include <GL/glut.h>
  #include <GL/glu.h>
  #include <GL/gl.h>
#endif

#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

#define randIn01() (rand() / (float) RAND_MAX)   // random number in [0,1]
