# Introduction
Our task was to get a simple raytracer working with shadowing (including soft shadows).

# Overview
In raytrace(), we calculate the reflection direction of a ray that has intersected an object, and the recursively call raytrace() in that direction to compute the illumination arriving from the direction of reflection, terminating this recursion after passing the maximum depth value.

Then, using the Phong method of illumination, we calculate the illumination returning to the camera (using material properties grabbed from obj->mat). 

We use shadow rays to calculate shadow values, and also implement soft shadows by averaging the contribution of many rays, sent to randomly generated points on a triangle (which was our occluding object). 

# Images
This image shows relection and shading:
![An image showing reflection and shading](/src/partA.png)

And an image showing soft shadows:
![An image showing soft shadows](/src/partB.png)

# Running the application
THIS APPLICATION WON'T COMPILE RIGHT NOW.

It was working when I submitted it two months ago, but I was coding on a mac at the time. I don't have time to debug it right now, as I have six exams in the next few weeks, but I will fix this after April 19th. The screenshots above are from when the program used to compile.

# Disclaimer
Some code supplied, which was written by Professor James Stewart, at Queen's University (http://research.cs.queensu.ca/~jstewart/).

