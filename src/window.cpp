/* window.C
 */

#include "headers.h"

#include <iostream>
#include <stdlib.h>
using namespace std;

#include "window.h"


window * windows[ MAX_NUM_WINDOWS ];


void window::registerWindow( int windowId )

{
  if (windowId < 0 || windowId >= MAX_NUM_WINDOWS) {
    cerr << "New window has windowId " << windowId
	 << ", which is outside the allowed range 0.." << MAX_NUM_WINDOWS-1 << endl;
    exit(-1);
  }
  windows[ windowId ] = this;
}


void GLUTdisplay() {
  windows[ glutGetWindow() ]->display();
}

void GLUTreshape( int x, int y ) {
  windows[ glutGetWindow() ]->reshape( x, y );
}

void GLUTmouseAction( int button, int state, int x, int y ) {
  windows[ glutGetWindow() ]->mouseAction( button, state, x, y );
}

void GLUTmouseMotion( int x, int y ) {
  windows[ glutGetWindow() ]->mouseMotion( x, y );
}

void GLUTkeyAction( unsigned char c, int x, int y ) {
  windows[ glutGetWindow() ]->keyAction( c, x, y );
}
