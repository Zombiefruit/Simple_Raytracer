/* scene.h
 */


#ifndef SCENE_H
#define SCENE_H


class RTwindow;


#include <iostream>
#include "seq.h"
#include "vector.h"
#include "object.h"
#include "light.h"
#include "eye.h"


class Scene {

  RTwindow *    win;		// rendering window

  Eye *         eye;		// viewpoint
  seq<Light *>  lights;		// all lights
  seq<Object *> objects;	// all objects

  vector        Ia;		// ambient illumination

  vector  llCorner, up, right;	// window parameters

  seq<vector> storedPoints;

  bool sceneLoaded;

 public:

  bool storingRays;
  seq<vector> storedRays;	// each pair of points is a ray
  seq<vector> storedRayColours;

  seq<Texture*> textures;	// all textures
  seq<Material*> materials;	// all materials
  int maxDepth;			// ray tracing depth
  int glossyIterations;		// number of rays to send for glossy reflections
  bool useTextureTransparency;

  Scene() {
    Ia = vector(0.1,0.1,0.1);
    maxDepth = 3;
    glossyIterations = 3;
    useTextureTransparency = true;
    storingRays = false;
	sceneLoaded = false;
  }

  void setWindow( RTwindow * w )
    { win = w; }

  void renderRT( bool restart );
  void renderGL();
  void read( istream &in );
  void write( ostream &out );
  vector pixelColour( int x, int y );
  vector raytrace( vector &rayStart, vector &rayDir, int depth, int thisObjIndex );
  vector calcIout( vector N, vector L, vector E, vector R,
		   vector Kd, vector Ks, float ns, vector In );
  bool findFirstObjectInt( vector rayStart, vector rayDir, int thisObjIndex,
			   vector &P, vector &N, float &param, int &objIndex );
  void outputEye()
    { cout << *eye << endl; }

  float incGlossy() {
    float ret = 0;
    for (int i=0; i<objects.size(); i++) {
      float &g = objects[i]->mat->g;
      if (g > 0) {
	g = 1 - (1 - g) * 0.75;
	if (g < 0)
	  g = 0;
	ret = g;
      }
    }
    return ret;
  }

  float decGlossy() {
    float ret = 0;
    for (int i=0; i<objects.size(); i++) {
      float &g = objects[i]->mat->g;
      if (g > 0) {
	g = 1 - (1 - g) / 0.75;
	if (g < 0)
	  g = 0;
	ret = g;
      }
    }
    return ret;
  }
};


#endif
