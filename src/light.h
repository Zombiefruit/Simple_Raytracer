/* light.h
 */


#ifndef LIGHT_H
#define LIGHT_H


#include "vector.h"


class Light {

 public:

  vector position;
  vector colour;

  Light() {}

  friend ostream& operator << ( ostream& stream, Light const& obj );
  friend istream& operator >> ( istream& stream, Light & obj );
};

#endif
