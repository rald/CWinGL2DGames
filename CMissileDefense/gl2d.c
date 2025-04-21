/*

	Easy GL2D

	Relminator 2010
	Richard Eric M. Lope BSN RN

	http://rel.phatcode.net


*/


#include "gl2d.h"

// mingw header excluding GL_BGRA in windows
#ifndef GL_BGRA
#define GL_BGRA  0x80E1
#endif

static GLuint gCurrentTexture = 0;
static GLuint gFontOffset = 0;
static GLuint gGlowTexture = 0;
/******************************************************************************

    IMPLEMENTATION

******************************************************************************/


/******************************************************************************

   Private!!!
   Abstracted(to be)  LoadTexture function

******************************************************************************/

int LoadTexture( const char *filename )
{

    if ( !glfwLoadTexture2D( filename, GLFW_BUILD_MIPMAPS_BIT | GLFW_ORIGIN_UL_BIT) )
    {
        glfwTerminate();
        printf( "Error loading %s", filename );
        return false;
    }


    return true;

}



/******************************************************************************

   Public funks

******************************************************************************/

void glBegin2D( const int width, const int height )
{

    gCurrentTexture = 0;
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glEnable( GL_ALPHA_TEST );
    glAlphaFunc( GL_GREATER, 0 );

    glPolygonMode( GL_FRONT, GL_FILL );

	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_TEXTURE_2D );

    glDisable( GL_STENCIL_TEST );
    glDisable( GL_TEXTURE_1D );
    glDisable( GL_LIGHTING );
    glDisable( GL_LOGIC_OP );
    glDisable( GL_DITHER );
    glDisable( GL_FOG );

    glPointSize( 1.0 );
    glLineWidth( 1.0 );

    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
    glHint( GL_LINE_SMOOTH_HINT , GL_NICEST );

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0, width, height, 0, -1, 1 );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
    glTranslatef( 0.375, 0.375, 0.0 );

}

void glEnd2D()
{

    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();

    glBlendMode( GL2D_SOLID );
    glColor4ub(255,255,255,255);

}




/******************************************************************************

    Sets texture environment color

    (1 - (texture image color))*(glColor colour) + (texture image colour)*(texture environment colour)
    I didn't put this as part of the set_blend since we can use this alongside
    blending

******************************************************************************/

void glEnableSpriteStencil( const GLuint gl2dcolor, const GLuint gl2dcolor_env, int flag )
{

	static GLfloat env_color[3];
	if( flag )
	{
		env_color[0] = ARGB_B(gl2dcolor_env)/255.0f;
		env_color[1] = ARGB_G(gl2dcolor_env)/255.0f;
		env_color[2] = ARGB_R(gl2dcolor_env)/255.0f;
		env_color[3] = ARGB_A(gl2dcolor_env)/255.0f;

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
		glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, &env_color[0]);
		glColor4ubv( (GLubyte*)&gl2dcolor );
	}
	else
	{
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	}

}

/******************************************************************************

    Enables or disables AA depending on the switch

******************************************************************************/

void glEnableAntialias( int flag )
{
	if( flag )
	{
		glEnable( GL_POINT_SMOOTH );
        glEnable( GL_LINE_SMOOTH  );
	}
	else
	{
		glDisable( GL_POINT_SMOOTH );
        glDisable( GL_LINE_SMOOTH  );
	}

}

