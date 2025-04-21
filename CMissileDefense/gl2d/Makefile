libgl2d.a: gl2d.o
	ar rcs libgl2d.a gl2d.o

gl2d.o: gl2d.c gl2d.h
	gcc -c gl2d.c -I. -L. -I ../../glfw/include -L ../../glfw/lib

clean:
	del gl2d.o libgl2d.a
