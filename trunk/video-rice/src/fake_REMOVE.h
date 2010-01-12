// these are fake functions so we can compile video-rice, remove later
#ifndef __FAKE_INCLUDE_
#define __FAKE_INCLUDE_

void glBegin(GLenum mode);
void glEnd(void);

void glVertex3f( GLfloat x,
    GLfloat y,
    GLfloat z );

void glVertex4f( GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w );

void glTexCoord2f( GLfloat s,
    GLfloat t );

void glPolygonMode(	GLenum  	face, 
 	GLenum  	mode);

void glColor4fv( const GLfloat *v );

#define GL_NONE GL_ZERO 
#define GL_LINE 0
#define GL_FILL 0

#define glFogi(X,Y) glFogx(X,Y)
#define GL_UNSIGNED_INT GL_FIXED

#endif

