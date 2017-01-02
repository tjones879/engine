#define GLEW_STATIC
#include <GL/glew.h>

#include "interfaces\Logger.h"
#include "shaders\Shader.h"
#include "shaders\ShaderUniform.h"

Logger logger("hello.txt");
int main()
{
	GLSLProgram program;
	program.compileShaderFromFile("shader.vs", GLSLShader::VERTEX);
	ShaderUniform helloShader = program["hello"];
	return 0;
}