/******************************************************************************


******************************************************************************/
GLuint GetGlowImage()
{

    if ( gGlowTexture == 0 )
	{
        const int IMAGE_WIDTH = 32, IMAGE_HEIGHT = 32;

		const unsigned int image_array[] = {
	    0x00000007, 0x00000004, 0x00000020, 0x00000020, 0x00000080, 0x00000000,
	    0x00000000, 0x00000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF010101, 0xFF020202,
	    0xFF020202, 0xFF030303, 0xFF030303, 0xFF030303, 0xFF020202, 0xFF020202,
	    0xFF010101, 0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF020202, 0xFF030303,
	    0xFF040404, 0xFF050505, 0xFF060606, 0xFF060606, 0xFF060606, 0xFF060606,
	    0xFF060606, 0xFF050505, 0xFF040404, 0xFF030303, 0xFF020202, 0xFF010101,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF020202, 0xFF040404,
	    0xFF050505, 0xFF070707, 0xFF080808, 0xFF090909, 0xFF0A0A0A, 0xFF0B0B0B,
	    0xFF0B0B0B, 0xFF0B0B0B, 0xFF0A0A0A, 0xFF090909, 0xFF080808, 0xFF070707,
	    0xFF050505, 0xFF040404, 0xFF020202, 0xFF010101, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF030303,
	    0xFF050505, 0xFF070707, 0xFF090909, 0xFF0B0B0B, 0xFF0C0C0C, 0xFF0E0E0E,
	    0xFF0F0F0F, 0xFF0F0F0F, 0xFF101010, 0xFF0F0F0F, 0xFF0F0F0F, 0xFF0E0E0E,
	    0xFF0C0C0C, 0xFF0B0B0B, 0xFF090909, 0xFF070707, 0xFF050505, 0xFF030303,
	    0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101,
	    0xFF030303, 0xFF060606, 0xFF080808, 0xFF0B0B0B, 0xFF0D0D0D, 0xFF0F0F0F,
	    0xFF111111, 0xFF131313, 0xFF141414, 0xFF151515, 0xFF151515, 0xFF151515,
	    0xFF141414, 0xFF131313, 0xFF111111, 0xFF0F0F0F, 0xFF0D0D0D, 0xFF0B0B0B,
	    0xFF080808, 0xFF060606, 0xFF030303, 0xFF010101, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF010101, 0xFF030303, 0xFF060606, 0xFF090909, 0xFF0C0C0C, 0xFF0E0E0E,
	    0xFF121212, 0xFF141414, 0xFF161616, 0xFF181818, 0xFF191919, 0xFF1A1A1A,
	    0xFF1B1B1B, 0xFF1A1A1A, 0xFF191919, 0xFF181818, 0xFF161616, 0xFF141414,
	    0xFF121212, 0xFF0E0E0E, 0xFF0C0C0C, 0xFF090909, 0xFF060606, 0xFF030303,
	    0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF010101, 0xFF030303, 0xFF060606, 0xFF090909, 0xFF0C0C0C,
	    0xFF0F0F0F, 0xFF131313, 0xFF161616, 0xFF191919, 0xFF1B1B1B, 0xFF1E1E1E,
	    0xFF1F1F1F, 0xFF202020, 0xFF212121, 0xFF202020, 0xFF1F1F1F, 0xFF1E1E1E,
	    0xFF1B1B1B, 0xFF191919, 0xFF161616, 0xFF131313, 0xFF0F0F0F, 0xFF0C0C0C,
	    0xFF090909, 0xFF060606, 0xFF030303, 0xFF010101, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF020202, 0xFF050505, 0xFF080808,
	    0xFF0C0C0C, 0xFF0F0F0F, 0xFF131313, 0xFF171717, 0xFF1B1B1B, 0xFF1E1E1E,
	    0xFF212121, 0xFF232323, 0xFF252525, 0xFF262626, 0xFF272727, 0xFF262626,
	    0xFF252525, 0xFF232323, 0xFF212121, 0xFF1E1E1E, 0xFF1B1B1B, 0xFF171717,
	    0xFF131313, 0xFF0F0F0F, 0xFF0C0C0C, 0xFF080808, 0xFF050505, 0xFF020202,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF040404,
	    0xFF070707, 0xFF0B0B0B, 0xFF0E0E0E, 0xFF131313, 0xFF171717, 0xFF1B1B1B,
	    0xFF1F1F1F, 0xFF232323, 0xFF262626, 0xFF292929, 0xFF2B2B2B, 0xFF2C2C2C,
	    0xFF2C2C2C, 0xFF2C2C2C, 0xFF2B2B2B, 0xFF292929, 0xFF262626, 0xFF232323,
	    0xFF1F1F1F, 0xFF1B1B1B, 0xFF171717, 0xFF131313, 0xFF0E0E0E, 0xFF0B0B0B,
	    0xFF070707, 0xFF040404, 0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF020202, 0xFF050505, 0xFF090909, 0xFF0D0D0D, 0xFF121212, 0xFF161616,
	    0xFF1B1B1B, 0xFF1F1F1F, 0xFF242424, 0xFF282828, 0xFF2B2B2B, 0xFF2E2E2E,
	    0xFF313131, 0xFF323232, 0xFF323232, 0xFF323232, 0xFF313131, 0xFF2E2E2E,
	    0xFF2B2B2B, 0xFF282828, 0xFF242424, 0xFF1F1F1F, 0xFF1B1B1B, 0xFF161616,
	    0xFF121212, 0xFF0D0D0D, 0xFF090909, 0xFF050505, 0xFF020202, 0xFF000000,
	    0xFF000000, 0xFF010101, 0xFF030303, 0xFF070707, 0xFF0B0B0B, 0xFF0F0F0F,
	    0xFF141414, 0xFF191919, 0xFF1E1E1E, 0xFF232323, 0xFF282828, 0xFF2C2C2C,
	    0xFF303030, 0xFF333333, 0xFF363636, 0xFF383838, 0xFF383838, 0xFF383838,
	    0xFF363636, 0xFF333333, 0xFF303030, 0xFF2C2C2C, 0xFF282828, 0xFF232323,
	    0xFF1E1E1E, 0xFF191919, 0xFF141414, 0xFF0F0F0F, 0xFF0B0B0B, 0xFF070707,
	    0xFF030303, 0xFF010101, 0xFF000000, 0xFF010101, 0xFF040404, 0xFF080808,
	    0xFF0C0C0C, 0xFF111111, 0xFF161616, 0xFF1B1B1B, 0xFF212121, 0xFF262626,
	    0xFF2B2B2B, 0xFF303030, 0xFF343434, 0xFF383838, 0xFF3B3B3B, 0xFF3D3D3D,
	    0xFF3D3D3D, 0xFF3D3D3D, 0xFF3B3B3B, 0xFF383838, 0xFF343434, 0xFF303030,
	    0xFF2B2B2B, 0xFF262626, 0xFF212121, 0xFF1B1B1B, 0xFF161616, 0xFF111111,
	    0xFF0C0C0C, 0xFF080808, 0xFF040404, 0xFF010101, 0xFF000000, 0xFF020202,
	    0xFF050505, 0xFF090909, 0xFF0E0E0E, 0xFF131313, 0xFF181818, 0xFF1E1E1E,
	    0xFF232323, 0xFF292929, 0xFF2E2E2E, 0xFF333333, 0xFF383838, 0xFF3C3C3C,
	    0xFF3F3F3F, 0xFF424242, 0xFF424242, 0xFF424242, 0xFF3F3F3F, 0xFF3C3C3C,
	    0xFF383838, 0xFF333333, 0xFF2E2E2E, 0xFF292929, 0xFF232323, 0xFF1E1E1E,
	    0xFF181818, 0xFF131313, 0xFF0E0E0E, 0xFF090909, 0xFF050505, 0xFF020202,
	    0xFF000000, 0xFF020202, 0xFF060606, 0xFF0A0A0A, 0xFF0F0F0F, 0xFF141414,
	    0xFF191919, 0xFF1F1F1F, 0xFF252525, 0xFF2B2B2B, 0xFF313131, 0xFF363636,
	    0xFF3B3B3B, 0xFF3F3F3F, 0xFF434343, 0xFF454545, 0xFF474747, 0xFF454545,
	    0xFF434343, 0xFF3F3F3F, 0xFF3B3B3B, 0xFF363636, 0xFF313131, 0xFF2B2B2B,
	    0xFF252525, 0xFF1F1F1F, 0xFF191919, 0xFF141414, 0xFF0F0F0F, 0xFF0A0A0A,
	    0xFF060606, 0xFF020202, 0xFF000000, 0xFF030303, 0xFF060606, 0xFF0B0B0B,
	    0xFF0F0F0F, 0xFF151515, 0xFF1A1A1A, 0xFF202020, 0xFF262626, 0xFF2C2C2C,
	    0xFF323232, 0xFF383838, 0xFF3D3D3D, 0xFF424242, 0xFF454545, 0xFFAEAEAE,
	    0xFFD3D3D3, 0xFF454545, 0xFF454545, 0xFF424242, 0xFF3D3D3D, 0xFF383838,
	    0xFF323232, 0xFF2C2C2C, 0xFF262626, 0xFF202020, 0xFF1A1A1A, 0xFF151515,
	    0xFF0F0F0F, 0xFF0B0B0B, 0xFF060606, 0xFF030303, 0xFF000000, 0xFF030303,
	    0xFF060606, 0xFF0B0B0B, 0xFF101010, 0xFF151515, 0xFF1B1B1B, 0xFF212121,
	    0xFF272727, 0xFF2C2C2C, 0xFF323232, 0xFF383838, 0xFF3D3D3D, 0xFF424242,
	    0xFF474747, 0xFFD3D3D3, 0xFFFFFFFF, 0xFF454545, 0xFF474747, 0xFF424242,
	    0xFF3D3D3D, 0xFF383838, 0xFF323232, 0xFF2C2C2C, 0xFF272727, 0xFF212121,
	    0xFF1B1B1B, 0xFF151515, 0xFF101010, 0xFF0B0B0B, 0xFF060606, 0xFF030303,
	    0xFF000000, 0xFF030303, 0xFF060606, 0xFF0B0B0B, 0xFF0F0F0F, 0xFF151515,
	    0xFF1A1A1A, 0xFF202020, 0xFF262626, 0xFF2C2C2C, 0xFF323232, 0xFF383838,
	    0xFF3D3D3D, 0xFF424242, 0xFF454545, 0xFF454545, 0xFF454545, 0xFF454545,
	    0xFF454545, 0xFF424242, 0xFF3D3D3D, 0xFF383838, 0xFF323232, 0xFF2C2C2C,
	    0xFF262626, 0xFF202020, 0xFF1A1A1A, 0xFF151515, 0xFF0F0F0F, 0xFF0B0B0B,
	    0xFF060606, 0xFF030303, 0xFF000000, 0xFF020202, 0xFF060606, 0xFF0A0A0A,
	    0xFF0F0F0F, 0xFF141414, 0xFF191919, 0xFF1F1F1F, 0xFF252525, 0xFF2B2B2B,
	    0xFF313131, 0xFF363636, 0xFF3B3B3B, 0xFF3F3F3F, 0xFF434343, 0xFF454545,
	    0xFF474747, 0xFF454545, 0xFF434343, 0xFF3F3F3F, 0xFF3B3B3B, 0xFF363636,
	    0xFF313131, 0xFF2B2B2B, 0xFF252525, 0xFF1F1F1F, 0xFF191919, 0xFF141414,
	    0xFF0F0F0F, 0xFF0A0A0A, 0xFF060606, 0xFF020202, 0xFF000000, 0xFF020202,
	    0xFF050505, 0xFF090909, 0xFF0E0E0E, 0xFF131313, 0xFF181818, 0xFF1E1E1E,
	    0xFF232323, 0xFF292929, 0xFF2E2E2E, 0xFF333333, 0xFF383838, 0xFF3C3C3C,
	    0xFF3F3F3F, 0xFF424242, 0xFF424242, 0xFF424242, 0xFF3F3F3F, 0xFF3C3C3C,
	    0xFF383838, 0xFF333333, 0xFF2E2E2E, 0xFF292929, 0xFF232323, 0xFF1E1E1E,
	    0xFF181818, 0xFF131313, 0xFF0E0E0E, 0xFF090909, 0xFF050505, 0xFF020202,
	    0xFF000000, 0xFF010101, 0xFF040404, 0xFF080808, 0xFF0C0C0C, 0xFF111111,
	    0xFF161616, 0xFF1B1B1B, 0xFF212121, 0xFF262626, 0xFF2B2B2B, 0xFF303030,
	    0xFF343434, 0xFF383838, 0xFF3B3B3B, 0xFF3D3D3D, 0xFF3D3D3D, 0xFF3D3D3D,
	    0xFF3B3B3B, 0xFF383838, 0xFF343434, 0xFF303030, 0xFF2B2B2B, 0xFF262626,
	    0xFF212121, 0xFF1B1B1B, 0xFF161616, 0xFF111111, 0xFF0C0C0C, 0xFF080808,
	    0xFF040404, 0xFF010101, 0xFF000000, 0xFF010101, 0xFF030303, 0xFF070707,
	    0xFF0B0B0B, 0xFF0F0F0F, 0xFF141414, 0xFF191919, 0xFF1E1E1E, 0xFF232323,
	    0xFF282828, 0xFF2C2C2C, 0xFF303030, 0xFF333333, 0xFF363636, 0xFF383838,
	    0xFF383838, 0xFF383838, 0xFF363636, 0xFF333333, 0xFF303030, 0xFF2C2C2C,
	    0xFF282828, 0xFF232323, 0xFF1E1E1E, 0xFF191919, 0xFF141414, 0xFF0F0F0F,
	    0xFF0B0B0B, 0xFF070707, 0xFF030303, 0xFF010101, 0xFF000000, 0xFF000000,
	    0xFF020202, 0xFF050505, 0xFF090909, 0xFF0D0D0D, 0xFF121212, 0xFF161616,
	    0xFF1B1B1B, 0xFF1F1F1F, 0xFF242424, 0xFF282828, 0xFF2B2B2B, 0xFF2E2E2E,
	    0xFF313131, 0xFF323232, 0xFF323232, 0xFF323232, 0xFF313131, 0xFF2E2E2E,
	    0xFF2B2B2B, 0xFF282828, 0xFF242424, 0xFF1F1F1F, 0xFF1B1B1B, 0xFF161616,
	    0xFF121212, 0xFF0D0D0D, 0xFF090909, 0xFF050505, 0xFF020202, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF010101, 0xFF040404, 0xFF070707, 0xFF0B0B0B,
	    0xFF0E0E0E, 0xFF131313, 0xFF171717, 0xFF1B1B1B, 0xFF1F1F1F, 0xFF232323,
	    0xFF262626, 0xFF292929, 0xFF2B2B2B, 0xFF2C2C2C, 0xFF2C2C2C, 0xFF2C2C2C,
	    0xFF2B2B2B, 0xFF292929, 0xFF262626, 0xFF232323, 0xFF1F1F1F, 0xFF1B1B1B,
	    0xFF171717, 0xFF131313, 0xFF0E0E0E, 0xFF0B0B0B, 0xFF070707, 0xFF040404,
	    0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF020202,
	    0xFF050505, 0xFF080808, 0xFF0C0C0C, 0xFF0F0F0F, 0xFF131313, 0xFF171717,
	    0xFF1B1B1B, 0xFF1E1E1E, 0xFF212121, 0xFF232323, 0xFF252525, 0xFF262626,
	    0xFF272727, 0xFF262626, 0xFF252525, 0xFF232323, 0xFF212121, 0xFF1E1E1E,
	    0xFF1B1B1B, 0xFF171717, 0xFF131313, 0xFF0F0F0F, 0xFF0C0C0C, 0xFF080808,
	    0xFF050505, 0xFF020202, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF010101, 0xFF030303, 0xFF060606, 0xFF090909, 0xFF0C0C0C,
	    0xFF0F0F0F, 0xFF131313, 0xFF161616, 0xFF191919, 0xFF1B1B1B, 0xFF1E1E1E,
	    0xFF1F1F1F, 0xFF202020, 0xFF212121, 0xFF202020, 0xFF1F1F1F, 0xFF1E1E1E,
	    0xFF1B1B1B, 0xFF191919, 0xFF161616, 0xFF131313, 0xFF0F0F0F, 0xFF0C0C0C,
	    0xFF090909, 0xFF060606, 0xFF030303, 0xFF010101, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF030303,
	    0xFF060606, 0xFF090909, 0xFF0C0C0C, 0xFF0E0E0E, 0xFF121212, 0xFF141414,
	    0xFF161616, 0xFF181818, 0xFF191919, 0xFF1A1A1A, 0xFF1B1B1B, 0xFF1A1A1A,
	    0xFF191919, 0xFF181818, 0xFF161616, 0xFF141414, 0xFF121212, 0xFF0E0E0E,
	    0xFF0C0C0C, 0xFF090909, 0xFF060606, 0xFF030303, 0xFF010101, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF010101, 0xFF030303, 0xFF060606, 0xFF080808, 0xFF0B0B0B,
	    0xFF0D0D0D, 0xFF0F0F0F, 0xFF111111, 0xFF131313, 0xFF141414, 0xFF151515,
	    0xFF151515, 0xFF151515, 0xFF141414, 0xFF131313, 0xFF111111, 0xFF0F0F0F,
	    0xFF0D0D0D, 0xFF0B0B0B, 0xFF080808, 0xFF060606, 0xFF030303, 0xFF010101,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF030303,
	    0xFF050505, 0xFF070707, 0xFF090909, 0xFF0B0B0B, 0xFF0C0C0C, 0xFF0E0E0E,
	    0xFF0F0F0F, 0xFF0F0F0F, 0xFF101010, 0xFF0F0F0F, 0xFF0F0F0F, 0xFF0E0E0E,
	    0xFF0C0C0C, 0xFF0B0B0B, 0xFF090909, 0xFF070707, 0xFF050505, 0xFF030303,
	    0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF010101, 0xFF020202, 0xFF040404, 0xFF050505, 0xFF070707,
	    0xFF080808, 0xFF090909, 0xFF0A0A0A, 0xFF0B0B0B, 0xFF0B0B0B, 0xFF0B0B0B,
	    0xFF0A0A0A, 0xFF090909, 0xFF080808, 0xFF070707, 0xFF050505, 0xFF040404,
	    0xFF020202, 0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101,
	    0xFF020202, 0xFF030303, 0xFF040404, 0xFF050505, 0xFF060606, 0xFF060606,
	    0xFF060606, 0xFF060606, 0xFF060606, 0xFF050505, 0xFF040404, 0xFF030303,
	    0xFF020202, 0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF010101, 0xFF010101, 0xFF020202,
	    0xFF020202, 0xFF030303, 0xFF030303, 0xFF030303, 0xFF020202, 0xFF020202,
	    0xFF010101, 0xFF010101, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000,
	    0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000, 0xFF000000 };

        glGenTextures( 1, &gGlowTexture );
        glBindTexture( GL_TEXTURE_2D, gGlowTexture );

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, IMAGE_WIDTH, IMAGE_HEIGHT,
        			  0, GL_BGRA, GL_UNSIGNED_BYTE, image_array + 8 );

        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	}

	return gGlowTexture;
}


