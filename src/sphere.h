/* sphere.h
 */


#ifndef SPHERE_H
#define SPHERE_H


#include "object.h"


class Sphere : public Object {

  vector centre;
  float radius;

 public:

  Sphere() {}

  bool rayInt( vector rayStart, vector rayDir,
	       vector & intPoint, vector & intNorm, float & intParam );

  void input( istream &stream );
  void output( ostream &stream ) const;
  vector polarToCart( float phi, float theta );
  vector textureColour( vector p, float &alpha );
  void renderGL();
};

#endif
