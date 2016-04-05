/* bbox.C
 */


#include "headers.h"
#include "bbox.h"


/* Intersect a ray with an axis-aligned bounding box.  We assume that
 * the ray starts from *outside* the BB.
 */


bool BBox::rayInt( vector rayStart, vector rayDir,
		   vector & intPoint, vector & intNorm, float & intParam )

{
  return false;
}



/* Render for OpenGL
 */


void BBox::renderGL()

{
  glBegin( GL_LINES );
  glVertex3f(c000.x, c000.y, c000.z); glVertex3f(c000.x, c000.y, c111.z);
  glVertex3f(c000.x, c111.y, c000.z); glVertex3f(c000.x, c111.y, c111.z);
  glVertex3f(c111.x, c000.y, c000.z); glVertex3f(c111.x, c000.y, c111.z);
  glVertex3f(c111.x, c111.y, c000.z); glVertex3f(c111.x, c111.y, c111.z);
  glVertex3f(c000.x, c000.y, c000.z); glVertex3f(c111.x, c000.y, c000.z);
  glVertex3f(c000.x, c000.y, c111.z); glVertex3f(c111.x, c000.y, c111.z);
  glVertex3f(c000.x, c111.y, c000.z); glVertex3f(c111.x, c111.y, c000.z);
  glVertex3f(c000.x, c111.y, c111.z); glVertex3f(c111.x, c111.y, c111.z);
  glVertex3f(c000.x, c000.y, c000.z); glVertex3f(c000.x, c111.y, c000.z);
  glVertex3f(c000.x, c000.y, c111.z); glVertex3f(c000.x, c111.y, c111.z);
  glVertex3f(c111.x, c000.y, c000.z); glVertex3f(c111.x, c111.y, c000.z);
  glVertex3f(c111.x, c000.y, c111.z); glVertex3f(c111.x, c111.y, c111.z);
  glEnd();
}
