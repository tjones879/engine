#include "ShaderUniform.h"

ShaderUniform::ShaderUniform()
{}

ShaderUniform::ShaderUniform(GLuint handle, GLenum type)
{
	this->handle = handle;
	this->type = type;
}

GLint ShaderUniform::glHandle()
{
	return handle;
}

GLenum ShaderUniform::glType()
{
	return type;
}
