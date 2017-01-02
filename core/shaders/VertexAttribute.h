#ifndef VERTEX_ATTRIB_H
#define VERTEX_ATTRIB_H

#include <gl/glew.h>

class VertexAttrib
{
public:
	VertexAttrib(GLint handle);
	GLint glHandle();
private:
	GLint handle;
};

#endif // !VERTEX_ATTRIB_H