/******************************************************************************


******************************************************************************/

void FontInit()
{
	const GLubyte rasterfont[95][13] = {

		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36},
		{0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00},
		{0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18},
		{0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70},
		{0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e},
		{0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c},
		{0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30},
		{0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00},
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03},
		{0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c},
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e},
		{0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e},
		{0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06},
		{0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60},
		{0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e},
		{0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18},
		{0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e},
		{0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06},
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3},
		{0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c},
		{0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe},
		{0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff},
		{0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3},
		{0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3},
		{0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff},
		{0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c},
		{0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60},
		{0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18},
		{0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70},
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03},
		{0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e},
		{0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00},
		{0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00},
		{0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0},
		{0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78},
		{0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00},
		{0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00},
		{0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f},
		{0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
		{0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00}
	};


	int i;
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );			// bit alignment
	gFontOffset = glGenLists( 128 );					// 128 display lists
	for( i = 32; i < 126; i++ )
	{
		glNewList( i + gFontOffset, GL_COMPILE );		// make list
			glBitmap( 8, 13, 0.0, 2.0, 10.0, 0.0, &rasterfont[i-32][0] );	// add each letter to the Dlist
		glEndList();
	}


}

/******************************************************************************

 Public Funks

******************************************************************************/



void glScreen2D( const int width, const int height, const int mode )
{
	glScreen2DEx( width, height, mode, 0, 0 );
}


