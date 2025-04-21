/*

	Easy GL2D

	Relminator 2010
	Richard Eric M. Lope BSN RN

	http://rel.phatcode.net


*/


/*!
 \mainpage Easy GL2D Documentation



 \section api Library API
 - \ref gl2d.h "Reference"

 \section intro Official Site
 - <a href="http://rel.phatcode.net">Genso's Junkyard</a>

 \section download Download
 - <a href="http://rel.phatcode.net/junk.php?id=117">Easy GL2D</a>

 \section games Example Games
 - <a href="http://rel.phatcode.net/index.php?action=contents&item=Bubble_Fight_EX_DS">Bubble Fight EX</a>
 - <a href="http://rel.phatcode.net/index.php?action=contents&item=Space-Impakto-DS">Space Impakto DS</a>

 \section tools Misc. Tools
 - <a href="http://rel.phatcode.net/junk.php?id=106">Rel's Texture Packer</a>

 \section external_links Useful links
 - <a href="http://www.devkitpro.org/">devkitPro</a>
 - <a href="http://www.freebasic.net">Freebasic</a>

*/




/*! \file gl2d.h
	\brief A very small and simple PC/MAC/DS rendering lib using the 3d core to render 2D stuff.
*/

#ifndef GL2D_H_INCLUDED
#define GL2D_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../glfw-2.7.9/include/GL/glfw.h"



#define ARGB_A(u) (((u) >> 24) & 0x000000FF)
#define ARGB_R(u) (((u) >> 16) & 0x000000FF)
#define ARGB_G(u) (((u) >> 8)  & 0x000000FF)
#define ARGB_B(u) (((u) >> 0)  & 0x000000FF)
#define RGBA( r, g, b, a ) ((a) << 24 | (r) << 16 | (g) << 8 | (b) )

/*! \brief Macro to use for all the color arguments of Easy GL2D primitives
\param r Red channnel of the 32 bit color (0-255).
\param g Green channnel of the 32 bit color (0-255).
\param b Blue channnel of the 32 bit color (0-255).
\param a Alpha channnel of the 32 bit color (0-255).
*/
#define GL2D_RGBA( r, g, b, a ) RGBA( b, g, r, a)

#ifndef true
    #define true 1
    #define false 0
#endif

/******************************************************************************

                          ENUMS and STRUCTURES

******************************************************************************/

/*! \brief Enums selecting flipping mode.
 *
 *	These enums are bits for flipping the sprites. <Br>
 *	You can <b>"|"</b> (or) GL_FLIP_V and GL_FLIP_H to flip
 *	both ways. <Br><Br>
 *  <ul>
 *	<li> Related functions:
 * 		<ol>
 *	 	<li>glSprite()
 * 		<li>glSpriteScale()
 *	 	<li>glSpriteRotate()
 * 		<li>glSpriteScaleXY()
 *	 	<li>glSpriteRotateScale()
 * 		<li>glSpriteRotateScaleXY()
 *	 	<li>glSpriteOnQuad()
 * 		</ol>
 * 	</ul>
 */

typedef enum GL2D_FLIP_MODE
{

    GL2D_FLIP_NONE 	= 1 << 0,
    GL2D_FLIP_V 	= 1 << 1,
    GL2D_FLIP_H 	= 1 << 2

} GL2D_FLIP_MODE;


/*! \brief Enums selecting Blending/Blitting mode.
 *
 */

typedef enum GL2D_BLEND_MODE
{

    GL2D_TRANS = 0,   	/*!< Transparent blit */
	GL2D_SOLID,			/*!< Solid blit */
	GL2D_BLENDED,		/*!< Alpha Blended blit */
	GL2D_GLOW,			/*!< Additive Blended blit */
	GL2D_ALPHA,			/*!< Alpha Transparent blit */
	GL2D_BLACK			/*!< Black color blit */


} GL2D_BLEND_MODE;

/*! \brief Struct for our GL-Based Images<BR>
This is our struct to hold our image
	attributes. You don't need to worry about this
	if you use the texture packer. */

/*! \brief Struct for out GL-Based Images.
 *
 *	This is our struct to hold our image attributes. <Br>
 *	You don't need to worry about this if you use the texture packer. <Br><Br>
 *  <ul>
 *	<li> Related functions:
 * 		<ol>
 *	 	<li>glSprite()
 * 		<li>glSpriteScale()
 *	 	<li>glSpriteRotate()
 * 		<li>glSpriteScaleXY()
 *	 	<li>glSpriteRotateScale()
 * 		<li>glSpriteRotateScaleXY()
 *	 	<li>glSpriteOnQuad()
 * 		</ol>
 * 	</ul>
 */

