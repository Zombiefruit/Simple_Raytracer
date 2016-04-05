/* volume.h
 */


#ifndef VOLUME_H
#define VOLUME_H


#include "object.h"
#include "bbox.h"


typedef unsigned short int Voxel;


class Volume : public Object {

  char *name;

  Voxel **volume;

  vector dim;			// dimensions of the dataset
  vector scale;			// scale factor
  vector centre;		// centre of dataset
  BBox   bbox;			// bounding box

  GLubyte *readVolume( char *filename, int width, int height, int depth );

 public:

  Volume() {}

  bool rayInt( vector rayStart, vector rayDir,
	       vector & intPoint, vector & intNorm, float & intParam );

  void input( istream &stream );
  void output( ostream &stream ) const;
  void renderGL();

  float sample( float x, float y, float z ); /* in [0,1]x[0,1]x[0,1] */
  float sample( int x, int y, int z );       /* in [0,xdim-1]x[0,ydim-1]x[0,zdim-1] */
};


#endif