// GLFW_WINDOW or GLFW_FULLSCREEN
void glScreen2DEx( const int width, const int height, const int mode,
				   const int depthbits, const int stencilbits )
{

    if( !glfwOpenWindow( width, height,
						 0,      			// Red
						 0,        			// green
						 0, 				// Blue
						 0, 				// Alpha
						 depthbits, 				// Depth
						 stencilbits, 				// Stencil
						 mode ) )
    {
        glfwTerminate();
    }

    glfwSetWindowTitle( "Easy GL2D" );


    double FOVy;
    double aspect;
    double znear;
    double zfar;

    // using screen info w and h as params
    glViewport( 0, 0, width, height );

    // Set current Mode to projection(ie: 3d)
    glMatrixMode( GL_PROJECTION );

    // Load identity matrix to projection matrix
    glLoadIdentity();

    // Set gluPerspective params
    FOVy = 90 / 2.0f;                                     //45 deg fovy
    aspect = width / (float)height;
    znear = 1;                                       //Near clip
    zfar = 500;                                      //far clip

    // use glu Perspective to set our 3d frustum dimension up
    gluPerspective( FOVy, aspect, znear, zfar );

    // Modelview mode
    // ie. Matrix that does things to anything we draw
    // as in lines, points, tris, etc.
    glMatrixMode( GL_MODELVIEW );

    // load identity(clean) matrix to modelview
    glLoadIdentity();

    glShadeModel( GL_SMOOTH );                 //'set shading to smooth(try GL_FLAT)
    glClearColor( 0.0, 0.0, 0.0, 1.0 );        //'set Clear color to BLACK
    glClearDepth( 1.0 );                       //'Set Depth buffer to 1(z-Buffer)
    glDisable( GL_DEPTH_TEST );                //'Disable Depth Testing so that our z-buffer works

    //'compare each incoming pixel z value with the z value present in the depth buffer
    //'LEQUAL means than pixel is drawn if the incoming z value is less than
    //'or equal to the stored z value
    glDepthFunc( GL_LEQUAL );

    //'have one or more material parameters track the current color
    //'Material is your 3d model
    glEnable( GL_COLOR_MATERIAL );


    //Enable Texturing
    glEnable( GL_TEXTURE_2D );


    //'Tell openGL that we want the best possible perspective transform
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    //'Disable Backface culling
    glDisable ( GL_CULL_FACE );

    glPolygonMode( GL_FRONT, GL_FILL );

    //'' enable blending for transparency
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glDisable( GL_DEPTH_TEST );

    glEnable( GL_ALPHA_TEST );
    glAlphaFunc( GL_GREATER, 0 );


    glDisable( GL_STENCIL_TEST );
    glDisable( GL_TEXTURE_1D );
    glDisable( GL_LIGHTING );
    glDisable( GL_LOGIC_OP );
    glDisable( GL_DITHER );
    glDisable( GL_FOG );

    glHint( GL_POINT_SMOOTH_HINT, GL_NICEST );
    glHint( GL_LINE_SMOOTH_HINT , GL_NICEST );

    glPointSize( 1.0 );
    glLineWidth( 1.0 );

	FontInit();

}


/******************************************************************************


******************************************************************************/
void glClose()
{
	glDeleteTextures ( 1, &gGlowTexture );
}

/******************************************************************************


******************************************************************************/

void glBlendMode( const GL2D_BLEND_MODE mode )
{
    switch ( mode )
    {
    	case GL2D_TRANS:
			glDisable( GL_BLEND );
			glEnable( GL_ALPHA_TEST );
			break;
		case GL2D_SOLID:
			glDisable( GL_BLEND );
			glDisable( GL_ALPHA_TEST );
			break;
		case GL2D_BLENDED:
			glEnable( GL_BLEND );
			glEnable( GL_ALPHA_TEST );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE );
			break;
		case GL2D_GLOW:
			glEnable( GL_BLEND );
			glEnable( GL_ALPHA_TEST );
			glBlendFunc( GL_ONE, GL_ONE );
			break;
        case GL2D_ALPHA:
			glEnable( GL_BLEND );
			glEnable( GL_ALPHA_TEST );
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			break;
		case GL2D_BLACK:
			glEnable( GL_BLEND );
			glEnable( GL_ALPHA_TEST );
			glBlendFunc( GL_ZERO,GL_ONE_MINUS_SRC_ALPHA );
			break;
		default:
			glDisable( GL_BLEND );
			glEnable( GL_ALPHA_TEST );
	}

}


/******************************************************************************


******************************************************************************/

void glClearScreen()
{

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

}


/******************************************************************************


******************************************************************************/

void glLineGlow( const int x1, const int y1,
                 const int x2, const int y2,
                 const int width, const GLuint color )
{

	GLuint textureID;

	textureID = GetGlowImage();

    glColor4ubv ( (GLubyte*)(&color) ) ;

	// Only change active texture when there is a need
	// Speeds up the rendering by batching textures

    if ( textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, textureID );
        gCurrentTexture = textureID;
    }


	float nx,ny;
	nx = -( y2-y1 );
	ny =  ( x2-x1 );

	float leng;
    leng = sqrt( nx * nx + ny * ny );
    nx = nx / leng;
    ny = ny / leng;

	nx *= width / 2.0;
	ny *= width / 2.0;

	float lx1, ly1, lx2, ly2, lx3, ly3, lx4, ly4;

	lx1 = x2 + nx;
    ly1 = y2 + ny;
    lx2 = x2 - nx;
    ly2 = y2 - ny;
    lx3 = x1 - nx;
    ly3 = y1 - ny;
    lx4 = x1 + nx;
    ly4 = y1 + ny;

	// MAIN
	glBegin( GL_QUADS );
		glTexCoord2f( 0.5, 0.0 ); glVertex3f( lx1, ly1, 0.0 );
		glTexCoord2f( 0.5, 1.0 ); glVertex3f( lx2, ly2, 0.0 );
		glTexCoord2f( 0.5, 1.0 ); glVertex3f( lx3, ly3, 0.0 );
		glTexCoord2f( 0.5, 0.0 ); glVertex3f( lx4, ly4, 0.0 );
	glEnd();

	//RIGHT
	float lx5, ly5, lx6, ly6, vx, vy;
	vx = ( x2-x1 );
	vy = ( y2-y1 );
	leng = sqrt( vx * vx + vy * vy );
	vx = vx / leng;
	vy = vy / leng;
	vx *= width / 2.0;
	vy *= width / 2.0;

	lx5 = lx1 + vx;
	ly5 = ly1 + vy;
	lx6 = lx2 + vx;
	ly6 = ly2 + vy;

	glBegin( GL_QUADS );
		glTexCoord2f( 0.5, 0.0 ); glVertex3f( lx1, ly1,0.0 );
		glTexCoord2f( 1.0, 0.0 ); glVertex3f( lx5, ly5,0.0 );
		glTexCoord2f( 1.0, 1.0 ); glVertex3f( lx6, ly6,0.0 );
		glTexCoord2f( 0.5, 1.0 ); glVertex3f( lx2, ly2,0.0 );
	glEnd();

	// LEFT
	lx5 = lx4 - vx;
	ly5 = ly4 - vy;
	lx6 = lx3 - vx;
	ly6 = ly3 - vy;

	glBegin( GL_QUADS );
		glTexCoord2f( 0.5, 0.0 ); glVertex3f( lx4, ly4, 0.0 );
		glTexCoord2f( 0.5, 1.0 ); glVertex3f( lx3, ly3 ,0.0 );
		glTexCoord2f( 1.0, 1.0 ); glVertex3f( lx6, ly6, 0.0 );
		glTexCoord2f( 1.0, 0.0 ); glVertex3f( lx5, ly5, 0.0 );
	glEnd();

	glColor4ub( 255, 255, 255, 255 );

}


/******************************************************************************


******************************************************************************/
void glPutPixel( int x, int y, const GLuint color )
{
    glDisable( GL_TEXTURE_2D );
    glColor4ubv ( (GLubyte*)(&color)) ;

    glBegin( GL_POINTS );
		glVertex2i( x, y );
	glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}

/******************************************************************************


******************************************************************************/
void glLine( int x1, int y1, int x2, int y2, const GLuint color )
{
    glDisable( GL_TEXTURE_2D );
    glColor4ubv ( (GLubyte*)(&color)) ;

    glBegin( GL_LINES );
		glVertex2i( x1, y1 );
		glVertex2i( x2, y2 );
	glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}

/******************************************************************************


******************************************************************************/
void glLineGradient( int x1, int y1, int x2, int y2,
                     const GLuint color1, const GLuint color2 )
{
    glDisable( GL_TEXTURE_2D );

    glBegin( GL_LINES );
		glColor4ubv( (GLubyte*)(&color1) ); glVertex2i( x1, y1 );
		glColor4ubv( (GLubyte*)(&color2) ); glVertex2i( x2, y2 );
	glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}

