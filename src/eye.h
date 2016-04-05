/* eye.h
 */


#ifndef EYE_H
#define EYE_H


#include "vector.h"


class Eye {

 public:

  vector position;
  vector lookAt;
  vector upDir;
  float  fovy;

  Eye() {}

  friend ostream& operator << ( ostream& stream, Eye const& obj );
  friend istream& operator >> ( istream& stream, Eye & obj );
};

#endif
