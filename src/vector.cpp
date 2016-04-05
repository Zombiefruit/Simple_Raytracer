/* vector.C
 *
 * See vector.h for a class description.  This file contains the
 * implementation.
 */


#include "headers.h"
#ifndef WIN32
  #include <values.h>
#endif

#include "vector.h"
#include <iostream>
using namespace std;


vector operator * ( float k, vector const& p )

{
  vector q;

  q.x = p.x * k;
  q.y = p.y * k;
  q.z = p.z * k;

  return q;
}


float distToEdge( vector v, vector head, vector tail )

{
  vector toV = v - tail;
  vector me = head - tail;
  float  dot = (toV * me) / (me * me);
  vector perp = toV - dot * me;

  if (dot < 0.15 || dot > 0.85)
    return MAXFLOAT;
  else
    return perp * perp;
}


vector vector::perp1()

{
  vector result(0,0,0);

  if (x == 0)
    if (y == 0 || z == 0)
      result.x = 1;     /* v = (0 0 z) or (0 y 0) */
    else {
      result.y = -z; /* v = (0 y z) */
      result.z = y;
    }
  else if (y == 0)
    if (z == 0)
      result.z = 1;     /* v = (x 0 0) */
    else {
      result.x = -z; /* v = (x 0 z) */
      result.z = x;
    }
  else {
    result.x = -y;   /* v = (x y z) or (x y 0) */
    result.y = x;
  }

  float lenRecip = 1.0 / sqrt( result.x*result.x + result.y*result.y + result.z*result.z );
  result.x *= lenRecip;
  result.y *= lenRecip;
  result.z *= lenRecip;

  return result;
}


vector vector::perp2()

{
  vector result(0,0,0);

  if (x == 0)
    if (y == 0)
      result.y = 1;
    else if (z == 0)
      result.z = 1;
    else
      result.x = 1;
  else
    if (y == 0)
      result.y = 1;
    else if (z == 0)
      result.z = 1;
    else {
      result.x = x * z;
      result.y = y * z;
      result.z = - x*x - y*y;

      float lenRecip = 1.0 / sqrt( result.x*result.x + result.y*result.y + result.z*result.z );
      result.x *= lenRecip;
      result.y *= lenRecip;
      result.z *= lenRecip;
    }

  return result;
}


// I/O operators

ostream& operator << ( ostream& stream, vector const& p )

{
  stream << p.x << " " << p.y << " " << p.z;
  return stream;
}

istream& operator >> ( istream& stream, vector & p )

{
  stream >> p.x >> p.y >> p.z;
  return stream;
}


