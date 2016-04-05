/* material.C
 */


#include "headers.h"

#include "material.h"
#include "main.h"


void Material::setMaterialForOpenGL()

{
  GLfloat p[4];

  p[3] = alpha;
  p[0] = ka.x; p[1] = ka.y; p[2] = ka.z; glMaterialfv( GL_FRONT, GL_AMBIENT,  &p[0] );
  p[0] = kd.x; p[1] = kd.y; p[2] = kd.z; glMaterialfv( GL_FRONT, GL_DIFFUSE,  &p[0] );
  p[0] = ks.x; p[1] = ks.y; p[2] = ks.z; glMaterialfv( GL_FRONT, GL_SPECULAR,  &p[0] );
  p[0] = Ie.x; p[1] = Ie.y; p[2] = Ie.z; glMaterialfv( GL_FRONT, GL_EMISSION,  &p[0] );
  glMaterialfv( GL_FRONT, GL_SHININESS, &n );

  if (texture != NULL) {
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, texture->texID() );
    if (scene->useTextureTransparency)
      if (texture->hasAlpha) {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      } else
	glDisable(GL_BLEND);
  } else if (scene->useTextureTransparency) {
    glDisable( GL_TEXTURE_2D );
    glDisable(GL_BLEND);
  }

  if (alpha < 1) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }
}


ostream& operator << ( ostream& stream, Material const& mat )

{
  stream << "material" << endl
	 << "  " << mat.name << endl
	 << "  " << mat.ka << endl
	 << "  " << mat.kd << endl
	 << "  " << mat.ks << endl
	 << "  " << mat.n << endl
	 << "  " << mat.g << endl
	 << "  " << mat.Ie << endl
	 << "  " << mat.alpha << endl
	 << "  " << mat.texName << endl;
  
  return stream;
}

istream& operator >> ( istream& stream, Material & mat )

{
  char matName[1000], texName[1000], bumpName[1000];

  skipComments( stream );  stream >> matName;
  skipComments( stream );  stream >> mat.ka;
  skipComments( stream );  stream >> mat.kd;
  skipComments( stream );  stream >> mat.ks;
  skipComments( stream );  stream >> mat.n;
  skipComments( stream );  stream >> mat.g;
  skipComments( stream );  stream >> mat.Ie;
  skipComments( stream );  stream >> mat.alpha;
  skipComments( stream );  stream >> texName;
  skipComments( stream );  stream >> bumpName;

  mat.name = strdup( matName );

  // Store the TEXTURE with the material

  if (texName[0] == '-' && texName[1] == '\0') {

    mat.texture = NULL;		// no texture
    mat.texName = strdup( "-" );

  } else {

    // Search for this texture

    int i;
    for (i=0; i<scene->textures.size(); i++)
      if (strcmp( texName, scene->textures[i]->name ) == 0)
	break;

    // Create the texture if it's not already loaded
    
    if (i == scene->textures.size())
      scene->textures.add( new Texture( texName ) );

    mat.texture = scene->textures[ i ];
    mat.texName = texName;
  }

  // Store the BUMP MAP with the material

  if (bumpName[0] == '-' && bumpName[1] == '\0') {

    mat.bumpMap = NULL;		// no bump map
    mat.bumpMapName = strdup( "-" );

  } else {

    // Search for this texture (bump maps and textures are
    // stored in the same way ... it's only their use that
    // differs).

    int i;
    for (i=0; i<scene->textures.size(); i++)
      if (strcmp( texName, scene->textures[i]->name ) == 0)
	break;

    // Create the texture if it's not already loaded
    
    if (i == scene->textures.size())
      scene->textures.add( new Texture( bumpName ) );

    mat.bumpMap = scene->textures[ i ];
    mat.bumpMapName = bumpName;
  }

  return stream;
}
