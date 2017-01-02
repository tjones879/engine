#ifndef SHADER_HEADER
#define SHADER_HEADER

#define GLEW_STATIC
#include<GL/glew.h>
#include<glm/glm.hpp>
#include<string>
#include<map>
#include<vector>

#include "../interfaces/Logger.h"

#include "ShaderUniform.h"
#include "VertexAttribute.h"

namespace GLSLShader {
	enum ShaderType {
		VERTEX, FRAGMENT, GEOMETRY, TESS_CONTROL, TESS_EVALUATION
	};
};

extern Logger logger;

// TODO: Auto add shader uniforms to map.
class GLSLProgram
{
public:
	GLSLProgram();
	GLuint compileShaderFromFile(const char* fileName, GLSLShader::ShaderType type);
	GLuint compileShaderFromString(const std::string & source, GLSLShader::ShaderType type);
	bool link();
	void use();
	std::string log();
	GLuint glProgram();
	bool isLinked();
	void bindAttribLocation(GLuint location, const char* name);
	void bindFragDataLocation(GLuint location, const char* name);
	void setUniform(ShaderUniform shaderUniform, GLfloat x, GLfloat y, GLfloat z);
	void setUniform(ShaderUniform shaderUniform, const glm::vec3& v);
	void setUniform(ShaderUniform shaderUniform, const glm::vec4& v);
	void setUniform(ShaderUniform shaderUniform, const glm::mat3& m);
	void setUniform(ShaderUniform shaderUniform, const glm::mat4& m);
	void setUniform(ShaderUniform shaderUniform, GLfloat val);
	void setUniform(ShaderUniform shaderUniform, GLint val);
	void setUniform(ShaderUniform shaderUniform, bool val);
	ShaderUniform operator[](const GLchar* uniformName);
	ShaderUniform operator[](const std::string uniformName);
	std::map<std::string, ShaderUniform> getShaderUniforms();
	std::vector<VertexAttrib> getVertexAttribs();
	void printActiveAttribs();
private:
	const std::string LOG_TAG = "GLSLProgram";
	GLuint program;
	bool linked;
	std::string logString;
	std::map<std::string, ShaderUniform> shaderUniforms;
	//std::vector<ShaderUniform> shaderUniforms;
	std::vector<VertexAttrib> vertexAttribs;
	bool fileExists(const std::string& fileName);
	const std::string loadShaderAsString(const char* fileName);
	void getShaderLog(GLuint shader);
	void readShaderUniforms();
};

#endif // !SHADER_HEADER