/******************************************************************************


******************************************************************************/
void glBox( int x1, int y1, int x2, int y2, const GLuint color )
{
    glDisable( GL_TEXTURE_2D );
    glColor4ubv ( (GLubyte*)(&color)) ;

    glBegin( GL_LINE_STRIP );
		glVertex2i( x1, y1 );
		glVertex2i( x2, y1 );
		glVertex2i( x2, y2 );
		glVertex2i( x1, y2 );
		glVertex2i( x1, y1 );
	glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}

/******************************************************************************


******************************************************************************/

void glBoxFilled( int x1, int y1, int x2, int y2, const GLuint color )
{
    glDisable( GL_TEXTURE_2D );
    glColor4ubv ( (GLubyte*)(&color)) ;

    x2++;
    y2++;

    glBegin( GL_QUADS );

        glVertex2i	( x1,y1 );
        glVertex2i	( x1,y2 );
        glVertex2i	( x2,y2 );
        glVertex2i	( x2,y1 );

    glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}


/******************************************************************************


******************************************************************************/

void glBoxFilledGradient( int x1, int y1, int x2, int y2,
                          const GLuint color1, const GLuint color2,
                          const GLuint color3, const GLuint color4 )
{
    glDisable( GL_TEXTURE_2D );

    x2++;
    y2++;

    glBegin( GL_QUADS );

        glColor4ubv( (GLubyte*)(&color1) ); glVertex2i( x1,y1 );
        glColor4ubv( (GLubyte*)(&color2) ); glVertex2i( x1,y2 );
        glColor4ubv( (GLubyte*)(&color3) ); glVertex2i( x2,y2 );
        glColor4ubv( (GLubyte*)(&color4) ); glVertex2i( x2,y1 );

    glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}


/******************************************************************************


******************************************************************************/
void glTriangle( int x1, int y1, int x2, int y2, int x3, int y3, const GLuint color )
{
    glDisable( GL_TEXTURE_2D );
    glColor4ubv ( (GLubyte*)(&color)) ;

    glBegin( GL_LINE_STRIP );
		glVertex2i( x1, y1 );
		glVertex2i( x2, y2 );
		glVertex2i( x3, y3 );
		glVertex2i( x1, y1 );
	glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}

/******************************************************************************


******************************************************************************/
void glTriangleFilled( int x1, int y1, int x2, int y2, int x3, int y3, const GLuint color )
{
    glDisable( GL_TEXTURE_2D );
    glColor4ubv ( (GLubyte*)(&color)) ;

    glBegin( GL_TRIANGLES );
		glVertex2i( x1, y1 );
		glVertex2i( x2, y2 );
		glVertex2i( x3, y3 );
	glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}


/******************************************************************************


******************************************************************************/
void glTriangleFilledGradient( int x1, int y1, int x2, int y2, int x3, int y3,
                               const GLuint color1, const GLuint color2, const GLuint color3 )
{
    glDisable( GL_TEXTURE_2D );

    glBegin( GL_TRIANGLES );
		glColor4ubv( (GLubyte*)(&color1) ); glVertex2i( x1, y1 );
		glColor4ubv( (GLubyte*)(&color2) ); glVertex2i( x2, y2 );
		glColor4ubv( (GLubyte*)(&color3) ); glVertex2i( x3, y3 );
	glEnd();

    glEnable( GL_TEXTURE_2D );

    glColor4ub( 255, 255, 255, 255 );

}

/******************************************************************************

    Contributed by Michael "h4tt3n" Nissen(I added a filled version ;*))
    syntax: ellipse(center x, center y, semimajor axis, semiminor axis, angle in degrees, color)

******************************************************************************/
void glEllipse( int x, int y, int a, int b, int degrees, const GLuint color )
{

	// these constants decide the quality of the ellipse
	const float  pi = M_PI;
	const float  twopi  = 2 * pi;   //        two pi (radians in a circle)
	const int face_length  = 8;     //        approx. face length in pixels
	const int max_faces = 256;      //        maximum number of faces in ellipse
	const int min_faces = 16;       //        minimum number of faces in ellipse

	// approx. ellipse circumference (hudson's method)
	float h = ( a-b*a-b ) / (float)( a+b*a+b );
	float circumference = 0.25 * pi * (a+b) * (3* (1+h*0.25)+1 / (float)(1-h*0.25));

	// number of faces in ellipse
	int num_faces = circumference/face_length;

	// clamp number of faces
	if( num_faces > max_faces ) num_faces = max_faces;
	if( num_faces < min_faces ) num_faces = min_faces;

	// keep number of faces divisible by 4
	num_faces -= (num_faces & 3);

	// precalc cosine theta
	float angle = degrees * M_PI /180.0;
	float s   = sin(twopi/(float)num_faces);
	float c   = cos(twopi/(float)num_faces);
	float xx  = 1;
	float yy  = 0;
	float xt  = 0;
	float ax  = cos(angle);
	float ay  = sin(angle);


	// draw ellipse
	glDisable( GL_TEXTURE_2D );
	glColor4ubv( (GLubyte*)(&color) );

    int i;
	glBegin( GL_LINE_LOOP );

		for( i = 0; i < num_faces; i++ )
		{
		    xt = xx;
			xx = c * xx - s * yy;
			yy = s * xt + c * yy;
			glVertex2f( x+a*xx*ax-b*yy*ay, y+a*xx*ay+b*yy*ax );
		}

		glVertex2f( x+a*ax, y+a*ay );

	glEnd();

	glEnable( GL_TEXTURE_2D );

	glColor4ub( 255, 255, 255,255 );

}

/******************************************************************************

    Contributed by Michael "h4tt3n" Nissen(I added a filled version ;*))
    syntax: ellipse(center x, center y, semimajor axis, semiminor axis, angle in degrees, color)

******************************************************************************/
void glEllipseFilled( int x, int y, int a, int b, int degrees, const GLuint color )
{

	// these constants decide the quality of the ellipse
	const float  pi = M_PI;
	const float  twopi  = 2 * pi;   //        two pi (radians in a circle)
	const int face_length  = 8;     //        approx. face length in pixels
	const int max_faces = 256;      //        maximum number of faces in ellipse
	const int min_faces = 16;       //        minimum number of faces in ellipse

	// approx. ellipse circumference (hudson's method)
	float h = ( a-b*a-b ) / (float)( a+b*a+b );
	float circumference = 0.25 * pi * (a+b) * (3* (1+h*0.25)+1 / (float)(1-h*0.25));

	// number of faces in ellipse
	int num_faces = circumference/face_length;

	// clamp number of faces
	if( num_faces > max_faces ) num_faces = max_faces;
	if( num_faces < min_faces ) num_faces = min_faces;

	// keep number of faces divisible by 4
	num_faces -= (num_faces & 3);

	// precalc cosine theta
	float angle = degrees * M_PI /180.0;
	float s   = sin(twopi/(float)num_faces);
	float c   = cos(twopi/(float)num_faces);
	float xx  = 1;
	float yy  = 0;
	float xt  = 0;
	float ax  = cos(angle);
	float ay  = sin(angle);


	// draw ellipse
	glDisable( GL_TEXTURE_2D );
	glColor4ubv( (GLubyte*)(&color) );

    int i;
	glBegin( GL_TRIANGLE_FAN );

		for( i = 0; i < num_faces; i++ )
		{
		    xt = xx;
			xx = c * xx - s * yy;
			yy = s * xt + c * yy;
			glVertex2f( x+a*xx*ax-b*yy*ay, y+a*xx*ay+b*yy*ax );
		}

		glVertex2f( x+a*ax, y+a*ay );

	glEnd();

	glEnable( GL_TEXTURE_2D );

	glColor4ub( 255, 255, 255,255 );

}

/******************************************************************************

    Draws a sprite
	Parameters:
       x 		-> x position of the sprite
	   y 		-> y position of the sprite
	   flipmode -> mode for flipping (see GL_FLIP_MODE enum)
	   *spr 	-> pointer to a glImage

******************************************************************************/
void glSprite( const int x, const int y, const int flipmode, const glImage *spr )
{
    int x1 = x;
    int y1 = y;
    int x2 = x + spr->width;
    int y2 = y + spr->height;

    float u1 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off + spr->u_width  : spr->u_off;
    float u2 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off 			       : spr->u_off + spr->u_width;
    float v1 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off + spr->v_height : spr->v_off;
    float v2 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off 			       : spr->v_off + spr->v_height;


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

    glBegin( GL_QUADS );

        glTexCoord2f( u1, v1 ); glVertex2i( x1, y1 );
        glTexCoord2f( u1, v2 ); glVertex2i( x1, y2 );
        glTexCoord2f( u2, v2 ); glVertex2i( x2, y2 );
        glTexCoord2f( u2, v1 ); glVertex2i( x2, y1 );

    glEnd();


}

