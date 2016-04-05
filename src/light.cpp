/* light.C
 */


#include "headers.h"

#include "light.h"
#include "main.h"


// Output a light

ostream& operator << ( ostream& stream, Light const& obj )

{
  stream << "light" << endl
	 << "  " << obj.position << endl
	 << "  " << obj.colour << endl;
  return stream;
}


// Input a light

istream& operator >> ( istream& stream, Light & obj )

{
  skipComments( stream );  stream >> obj.position;
  skipComments( stream );  stream >> obj.colour;
  return stream;
}

