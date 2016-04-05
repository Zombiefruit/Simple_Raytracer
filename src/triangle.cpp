/* triangle.C
 */


#include "headers.h"
#include "triangle.h"
#include "main.h"
#include "texture.h"


// Compute plane/ray intersection, and then the local coordinates to
// see whether the intersection point is inside.

bool Triangle::rayInt( vector rayStart, vector rayDir,
		       vector & intPoint, vector & intNorm, float & intParam )

{
  float param;
  vector point, lc;

  // Compute ray/plane intersection

  float dn = rayDir * faceNormal;

  if (fabs(dn) < 0.0001) 	// *** CHANGED TO ALLOW INTERSECTION FROM BEHIND TRIANGLE ***
    return false;		// ray is parallel to plane

  param = (dist - rayStart*faceNormal) / dn;
  if (param < 0)
    return false;		// plane is behind starting point

  point = rayStart + param * rayDir;

  // Compute barycentric coords

  lc = localCoords( point );

  if (lc.x < 0 || lc.y < 0 || lc.x + lc.y > 1)
    return false;		// outside of triangle

  intParam = param;
  intPoint = point;

  // Find the normal with bump mapping

  if (mat->bumpMap != NULL) {
    intNorm = faceNormal;	// NOT YET IMPLEMENTED!
    return true;
  }

  // No bump mapping: Find the normal with phong shading

  if (verts[0].normal.x == 0 && verts[0].normal.y == 0 && verts[0].normal.z == 0)
    intNorm = faceNormal;
  else {
    vector bc = barycentricCoords( point );
    intNorm = bc.x * verts[0].normal + bc.y * verts[1].normal + bc.z * verts[2].normal;
    intNorm = intNorm.normalize();
  }

  return true;
}


// Determine the texture colour at a point


vector Triangle::textureColour( vector p, float &alpha )

{
  // No texture map?

  if (mat->texture == NULL) {
    alpha = 1;
    return vector(1,1,1);
  }

  // Texture map:

  vector bc = barycentricCoords( p );
  vector texCoords = bc.x * verts[0].texCoords + bc.y * verts[1].texCoords + bc.z * verts[2].texCoords;

  return mat->texture->texel( texCoords.x, texCoords.y, alpha );
}

// Compute the barycentric coordinates of a point which lies on the
// plane of the triangle: p = ua + vb + wc where a,b,c are the first,
// second, and third vertices of the triangle.
//
// See http://research.microsoft.com/~hollasch/cgindex/math/barycentric.html

vector Triangle::barycentricCoords( vector p )

{
  float u = barycentricFactor * (((verts[2].position-verts[1].position) ^ (p - verts[1].position))
				 * faceNormal);

  float v = barycentricFactor * (((verts[0].position-verts[2].position) ^ (p - verts[2].position))
				 * faceNormal);
  float w = 1.0 - u - v;

  return vector( u, v, w );
}


// Compute the local coordinates of a point which lies on the plane of
// the triangle: p = s (b-a) + t (c-a) where a,b,c are the first,
// second, and third vertices of the triangle.  A vector (s,t,0) is
// returned (you can ignore the 0).

vector Triangle::localCoords( vector p )

{
  vector bc = barycentricCoords( p );
  return vector( bc.y, bc.z, 0 );
}


// Output a triangle

void Triangle::output( ostream &stream ) const

{
  stream << "triangle" << endl
	 << "  " << verts[0] << endl
	 << "  " << verts[1] << endl
	 << "  " << verts[2] << endl;
}


// Input a triangle

void Triangle::input( istream &stream )

{
  skipComments( stream );  stream >> verts[0];
  skipComments( stream );  stream >> verts[1];
  skipComments( stream );  stream >> verts[2];

  // Compute the triangle normal and the barycentric factor which is
  // used in computing the barycentric coordinates of a point.

  faceNormal = (verts[1].position - verts[0].position) ^ (verts[2].position - verts[0].position);
  barycentricFactor = 1.0/faceNormal.length();
  faceNormal = barycentricFactor * faceNormal;
  dist   = verts[0].position * faceNormal;
}


// Render with openGL

void Triangle::renderGL()

{
  glNormal3fv( (GLfloat *) & faceNormal.x );

  glBegin( GL_POLYGON );

  if (mat->texture == NULL) {
    glVertex3fv( (GLfloat *) & verts[0].position.x );
    glVertex3fv( (GLfloat *) & verts[1].position.x );
    glVertex3fv( (GLfloat *) & verts[2].position.x );
  } else {
    glTexCoord2f( verts[0].texCoords.x, verts[0].texCoords.y );
    glVertex3fv( (GLfloat *) & verts[0].position.x );
    glTexCoord2f( verts[1].texCoords.x, verts[1].texCoords.y );
    glVertex3fv( (GLfloat *) & verts[1].position.x );
    glTexCoord2f( verts[2].texCoords.x, verts[2].texCoords.y );
    glVertex3fv( (GLfloat *) & verts[2].position.x );
  }

  glEnd();
}

//Vertex* Triangle::getVertex(){
//    return verts;
//}