/******************************************************************************

    Draws a scaled sprite
	Parameters:
       x 		-> x position of the sprite
	   y 		-> y position of the sprite
	   scale    -> float value to scale the sprite (1.0 for no scaling)
	   flipmode -> mode for flipping (see GL_FLIP_MODE enum)
	   *spr 	-> pointer to a glImage

******************************************************************************/
void glSpriteScale( const int x, const int y, const float scale, const int flipmode, const glImage *spr )
{
    int x1 = 0;
    int y1 = 0;
    int x2 = spr->width;
    int y2 = spr->height;

    float u1 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off + spr->u_width  : spr->u_off;
    float u2 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off 			       : spr->u_off + spr->u_width;
    float v1 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off + spr->v_height : spr->v_off;
    float v2 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off 			       : spr->v_off + spr->v_height;


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

    glPushMatrix();

    glTranslatef( x, y, 0.0 );
    glScalef( scale, scale, 1.0 );

    glBegin( GL_QUADS );

        glTexCoord2f( u1, v1 ); glVertex2i( x1, y1 );
        glTexCoord2f( u1, v2 ); glVertex2i( x1, y2 );
        glTexCoord2f( u2, v2 ); glVertex2i( x2, y2 );
        glTexCoord2f( u2, v1 ); glVertex2i( x2, y1 );

    glEnd();

    glPopMatrix();

}


/******************************************************************************

    Draws a scaled sprite
	Parameters:
       x 		-> x position of the sprite
	   y 		-> y position of the sprite
	   scale    -> float value to scale the sprite (1.0 for no scaling)
	   flipmode -> mode for flipping (see GL_FLIP_MODE enum)
	   *spr 	-> pointer to a glImage

******************************************************************************/
void glSpriteScaleXY( const int x, const int y, const float scaleX, const float scaleY, const int flipmode, const glImage *spr )
{
    int x1 = 0;
    int y1 = 0;
    int x2 = spr->width;
    int y2 = spr->height;

    float u1 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off + spr->u_width  : spr->u_off;
    float u2 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off 			       : spr->u_off + spr->u_width;
    float v1 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off + spr->v_height : spr->v_off;
    float v2 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off 			       : spr->v_off + spr->v_height;


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

    glPushMatrix();

    glTranslatef( x, y, 0.0 );
    glScalef( scaleX, scaleY, 1.0 );

    glBegin( GL_QUADS );

        glTexCoord2f( u1, v1 ); glVertex2i( x1, y1 );
        glTexCoord2f( u1, v2 ); glVertex2i( x1, y2 );
        glTexCoord2f( u2, v2 ); glVertex2i( x2, y2 );
        glTexCoord2f( u2, v1 ); glVertex2i( x2, y1 );

    glEnd();

    glPopMatrix();

}

/******************************************************************************

    Draws a center rotated sprite
	Parameters:
       x 		-> x position of the sprite center
	   y 		-> y position of the sprite center
	   angle    -> is the angle to rotated (in degrees)
	   flipmode -> mode for flipping (see GL_FLIP_MODE enum)
	   *spr 	-> pointer to a glImage

******************************************************************************/
void glSpriteRotate( const int x, const int y, const int angle, const int flipmode, const glImage *spr )
{

    int s_half_x = spr->width/2;
    int	s_half_y = spr->height/2;

    int x1 =  -s_half_x;
    int y1 =  -s_half_y;

    int x2 =  s_half_x;
    int y2 =  s_half_y;


    float u1 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off + spr->u_width  : spr->u_off;
    float u2 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off 			       : spr->u_off + spr->u_width;
    float v1 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off + spr->v_height : spr->v_off;
    float v2 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off 			       : spr->v_off + spr->v_height;


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

    glPushMatrix();

    glTranslatef( x, y, 0.0 );
    glRotatef( angle, 0.0, 0.0, 1.0 );


    glBegin( GL_QUADS );

        glTexCoord2f( u1, v1 ); glVertex2i( x1, y1 );
        glTexCoord2f( u1, v2 ); glVertex2i( x1, y2 );
        glTexCoord2f( u2, v2 ); glVertex2i( x2, y2 );
        glTexCoord2f( u2, v1 ); glVertex2i( x2, y1 );

    glEnd();

    glPopMatrix();


}



/******************************************************************************

    Draws a center rotated and scaled sprite
	Parameters:
       x 		-> x position of the sprite center
	   y 		-> y position of the sprite center
	   angle    -> is the angle to rotated (-32768 to 32767)
	   scale    -> is a 20.12 FP scale value (you can use floattof32(1.45) to scale
	               and GCC would optimize it to a constant)
	   flipmode -> mode for flipping (see GL_FLIP_MODE enum)
	   *spr 	-> pointer to a glImage

******************************************************************************/
void glSpriteRotateScale( const int x, const int y, const int angle, const float scale, const int flipmode, const glImage *spr )
{

    int s_half_x = spr->width / 2;
    int	s_half_y = spr->height / 2;

    int x1 =  -s_half_x;
    int y1 =  -s_half_y;

    int x2 =  s_half_x;
    int y2 =  s_half_y;


    float u1 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off + spr->u_width  : spr->u_off;
    float u2 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off 			       : spr->u_off + spr->u_width;
    float v1 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off + spr->v_height : spr->v_off;
    float v2 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off 			       : spr->v_off + spr->v_height;


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

    glPushMatrix();

    glTranslatef( x, y, 0.0 );
    glScalef( scale, scale, 1.0 );
    glRotatef(angle, 0.0, 0.0, 1.0);

    glBegin( GL_QUADS );

        glTexCoord2f( u1, v1 ); glVertex2i( x1, y1 );
        glTexCoord2f( u1, v2 ); glVertex2i( x1, y2 );
        glTexCoord2f( u2, v2 ); glVertex2i( x2, y2 );
        glTexCoord2f( u2, v1 ); glVertex2i( x2, y1 );

    glEnd();

    glPopMatrix();


}

/******************************************************************************

    Draws a center rotated and scaled sprite
	Parameters:
       x 		-> x position of the sprite center
	   y 		-> y position of the sprite center
	   angle    -> is the angle to rotated (-32768 to 32767)
	   scale    -> is a 20.12 FP scale value (you can use floattof32(1.45) to scale
	               and GCC would optimize it to a constant)
	   flipmode -> mode for flipping (see GL_FLIP_MODE enum)
	   *spr 	-> pointer to a glImage

******************************************************************************/
void glSpriteRotateScaleXY( const int x, const int y, const int angle, const float scaleX, const float scaleY, const int flipmode, const glImage *spr )
{

    int s_half_x = spr->width / 2;
    int	s_half_y = spr->height / 2;

    int x1 =  -s_half_x;
    int y1 =  -s_half_y;

    int x2 =  s_half_x;
    int y2 =  s_half_y;


    float u1 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off + spr->u_width  : spr->u_off;
    float u2 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off 			       : spr->u_off + spr->u_width;
    float v1 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off + spr->v_height : spr->v_off;
    float v2 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off 			       : spr->v_off + spr->v_height;


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

    glPushMatrix();

    glTranslatef( x, y, 0.0 );
    glScalef( scaleX, scaleY, 1.0 );
    glRotatef(angle, 0.0, 0.0, 1.0);

    glBegin( GL_QUADS );

        glTexCoord2f( u1, v1 ); glVertex2i( x1, y1 );
        glTexCoord2f( u1, v2 ); glVertex2i( x1, y2 );
        glTexCoord2f( u2, v2 ); glVertex2i( x2, y2 );
        glTexCoord2f( u2, v1 ); glVertex2i( x2, y1 );

    glEnd();

    glPopMatrix();


}

