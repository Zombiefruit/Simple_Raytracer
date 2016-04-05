/* vertex.h
 */


#ifndef VERTEX_H
#define VERTEX_H


#include <iostream>
#include "vector.h"


class Vertex {
 public:
  vector position;		// vertex position
  vector normal;		// vertex normal
  vector texCoords;		// vertex texture coordinates

  friend ostream& operator << ( ostream& stream, Vertex const& v );
  friend istream& operator >> ( istream& stream, Vertex & v );
};


#endif
