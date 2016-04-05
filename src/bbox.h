/* bbox.h
 *
 * An axis-aligned bounding box
 */


#include "vector.h"


class BBox {

 public:

  vector c000;			// one corner
  vector c111;			// opposite corner

  BBox() {}

  BBox( vector c0, vector c1 ) {
    c000 = c0;
    c111 = c1;
  }

  bool rayInt( vector rayStart, vector rayDir,
	       vector & intPoint, vector & intNorm, float & intParam );

  void renderGL();
};
