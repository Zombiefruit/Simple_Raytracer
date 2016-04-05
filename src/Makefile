# uncomment the -lpng12 and -DHAVEPNG if you have the png12 libraries
# installed on Linux.
#
# If running under Windows, comment out the LIBS line like this:  #LIBS = ...

PROG = rt
EXECDIR = ../exec

OBJS = main.o window.o arcballWindow.o vector.o font.o \
       scene.o sphere.o triangle.o light.o eye.o object.o \
       material.o texture.o vertex.o volume.o bbox.o

INCS = 
LIBS = -lGL -lGLU -lglut # -lpng12

CXXFLAGS = -O2 $(INCS) # -DHAVEPNG
CXX      = g++

$(PROG):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(PROG) $(OBJS) $(LIBS)
	cp $(PROG) $(EXECDIR)

.C.o:
	$(CXX) $(CXXFLAGS) -c $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *~ core $(PROG) Makefile.bak

depend:	
	makedepend -Y *.[hC] >&2 /dev/null

# DO NOT DELETE

arcballWindow.o: headers.h vector.h window.h
bbox.o: vector.h
eye.o: vector.h
light.o: vector.h
main.o: seq.h scene.h vector.h object.h material.h texture.h headers.h
main.o: light.h eye.h rtWindow.h arcballWindow.h window.h
material.o: vector.h texture.h headers.h seq.h
object.o: vector.h material.h texture.h headers.h seq.h
rtWindow.o: arcballWindow.h headers.h vector.h window.h scene.h seq.h
rtWindow.o: object.h material.h texture.h light.h eye.h
scene.o: seq.h vector.h object.h material.h texture.h headers.h light.h eye.h
sphere.o: object.h vector.h material.h texture.h headers.h seq.h
texture.o: headers.h seq.h vector.h
triangle.o: object.h vector.h material.h texture.h headers.h seq.h vertex.h
vertex.o: vector.h
volume.o: object.h vector.h material.h texture.h headers.h seq.h bbox.h
window.o: headers.h vector.h
