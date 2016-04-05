/* triangle.h
 */


#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "object.h"
#include "vertex.h"


class Triangle : public Object {

  vector faceNormal;		// triangle normal
  float  barycentricFactor;     // factor used in computing local coords
  float  dist;			// distance origin-to-plane of triangle
  Vertex verts[3];
    
 public:
    
//  Vertex verts[3];// three vertices of the triangle -- copied to allow access from scene.cpp
    
  Triangle() {}

  bool rayInt( vector rayStart, vector rayDir,
	       vector & intPoint, vector & intNorm, float & intParam );

  void input( istream &stream );
  void output( ostream &stream ) const;
  void renderGL();
    
  //Vertex* getVertex();

  vector localCoords( vector point );
  vector barycentricCoords( vector point );
  vector textureColour( vector p, float &alpha );
};

#endif