/******************************************************************************

    Draws a sprite stretched on a quad
	Parameters:
		x1 			-> x1 position of the sprite
		y1 			-> y1 position of the sprite
		x2 			-> x2 position of the sprite
		y2 			-> y2 position of the sprite
		x3 			-> x3 position of the sprite
		y3 			-> y3 position of the sprite
		x4 			-> x4 position of the sprite
		y4 			-> y4 position of the sprite
		flipmode 	-> mode for flipping (see GL_FLIP_MODE enum)
		*spr 		-> pointer to a glImage

******************************************************************************/
void glSpriteOnQuad( int x1, int y1,
					 int x2, int y2,
					 int x3, int y3,
					 int x4, int y4,
					 float uoff, float voff,
					 int flipmode, const glImage *spr )
{

	float u1 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off + spr->u_width  : spr->u_off;
    float u2 = ( flipmode & GL2D_FLIP_H ) ? spr->u_off 			       : spr->u_off + spr->u_width;
    float v1 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off + spr->v_height : spr->v_off;
    float v2 = ( flipmode & GL2D_FLIP_V ) ? spr->v_off 			       : spr->v_off + spr->v_height;


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }


	glBegin( GL_QUADS );

		glTexCoord2f( u1+uoff, v1+voff ); glVertex2i( x1, y1 );
		glTexCoord2f( u1+uoff, v2+voff ); glVertex2i( x2, y2 );
		glTexCoord2f( u2+uoff, v2+voff ); glVertex2i( x3, y3 );
		glTexCoord2f( u2+uoff, v1+voff ); glVertex2i( x4, y4 );

	glEnd();

}


/******************************************************************************

    Draws a sprite stretched on a quad
	Parameters:
		x1 			-> x1 position of the sprite
		y1 			-> y1 position of the sprite
		x2 			-> x2 position of the sprite
		y2 			-> y2 position of the sprite
		x3 			-> x3 position of the sprite
		y3 			-> y3 position of the sprite
		x4 			-> x4 position of the sprite
		y4 			-> y4 position of the sprite
		flipmode 	-> mode for flipping (see GL_FLIP_MODE enum)
		*spr 		-> pointer to a glImage

******************************************************************************/
void glSpriteOnQuadClipped( int x1, int y1,
							int x2, int y2,
							int x3, int y3,
							int x4, int y4,
							float luclip, float lvclip,
							float ruclip, float rvclip,
							int flipmode, const glImage *spr )
{


	float u1 = spr->u_off + (( flipmode & GL2D_FLIP_H ) ? spr->u_width-(ruclip) : luclip);
 	float u2 = spr->u_off + (( flipmode & GL2D_FLIP_H ) ? luclip 		    	: spr->u_width-(ruclip));
	float v1 = spr->v_off + (( flipmode & GL2D_FLIP_V ) ? spr->v_height-(rvclip): lvclip);
 	float v2 = spr->v_off + (( flipmode & GL2D_FLIP_V ) ? lvclip		    	: spr->v_height-(rvclip));


    if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

	glBegin( GL_QUADS );

		glTexCoord2f( u1, v1 ); glVertex2i( x1, y1 );
		glTexCoord2f( u1, v2 ); glVertex2i( x2, y2 );
		glTexCoord2f( u2, v2 ); glVertex2i( x3, y3 );
		glTexCoord2f( u2, v1 ); glVertex2i( x4, y4 );

	glEnd();


}



