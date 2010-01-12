// these are fake functions so we can compile video-rice, remove later

#include <SDL_opengl.h>
#include "fake_REMOVE.h"

void glBegin(GLenum mode) {}

void glEnd(void) {}

void glVertex3f( GLfloat x,
    GLfloat y,
    GLfloat z ) {}

void glVertex4f( GLfloat x,
    GLfloat y,
    GLfloat z,
    GLfloat w ) {}

void glTexCoord2f( GLfloat s,
    GLfloat t ) {}

void glPolygonMode(     GLenum          face,
        GLenum          mode) {}

void glColor4fv( const GLfloat *v ) {}

