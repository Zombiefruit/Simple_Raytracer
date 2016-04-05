/* material.h
 */


#ifndef MATERIAL_H
#define MATERIAL_H


#include "vector.h"
#include "texture.h"


class Material {

 public:

  char *  name;                 // material name
  char *  texName;              // texture filename (for debugging)
  char *  bumpMapName;          // bump map filename (for debugging)

  vector  ka;                   // ambient reflectivity
  vector  kd;                   // diffuse reflectivity
  vector  ks;                   // specular reflectivity
  float   n;                    // shininess
  float   g;                    // glossiness in range 1 (a mirror) to 0 (a very rough surface)
  vector  Ie;                   // emitted light
  float   alpha;                // opacity in [0,1] with 1 = opaque
  Texture *texture;             // texture map (= NULL if none)
  Texture *bumpMap;             // bump map (= NULL if none)

  Material() {}

  void setMaterialForOpenGL();

  friend ostream& operator << ( ostream& stream, Material const& m );
  friend istream& operator >> ( istream& stream, Material & m );
  
};


#endif