typedef struct glImage
{

    int		width;				/*!< Width of the sprite */
    int 	height;				/*!< Height of the sprite */
    float	u_off;				/*!< Horizontal texture offset of the sprite */
    float	v_off;				/*!< Vertical texture offset of the sprite */
    float	u_width;			/*!< Horizontal texture offset width of the sprite */
    float	v_height;			/*!< Vertical texture offset height of the sprite */

    GLuint	textureID;			/*!< OpenGL generated texture ID of the sprite */

} glImage;


#ifdef __cplusplus
extern "C"
{
#endif

/*! \brief Sets up OpenGL for 2d rendering. <Br>
	Call this before drawing any of GL2D's drawing or sprite functions.
\param width width of the window.
\param height height of the window.
 */
void glBegin2D( const int width, const int height );


/*! \brief Issue this after drawing 2d so that we don't mess the matrix stack. <Br>
	The compliment of glBegin2D().
 */
void glEnd2D();

/*! \brief Initializes GL in 2D mode
\param width width of the window.
\param height height of the window.
\param mode either GLFW_FULLSCREEN or GLFW_WINDOWED
*/
void glScreen2D( const int width, const int height, const int mode );

/*! \brief Initializes GL in 2D mode with more control
\param width width of the window.
\param height height of the window.
\param mode either GLFW_FULLSCREEN or GLFW_WINDOWED
\param depthbits depth buffer usually 32.
\param stencilbits stencil buffer 8 would suffice for most purposes.
*/
void glScreen2DEx( const int width, const int height, const int mode,
				   const int depthbits, const int stencilbits );

/*! \brief Cleans up Easy GL2D. Call this at program end.
	External texture management is up for the user to clean up.*/
void glClose();

/*! \brief Sets the default blending/blitting mode
\param mode enums for blending see example files.
*/
void glBlendMode( const GL2D_BLEND_MODE mode );

/*! \brief Sets texture environment color
	Used to draw sprites in a single fill color
	Very useful for flash/hit animations
	(1 - (texture image color)) * (glColor color) + (texture image color) * (texture environment color)
	ie. Pure White Sprites
\param gl2dcolor color.
\param gl2dcolor_env environment color.
\param flag true == blendmode; false(0) == modulate.
*/
void glEnableSpriteStencil( const GLuint gl2dcolor, const GLuint gl2dcolor_env, int flag );

/*! Enables or disables AA depending on the switch
param flag true == enable; false(0) == disable.
*/
void glEnableAntialias( int flag );

/*! \brief Clears the GL2D screen buffer*/
void glClearScreen();

/*! \brief Draws a glowing line
\param x1,y1 Start point of the line.
\param y2,y2 End point of the line.
\param width Thickness of the line.
\param color GL2D_RGBA color.
*/
void glLineGlow( const int x1, const int y1,
                 const int x2, const int y2,
                 const int width, const GLuint color );

/*! \brief Draws a Pixel
\param x X position of the pixel.
\param y Y position of the pixel.
\param color GL2D_RGBA color.
*/
void glPutPixel( int x, int y, const GLuint color );

/*! \brief Draws a Line
\param x1,y1 Start point of the line.
\param y2,y2 End point of the line.
\param color GL2D_RGBA color.
*/
void glLine( int x1, int y1, int x2, int y2, const GLuint color );

/*! \brief Draws a Line in a gradient color
\param x1,y1 Start point of the line.
\param y2,y2 End point of the line.
\param color1 Start point GL2D_RGBA color .
\param color2 End point GL2D_RGBA color .
*/
void glLineGradient( int x1, int y1, int x2, int y2,
                     const GLuint color1, const GLuint color2 );

/*! \brief Draws a Box
\param x1,y1 Top-Left coordinate of the box.
\param x2,y2 Bottom-Right coordinate of the box.
\param color GL2D_RGBA color.
*/
void glBox( int x1, int y1, int x2, int y2, const GLuint color );

/*! \brief Draws a Box filled with a single color
\param x1,y1 Top-Left coordinate of the box.
\param x2,y2 Bottom-Right coordinate of the box.
\param color GL2D_RGBA color.
*/
void glBoxFilled( int x1, int y1, int x2, int y2, const GLuint color );

/*! \brief Draws a Box filled with a gradient color
\param x1,y1 Top-Left coordinate of the box.
\param x2,y2 Bottom-Right coordinate of the box.
\param color1 GL2D_RGBA color of the Top-Left corner.
\param color2 GL2D_RGBA color of the Bottom-Left corner.
\param color3 GL2D_RGBA color of the Bottom-Right corner.
\param color4 GL2D_RGBA color of the Top-Right corner.
*/
void glBoxFilledGradient( int x1, int y1, int x2, int y2,
                          const GLuint color1, const GLuint color2,
                          const GLuint color3, const GLuint color4 );

/*! \brief Draws a Triangle
\param x1,y1 Vertex 1 of the triangle.
\param x2,y2 Vertex 2 of the triangle.
\param x3,y3 Vertex 3 of the triangle.
\param color GL2D_RGBA color of the triangle.
*/
void glTriangle( int x1, int y1, int x2, int y2, int x3, int y3, const GLuint color );

/*! \brief Draws a Triangle filled with a single color
\param x1,y1 Vertex 1 of the triangle.
\param x2,y2 Vertex 2 of the triangle.
\param x3,y3 Vertex 3 of the triangle.
\param color GL2D_RGBA color of the triangle.
*/
void glTriangleFilled( int x1, int y1, int x2, int y2, int x3, int y3, const GLuint color );

/*! \brief Draws a Triangle filled with a gradient color
\param x1,y1 Vertex 1 of the triangle.
\param x2,y2 Vertex 2 of the triangle.
\param x3,y3 Vertex 3 of the triangle.
\param color1 GL2D_RGBA color of the vertex 1.
\param color2 GL2D_RGBA color of the vertex 2.
\param color3 GL2D_RGBA color of the vertex 3.
*/
void glTriangleFilledGradient( int x1, int y1, int x2, int y2, int x3, int y3,
                               const GLuint color1, const GLuint color2, const GLuint color3 );

/*! \brief Draws a hollow Ellipse
\param x,y Center of the ellipse.
\param a Semi-major axis.
\param b Semi-minor.
\param degrees Angle(in degrees).
\param color GL2D_RGBA color of the ellipse.
*/
void glEllipse( int x, int y, int a, int b, int degrees, const GLuint color );

/*! \brief Draws a filled Ellipse
\param x,y Center of the ellipse.
\param a Semi-major axis.
\param b Semi-minor.
\param degrees Angle(in degrees).
\param color GL2D_RGBA color of the ellipse.
*/
void glEllipseFilled( int x, int y, int a, int b, int degrees, const GLuint color );

/******************************************************************************
******************************************************************************/

/*! \brief Draws a Sprite
\param x X position of the sprite.
\param y Y position of the sprite.
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSprite( const int x, const int y, const int flipmode, const glImage *spr );

/*! \brief Draws a Scaled Sprite
\param x X position of the sprite.
\param y Y position of the sprite.
\param scale scale value (1.0f is normal).
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSpriteScale( const int x, const int y, const float scale, const int flipmode, const glImage *spr );

/*! \brief Draws an Axis Exclusive Scaled Sprite
\param x X position of the sprite.
\param y Y position of the sprite.
\param scaleX X-Axis scale value (1.0f is normal).
\param scaleY Y-Axis scale value (1.0f is normal).
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSpriteScaleXY( const int x, const int y, const float scaleX, const float scaleY, const int flipmode, const glImage *spr );

/*! \brief Draws a Center Rotated Sprite
\param x X position of the sprite center.
\param y Y position of the sprite center.
\param angle Angle(in degrees) to rotate the sprite.
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSpriteRotate( const int x, const int y, const int angle, const int flipmode, const glImage *spr );


/*! \brief Draws a Center Rotated Scaled Sprite
\param x X position of the sprite center.
\param y Y position of the sprite center.
\param angle Angle(in degrees) to rotate the sprite.
\param scale scale value (1.0f is normal).
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSpriteRotateScale( const int x, const int y, const int angle, const float scale, const int flipmode, const glImage *spr );


/*! \brief Draws a Center Rotated Axis-Exclusive Scaled Sprite
\param x X position of the sprite center.
\param y Y position of the sprite center.
\param angle Angle(in degrees) to rotate the sprite.
\param scaleX X-Axis scale value (1.0f is normal).
\param scaleY Y-Axis scale value (1.0f is normal).
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSpriteRotateScaleXY( const int x, const int y, const int angle, const float scaleX, const float scaleY, const int flipmode, const glImage *spr );


/*! \brief Draws a Stretched Sprite across a quad <Br>
	Useful for "Shrearing Effects".
\param x1,y1 First corner of the sprite.
\param x2,y2 Second corner of the sprite.
\param x3,y3 Third corner of the sprite.
\param x4,y4 Fourth corner of the sprite.
\param uoff,voff texture offsets.
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSpriteOnQuad( int x1, int y1,
					 int x2, int y2,
					 int x3, int y3,
					 int x4, int y4,
					 float uoff, float voff,
					 int flipmode, const glImage *spr );


/*! \brief Draws a Stretched Sprite across a quad with clipped textures<Br>
	I needed this for my ikaruga laser implementation.
\param x1,y1 First corner of the sprite.
\param x2,y2 Second corner of the sprite.
\param x3,y3 Third corner of the sprite.
\param x4,y4 Fourth corner of the sprite.
\param luclip,lvclip left horizo/vertical ntaltexture offsets.
\param ruclip,rvclip right horizo/vertical ntaltexture offsets.
\param flipmode mode for flipping (see GL2D_FLIP_MODE enum).
\param spr pointer to a glImage.
*/
void glSpriteOnQuadClipped( int x1, int y1,
							int x2, int y2,
							int x3, int y3,
							int x4, int y4,
							float luclip, float lvclip,
							float ruclip, float rvclip,
							int flipmode, const glImage *spr );


/*! \brief Draws a clean horizontally stretched Sprite<Br>
	Useful for lasers and huds.
\param x,y Location of the sprite.
\param length length to stretch in pixels.
\param spr pointer to a glImage.
*/
void glSpriteStretchHorizontal( int x, int y, int length, const glImage *spr );


/*! \brief Draws a clean vertically stretched Sprite<Br>
	Useful for lasers and huds.
\param x,y Location of the sprite.
\param height height to stretch in pixels.
\param spr pointer to a glImage.
*/
void glSpriteStretchVertical( int x, int y, int height, const glImage *spr );

/*! \brief Draws a clean horizontally and vertically stretched Sprite<Br>
	Useful for lasers, huds and dialog boxes.
\param x,y Location of the sprite.
\param length length to stretch in pixels.
\param height height to stretch in pixels.
\param spr pointer to a glImage.
*/
void glSpriteStretchHV( int x, int y, int length, int height, const glImage *spr );

/*! \brief Prints a rudimentary text for feedback/debugging purposes<Br>
	Not to be used in actual application/games as it is extremely sloooow.
	Rasterfont from the GLRedbook.
\param x,y Location of the sprite.
\param text text to print.
\param color GL2D_RGBA color of the Top-Right corner.
*/
void glPrint( int x, int y, const char *text, const GLuint color );

/*! \brief Initializes our spriteset with Texture Packer generated UV coordinates <Br>
	Very safe and easy to use..
\param filename filename of the TGA file to load ie. "ships.tga".
\param sprite Pointer to an array of glImage.
\param width The horizontal size of the texture
\param height The vertical size of the texture
\param numframes number of frames in a spriteset (auto-generated by Texture Packer).
\param texcoords Texture Packer auto-generated array of UV coords.
\param filtermode GL_NEAREST or GL_LINEAR.
*/
GLuint glLoadSpriteSet( const char *filename,
                        glImage *sprite,
                        const int width,
                        const int height,
                        const int numframes,
                        const unsigned int *texcoords,
                        const  GLuint filtermode );


/*! \brief Initializes our Tileset (like glInitSpriteset()) but without the use of Texture Packer auto-generated files. <Br>
	Can only be used when tiles in a tilset are of the same dimensions.
\param filename filename of the TGA file to load ie. "ships.tga".
\param sprite Pointer to an array of glImage.
\param tile_wid Width of each tile in the texture.
\param tile_hei Height of each tile in the texture.
\param bmp_wid Width of of the texture or tileset.
\param bmp_hei height of of the texture or tileset.
\param filtermode GL_NEAREST or GL_LINEAR.
*/
GLuint  glLoadTileSet( const char *filename,
					   glImage *sprite,
					   const int tile_wid,
					   const int tile_hei,
					   const int bmp_wid,
					   const int bmp_hei,
					   const  GLuint filtermode	);

/*! \brief Loads a single power of 2 image.
\param filename filename of the TGA file to load ie. "ship.tga".
\param sprite Pointer to an array of glImage.
\param width Width of of the texture.
\param height height of of the texture.
\param filtermode GL_NEAREST or GL_LINEAR.
*/
GLuint glLoadSprite( const char *filename,
                     glImage *sprite,
                     const int width,
                     const int height,
                     const  GLuint filtermode );


/*! \brief "Gets" a tile from a loaded spriteset.
\param SpriteDest Destination pointer to an array of glImage.
\param SpriteSource Source pointer to an array of glImage.
\param x1,y1 Top-Left coordinate of the image to "get".
\param x2,y2 Bottom-Right coordinate of the image to "get".
*/
void glGet( glImage *SpriteDest, const glImage *SpriteSource, int x1, int y1, int x2, int y2 );

#ifdef __cplusplus
}
#endif


#endif // GL2D_H_INCLUDED
