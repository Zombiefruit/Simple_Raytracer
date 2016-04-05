/* volume.C
 */


#include "headers.h"

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include "volume.h"
#include "main.h"

using namespace std;


/* Determine whether a ray intersects the volume.  
 */

bool Volume::rayInt( vector rayStart, vector rayDir,
	     vector & intPoint, vector & intNorm, float & intParam )

{
  return false;
}


// Output a volume

void Volume::output( ostream &stream ) const

{
  stream << "volume" << endl
	 << "  " << name << endl
	 << "  " << dim << endl
	 << "  " << scale << endl
	 << "  " << centre << endl;
}


// Input a volume

void Volume::input( istream &stream )

{
  char volName[1000];

  skipComments( stream );  stream >> volName;
  skipComments( stream );  stream >> dim;
  skipComments( stream );  stream >> scale;
  skipComments( stream );  stream >> centre;

  name = strdup( volName );

  // Store bounding box

  vector size( (dim.x-1) * scale.x, (dim.y-1) * scale.y, (dim.z-1) * scale.z );

  bbox = BBox( centre - 0.5*size, centre + 0.5*size );

  // Get the volume data

  volume = (Voxel **) malloc( sizeof(Voxel *) * (int)dim.z );

  for (int k=0; k<dim.z; k++) {

    char filename[1000];
    sprintf( filename, "%s.%d", volName, k+1 );

    ifstream slice( filename );
    if (!slice) {
      cerr << "Couldn't open slice '" << filename
	   << "' of volume '" << volName << "'." << endl;
      exit(-1);
    }

    volume[k] = (Voxel *) malloc( sizeof(Voxel) * (int)(dim.x*dim.y) );
    slice.read( (char *) volume[k], (int) (dim.x*dim.y*sizeof(Voxel)) );
  }
}


/* look up the sample at (x,y,z).  The sample is normalized
 * to the range [0,1].
 */


float Volume::sample( float x, float y, float z )

{
  if (x < 0) x = 0;
  if (x > 1) x = 1;
  if (y < 0) y = 0;
  if (y > 1) y = 1;
  if (z < 0) z = 0;
  if (z > 1) z = 1;
    
  int xi = (int) floor(x * (dim.x-1) + 0.5);
  int yi = (int) floor(y * (dim.y-1) + 0.5);
  int zi = (int) floor(z * (dim.z-1) + 0.5);

  Voxel val;

  val = volume[zi][xi+yi*(int)dim.x];

  return (float) val / 65535.0;	// we assume "Voxel" = 2 bytes
}


float Volume::sample( int x, int y, int z )

{
  if (x < 0) x = 0;
  if (x > dim.x-1) x = (int) dim.x-1;
  if (y < 0) y = 0;
  if (y > dim.y-1) y = (int) dim.y-1;
  if (z < 0) z = 0;
  if (z > dim.z-1) z = (int) dim.z-1;
    
  Voxel val;

  val = volume[z][x+y*(int)dim.x];

  return (float) val / 65535.0;	// we assume "Voxel" = 2 bytes
}


/* Render just a cube for OpenGL
 */


void Volume::renderGL()

{
  glDisable( GL_LIGHTING );

  glBegin( GL_POINTS );
  for (int i=0; i<dim.x; i+=(int)dim.x/10)
    for (int j=0; j<dim.y; j+=(int)dim.y/10)
      for (int k=0; k<dim.z; k+=(int)dim.z/10) {
	float density = sample(i,j,k);
	glColor3f( density, density, density );
	glVertex3f( bbox.c000.x+i*scale.x, bbox.c000.y+j*scale.y, bbox.c000.z+k*scale.z );
      }
  glEnd();

  glEnable( GL_LIGHTING );

  bbox.renderGL();
}
