#include "VertexAttribute.h"

VertexAttrib::VertexAttrib(GLint handle)
{
	this->handle = handle;
}

GLint VertexAttrib::glHandle()
{
	return handle;
}