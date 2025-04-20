#ifndef GL2D_H
#define GL2D_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <GL/glfw.h>



#define ARGB_A(u) (((u) >> 24) & 0x000000FF)
#define ARGB_R(u) (((u) >> 16) & 0x000000FF)
#define ARGB_G(u) (((u) >> 8)  & 0x000000FF)
#define ARGB_B(u) (((u) >> 0)  & 0x000000FF)
#define RGBA( r, g, b, a ) ((a) << 24 | (r) << 16 | (g) << 8 | (b) )
#define GL2D_RGBA( r, g, b, a ) RGBA( b, g, r, a)



typedef enum GL2D_FLIP_MODE {
    GL2D_FLIP_NONE 	= 1 << 0,
    GL2D_FLIP_V 	= 1 << 1,
    GL2D_FLIP_H 	= 1 << 2
} GL2D_FLIP_MODE;



typedef enum GL2D_BLEND_MODE {
  GL2D_TRANS = 0,
	GL2D_SOLID,
	GL2D_BLENDED,
	GL2D_GLOW,
	GL2D_ALPHA,
	GL2D_BLACK
} GL2D_BLEND_MODE;



typedef struct glImage {

    int		width;
    int 	height;
    float	u_off;
    float	v_off;
    float	u_width;
    float	v_height;

    GLuint	textureID;

} glImage;



void glScreenInit(const int width, const int height);

void glBlendMode(const GL2D_BLEND_MODE mode);

void glClearScreen();

void glPutPixel( int x1, int y1, const GLuint color );

void glLine( int x1, int y1, int x2, int y2, const GLuint color );

void glBox(int x1, int y1, int x2, int y2, const GLuint color);

void glBoxFilled(int x1, int y1, int x2, int y2, const GLuint color);

void glTriangle( int x1, int y1, int x2, int y2, int x3, int y3, const GLuint color );

void glTriangleFilled( int x1, int y1, int x2, int y2, int x3, int y3, const GLuint color );

void glEllipse(int x, int y, int a, int b, int degrees, const GLuint color);

void glEllipseFilled(int x, int y, int a, int b, int degrees, const GLuint color);



void glSprite(const int x, const int y, const int flipmode, const glImage *spr);

void glSpriteScale(const int x, const int y, const float scale, const int flipmode, const glImage *spr);

void glSpriteRotate(const int x, const int y, const int angle, const int flipmode, const glImage *spr);

void glSpriteRotateScale(const int x, const int y, const int angle, const float scale, const int flipmode, const glImage *spr);

GLuint glLoadSpriteSet( const char *filename,
                        glImage *sprite,
                        const int width,
                        const int height,
                        const int numframes,
                        const unsigned int *texcoords,
                        const  GLuint filtermode
                      );

GLuint glLoadSprite( const char *filename,
                     glImage *sprite,
                     const int width,
                     const int height,
                     const  GLuint filtermode
                   );



void glPrint( int x, int y, const char *text, const GLuint color );



#endif
