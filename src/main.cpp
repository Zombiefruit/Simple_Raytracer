/* A basic raytracer
 *
 * A scene is read from the standard input.  See 'testInput'
 * for the format.
 *
 * You can move the viewpoint with the left mouse button, and
 * zoom with the middle mouse button.  With the mouse in the
 * window, you can press:
 *
 *      e   output the eye position (useful to store in your scene file)
 *      +   increase the ray depth
 *      -   decrease the ray depth
 *
 * Whenever nothing is happening in the window, the program starts
 * raytracing the current scene, and draws that as soon as it's done.
 * You can move the viewpoint again, or press a button, and it'll
 * start raytracing again from the new position.
 */


#include "headers.h"

#include <stdlib.h>
#include <ctype.h>
#include <fstream>
#include "rtWindow.h"
#include "scene.h"
#include "texture.h"
#include "material.h"
#include "seq.h"


Scene *scene;
RTwindow *win;
int lineNum = 1;
char *filename[2] = { NULL, NULL };


// Parse the command-line options

void parseOptions( int argc, char **argv )

{
  int next_arg = 0;
  int next_fn = 0;
  
  while (argc > 1) {
    argv++;
    argc--;
    if (argv[0][0] != '-') {

      if (next_fn >= 2)
        cerr << "Only two filenames allowed on command line" << endl;
      else
        filename[ next_fn++ ] = argv[0];

    } else switch( argv[0][1] ) {

    case 'd':                   // max depth for ray tracing
      argc--; argv++;
      scene->maxDepth = atoi( *argv );
      break;

    case 't':                   // use texture maps?
      scene->useTextureTransparency = !scene->useTextureTransparency;
      break;

    case 'g':                   // number of glossy iterations
      argc--; argv++;
      scene->glossyIterations = atoi( *argv );
      break;

    case 'm':                   // use mipMaps?
      Texture::useMipMaps = !Texture::useMipMaps;
      break;

    default:
      cerr << "Unrecognized option -" << argv[0][1] << ".  Options are:" << endl;
      cerr << "  -d #   set max depth\n" << endl;
      cerr << "  -t     toggle texture transparency\n" << endl;
      break;
    }
  }

  if (next_fn == 0) {
    cerr << "No input filename provided on command line" << endl;
    abort();
  }
}


// Skip past a comment

void skipComments( istream &in )

{
  char c;

  // get next non-space

  do {
    if (!in.get(c))
      return;

    if (c == '\n')
      lineNum++;
  } while (in && isspace(c));
  in.putback(c);

  // Skip past any comments

  while (c == '#') {
    do
      if (!in.get(c))
        return;
    while (in && c != '\n' && c != EOF);
    lineNum++;
    do {
      if (!in.get(c))
        return;
      if (c == '\n')
        lineNum++;
    } while (in && isspace(c));
    in.putback(c);
  }
}


// Main program


void idle()

{
  win->raytrace();
}


int main( int argc, char **argv )

{
  glutInit( &argc, argv );
  glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

  scene = new Scene();
  parseOptions( argc, argv );

  win = new RTwindow( 50, 50, 400, 300, "raytracer", scene );
  scene->setWindow( win );

  ifstream in( filename[0] );
  scene->read( in );

  if (filename[1] != NULL) {
    ofstream out( filename[1] );
    scene->write( out );
  }

  glutIdleFunc( idle );
  glutMainLoop();
  return 0;
}
