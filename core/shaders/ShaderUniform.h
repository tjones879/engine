#ifndef SHADER_UNIFORM_H
#define SHADER_UNIFORM_H

#include <GL/glew.h>

class ShaderUniform
{
public:
	ShaderUniform();
	ShaderUniform(GLuint handle, GLenum type);
	GLint glHandle();
	GLenum glType();
private:
	GLint handle;
	GLenum type;
};

#endif // !SHADER_UNIFORM_H
