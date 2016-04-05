/* object.h
 */

#ifndef OBJECT_H
#define OBJECT_H


#include "vector.h"
#include "material.h"


class Object {

 public:

  Material *mat;

  Object() {}

  virtual bool rayInt( vector rayStart, vector rayDir,
		       vector & intPoint, vector & intNorm, float & intParam ) = 0;

  virtual vector textureColour( vector p, float &alpha ) {
    alpha = 1;
    return vector(1,1,1);
  }

  virtual void renderGL() {}

  virtual void input( istream &istream ) {}
  virtual void output( ostream &ostream ) const {}

  friend ostream& operator << ( ostream& stream, Object const& o );
  friend istream& operator >> ( istream& stream, Object & o );
};

#endif