/******************************************************************************

    Draws a sprite cleanly stretched horizontally
	Parameters:
		x 			-> x1 position of the sprite
		y 			-> y1 position of the sprite
		flipmode 	-> mode for flipping (see GL_FLIP_MODE enum)
		*spr 		-> pointer to a glImage

******************************************************************************/
void glSpriteStretchHorizontal( int x, int y, int length, const glImage *spr )
{
	int hw = (spr->width/2);

	int x1 = x;
	int y1 = y;
	int x2 = x + length;
	int y2 = y + spr->height;

	float u_off = spr->u_off;
	float v_off = spr->v_off;

	float u_width = spr->u_width;
	float v_height = spr->v_height;

	float su = u_width/2.0f;

	if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

	// left
	int x2l = x1 + hw;

	glBegin( GL_QUADS );

		glTexCoord2f( u_off, v_off );
		glVertex2i( x1, y1 );

		glTexCoord2f( u_off, v_off + v_height );
		glVertex2i( x1, y2 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( x2l, y2 );

		glTexCoord2f( u_off + su, v_off );
		glVertex2i( x2l, y1 );

	glEnd();

	// center
	int x1l = x + hw;
	x2l = x2 - hw - 1;

	glBegin( GL_QUADS );

		glTexCoord2f( u_off + su, v_off );
		glVertex2i( x1l,y1 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( x1l,y2 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( x2l, y2 );

		glTexCoord2f( u_off + su, v_off );
		glVertex2i( x2l, y1 );

	glEnd();

	// right
	x1l = x2 - hw - 1;

	glBegin( GL_QUADS );

		glTexCoord2f( u_off + su, v_off );
		glVertex2i( x1l,y1 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( x1l, y2 );

		glTexCoord2f( u_off + u_width, v_off + v_height );
		glVertex2i( x2, y2 );

		glTexCoord2f( u_off + u_width, v_off );
		glVertex2i( x2, y1 );

	glEnd();

}

/******************************************************************************

    Draws a sprite cleanly stretched vertically
	Parameters:
		x 			-> x1 position of the sprite
		y 			-> y1 position of the sprite
		flipmode 	-> mode for flipping (see GL_FLIP_MODE enum)
		*spr 		-> pointer to a glImage

******************************************************************************/
void glSpriteStretchVertical( int x, int y, int height, const glImage *spr )
{
	int hh = (spr->height/2);

	int x1 = x;
	int y1 = y;
	int x2 = x + spr->width;
	int y2 = y + height;

	float u_off = spr->u_off;
	float v_off = spr->v_off;

	float u_width = spr->u_width;
	float v_height = spr->v_height;

	float tv = v_height/2.0f;

	if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }

	// top
	int y21 = y1 + hh;

	glBegin( GL_QUADS );

		glTexCoord2f( u_off, v_off );
		glVertex2i( x1, y1 );

		glTexCoord2f( u_off, v_off + tv );
		glVertex2i( x1, y21 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, y21 );

		glTexCoord2f( u_off + u_width, v_off );
		glVertex2i( x2, y1 );

	glEnd();

	// center
	int y11 = y + hh;
	y21 = y2 - hh - 1;

	glBegin( GL_QUADS );

		glTexCoord2f( u_off, v_off + tv );
		glVertex2i( x1,y11 );

		glTexCoord2f( u_off, v_off + tv );
		glVertex2i( x1,y21 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, y21 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, y11 );

	glEnd();

	// bottom
	y11 = y2 - hh - 1;

	glBegin( GL_QUADS );

		glTexCoord2f( u_off, v_off + tv );
		glVertex2i( x1,y11 );

		glTexCoord2f( u_off, v_off + v_height );
		glVertex2i( x1, y2 );

		glTexCoord2f( u_off + u_width, v_off + v_height );
		glVertex2i( x2, y2 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, y11 );

	glEnd();

}


/******************************************************************************

    Draws a sprite cleanly stretched horizontally and vertically
	Parameters:
		x 			-> x1 position of the sprite
		y 			-> y1 position of the sprite
		flipmode 	-> mode for flipping (see GL_FLIP_MODE enum)
		*spr 		-> pointer to a glImage

******************************************************************************/

void glSpriteStretchHV( int x, int y, int length, int height, const glImage *spr )
{

	int hw = (spr->width/2);
	int hh = (spr->height/2);

	int x1 = x;
	int y1 = y;
	int x2 = x + length;
	int y2 = y + height;

	float u_off = spr->u_off;
	float v_off = spr->v_off;

	float u_width = spr->u_width;
	float v_height = spr->v_height;

	float su = u_width/2.0f;
	float tv = v_height/2.0f;

	if ( spr->textureID != gCurrentTexture )
    {
        glBindTexture( GL_TEXTURE_2D, spr->textureID );
        gCurrentTexture = spr->textureID;
    }


	// variables

	int xh1 = x1 + hw;
	int yh1 = y1 + hh;
	int xh2 = x2 - hw;
	int yh2 = y2 - hh;


	// top-left
	glBegin( GL_QUADS );
		glTexCoord2f( u_off, v_off );
		glVertex2i( x1, y1 );

		glTexCoord2f( u_off, v_off + tv );
		glVertex2i( x1, yh1 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh1, yh1 );

		glTexCoord2f( u_off + su, v_off );
		glVertex2i( xh1, y1 );
	glEnd();

	// top-right
	glBegin( GL_QUADS );
		glTexCoord2f( u_off + su, v_off );
		glVertex2i( xh2, y1 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh2, yh1 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, yh1 );

		glTexCoord2f( u_off + u_width, v_off );
		glVertex2i( x2, y1 );
	glEnd();

	// bottom left
	glBegin( GL_QUADS );
		glTexCoord2f( u_off, v_off + tv);
		glVertex2i( x1, yh2 );

		glTexCoord2f( u_off, v_off + v_height );
		glVertex2i( x1, y2 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( xh1, y2 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh1, yh2 );
	glEnd();

	// bottom - right
	glBegin( GL_QUADS );
		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh2,yh2 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( xh2, y2 );

		glTexCoord2f( u_off + u_width, v_off + v_height );
		glVertex2i( x2, y2 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, yh2 );
	glEnd();

	// top-border
	glBegin( GL_QUADS );
		glTexCoord2f( u_off + su, v_off );
		glVertex2i( xh1,y1 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh1,yh1 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh2, yh1 );

		glTexCoord2f( u_off + su, v_off );
		glVertex2i( xh2, y1 );
	glEnd();

	// bottom-border
	glBegin( GL_QUADS );
		glTexCoord2f( u_off + su, v_off + tv);
		glVertex2i( xh1,yh2 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( xh1,y2 );

		glTexCoord2f( u_off + su, v_off + v_height );
		glVertex2i( xh2, y2 );

		glTexCoord2f( u_off + su, v_off + tv);
		glVertex2i( xh2, yh2 );
	glEnd();

	// left-border
	glBegin( GL_QUADS );
		glTexCoord2f( u_off, v_off + tv);
		glVertex2i( x1,yh1 );

		glTexCoord2f( u_off, v_off + tv );
		glVertex2i( x1,yh2 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh1, yh2 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh1, yh1 );
	glEnd();

	// right-border
	glBegin( GL_QUADS );
		glTexCoord2f( u_off + su, v_off + tv);
		glVertex2i( xh2,yh1 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh2,yh2 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, yh2 );

		glTexCoord2f( u_off + u_width, v_off + tv );
		glVertex2i( x2, yh1 );
	glEnd();

	// center
	glBegin( GL_QUADS );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh1,yh1 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh1,yh2 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh2, yh2 );

		glTexCoord2f( u_off + su, v_off + tv );
		glVertex2i( xh2, yh1 );

	glEnd();



}

/******************************************************************************

******************************************************************************/

void glPrint( int x, int y, const char *text, const GLuint color )
{


	glDisable( GL_TEXTURE_2D );
	glColor4ubv( (GLubyte*)(&color) );
		glPushAttrib( GL_LIST_BIT );
			glRasterPos2i( x, y+10 );
			glDisable( GL_TEXTURE_2D );
			glListBase( gFontOffset );
			glCallLists( strlen(text), GL_UNSIGNED_BYTE, text );
		glPopAttrib();
	glEnable( GL_TEXTURE_2D );

}

/******************************************************************************

    Initializes our spriteset with Texture Packer generated UV coordinates
	Very safe and easy to use.
	Parameters:
       filename     -> name of the file to load as texture
       *sprite 		-> pointer to an array of glImage
       width/height -> image dimensions
	   numframes 	-> number of frames in a spriteset (auto-generated by Texture Packer)
	   *texcoords 	-> Texture Packer auto-generated array of UV coords
	   textureID 	-> Texture handle returned by glGenTextures()
       filtemode    -> GL_NEAREST or GL_LINEAR

******************************************************************************/
GLuint glLoadSpriteSet( const char *filename,
                        glImage *sprite,
                        const int width,
                        const int height,
                        const int numframes,
                        const unsigned int *texcoords,
                        const  GLuint filtermode )
{

    int i;
    GLuint textureID;

    glGenTextures ( 1, &textureID );
    glBindTexture ( GL_TEXTURE_2D, textureID );

    LoadTexture( filename );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtermode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtermode );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glBindTexture( GL_TEXTURE_2D, 0 );

    // init sprites texture coords and texture ID
    for ( i = 0; i < numframes; i++)
    {
        int j = i * 4; // texcoords array is u_off, wid, hei
        sprite[i].textureID = textureID;
        sprite[i].width = texcoords[j+2];
        sprite[i].height = texcoords[j+3];
        sprite[i].u_off = texcoords[j] / (float)width;				// set x-coord
        sprite[i].v_off = texcoords[j+1] / (float)height;			// y-coord
        sprite[i].u_width = texcoords[j+2] / (float)width;			// set x-coord
        sprite[i].v_height = texcoords[j+3] / (float)height;		// y-coord

    }

    return textureID;

}


/******************************************************************************

    Initializes our Tileset (like glInitSpriteset()) but without the use of
	Texture Packer auto-generated files.
	Very rigid and prone to human error.
	!!! Can ony be used for tilesets whose tiles are the same sizes!!!
	Parameters:
		*sprite 		-> pointer to an array of glImage
		tile_wid 	-> width of each tile in the texture
		tile_hei 	-> height of each tile in the texture
		bmp_wid 	-> width of of the texture in VRAM
		bmp_hei 	-> height of of the texture in VRAM
	    filtemode    -> GL_NEAREST or GL_LINEAR

******************************************************************************/
GLuint  glLoadTileSet( const char *filename,
					   glImage *sprite,
					   const int tile_wid,
					   const int tile_hei,
					   const int bmp_wid,
					   const int bmp_hei,
					   const  GLuint filtermode	)
{


    GLuint textureID;

    glGenTextures ( 1, &textureID );
    glBindTexture ( GL_TEXTURE_2D, textureID );

    LoadTexture( filename );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtermode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtermode );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glBindTexture( GL_TEXTURE_2D, 0 );

	int i = 0;
	int x, y;


	// init sprites texture coords and texture ID
	for( y = 0; y < (bmp_hei/tile_hei); y++ )
	{
		for( x = 0; x < (bmp_wid/tile_wid); x++ )
		{
			sprite[i].width 			= tile_wid;
			sprite[i].height 			= tile_hei;
			sprite[i].u_off				= (x*tile_wid)/(float)bmp_wid;
			sprite[i].v_off				= (y*tile_hei)/(float)bmp_hei;
			sprite[i].u_width 			= tile_wid/(float)bmp_wid;
			sprite[i].v_height 			= tile_hei/(float)bmp_hei;
			sprite[i].textureID 		= textureID;

			i++;
		}
	}

	return textureID;
}

GLuint glLoadSprite( const char *filename,
                     glImage *sprite,
                     const int width,
                     const int height,
                     const  GLuint filtermode )
{

    GLuint textureID;

    glGenTextures ( 1, &textureID );
    glBindTexture ( GL_TEXTURE_2D, textureID );

    LoadTexture( filename );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtermode );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtermode );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    glBindTexture( GL_TEXTURE_2D, 0 );

    sprite->textureID = textureID;
    sprite->width = width;
    sprite->height = height;
    sprite->u_off = 0.0;		// set x-coord
    sprite->v_off = 0.0;		// y-coord
    sprite->u_width = 1.0;		// set x-coord
    sprite->v_height = 1.0;		// y-coord


    return textureID;

}

/******************************************************************************


******************************************************************************/
void glGet( glImage *SpriteDest, const glImage *SpriteSource, int x1, int y1, int x2, int y2 )
{

	int width = (x2 - x1 ) + 1;
	int height = (y2 - y1 ) + 1;
	float uoff = x1 / (float) SpriteSource->width;
	float voff = y1 / (float) SpriteSource->height;
	float uwidth = width / (float) SpriteSource->width;
	float vheight= height / (float) SpriteSource->height;

	SpriteDest->textureID = SpriteSource->textureID;
    SpriteDest->width = width;
    SpriteDest->height = height;
    SpriteDest->u_off = uoff;		// set x-coord
    SpriteDest->v_off = voff;		// y-coord
    SpriteDest->u_width = uwidth;		// set x-coord
    SpriteDest->v_height = vheight;		// y-coord


}
