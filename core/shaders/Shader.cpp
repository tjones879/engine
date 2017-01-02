#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>


GLSLProgram::GLSLProgram()
{
	linked = false;
	program = 0;
	logString = "";
}

/**
* Compiles a shader from a GLSL file path.
* @param fileName	The file path pointing to the shader file.
* @param type		The type of GLSL shader to be compiled.
* @return openGL handle to the shader. This value is GL_FALSE if there was a compilation or creation error. @see logString 
* @see compileShaderFromString()
*/
GLuint GLSLProgram::compileShaderFromFile(const char* fileName, GLSLShader::ShaderType type)
{
	if (!fileExists(fileName))
	{
		logger.addMessage(Log::SHADER, LOG_TAG, "Shader file path not found");
		logger.write();
		return GL_FALSE;
	}
	return compileShaderFromString(loadShaderAsString(fileName), type);
}

/**
* Compiles a shader from a std::string containing GLSL source code.
* @param fileName	The file path pointing to the shader file.
* @param type		The type of GLSL shader to be compiled.
* @return openGL handle to the shader. This value is GL_FALSE if there was a compilation or creation error. @see logString 
*/
GLuint GLSLProgram::compileShaderFromString(const std::string& source, GLSLShader::ShaderType type)
{
	GLuint shader = glCreateShader(type);
	if (shader == GL_FALSE)
	{
		getShaderLog(shader);
		return shader;
	}

	const GLchar* shaderSource = source.c_str();
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint compileResult;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE)
	{
		getShaderLog(shader);
		return GL_FALSE;
	}

	readShaderUniforms();
	return shader;
}

bool GLSLProgram::link()
{
	GLint success;
	GLchar infoLog[512];
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (success)
	{
		linked = true;
		return true;
	}
	else
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		logString = std::string(infoLog);
		return false;
	}
}

void GLSLProgram::use()
{
	if (linked)
	glUseProgram(this->program);
}

std::string GLSLProgram::log()
{
	return logString;
}

GLuint GLSLProgram::glProgram()
{
	return program;
}

bool GLSLProgram::isLinked()
{
	return linked;
}

void GLSLProgram::bindAttribLocation(GLuint location, const char* name)
{
	if (!linked)
	{
		glBindAttribLocation(program, location, name);
	}
}

void GLSLProgram::bindFragDataLocation(GLuint location, const char* name)
{
	if (!linked)
	{
		glBindFragDataLocation(program, location, name);
	}
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, GLfloat x, GLfloat y, GLfloat z)
{
	glUniform3f(shaderUniform.glHandle(), x, y, z);
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, const glm::vec3& v)
{
	glUniform3f(shaderUniform.glHandle(), v.x, v.y, v.z);
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, const glm::vec4& v)
{
	glUniform4f(shaderUniform.glHandle(), v.x, v.y, v.z, v.w);
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, const glm::mat3& m)
{
	glUniformMatrix3fv(shaderUniform.glHandle(), 1, GL_FALSE, glm::value_ptr(m));
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, const glm::mat4& m)
{
	glUniformMatrix4fv(shaderUniform.glHandle(), 1, GL_FALSE, glm::value_ptr(m));
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, GLfloat val)
{
	glUniform1f(shaderUniform.glHandle(), val);
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, GLint val)
{
	glUniform1i(shaderUniform.glHandle(), val);
}

void GLSLProgram::setUniform(ShaderUniform shaderUniform, bool val)
{
	glUniform1i(shaderUniform.glHandle(), val);
}

ShaderUniform GLSLProgram::operator[](const GLchar* uniformName)
{
	return shaderUniforms[uniformName];
}

ShaderUniform GLSLProgram::operator[](const std::string uniformName)
{
	return shaderUniforms[uniformName];
}

std::map<std::string, ShaderUniform> GLSLProgram::getShaderUniforms()
{
	return shaderUniforms;
}

std::vector<VertexAttrib> GLSLProgram::getVertexAttribs()
{
	return vertexAttribs;
}

void GLSLProgram::printActiveAttribs()
{

}


// PRIVATE:

bool GLSLProgram::fileExists(const std::string& fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

const std::string GLSLProgram::loadShaderAsString(const char* fileName)
{
	std::ifstream shaderFile(fileName, std::ifstream::in);
	std::stringstream sstream;
	sstream << shaderFile.rdbuf();
	const std::string shaderString(sstream.str());
	return shaderString;
}

/**
* Obtains any information from the shader info log and adds it 
* to the logger and shader logString.
* 
* @param shader The openGL handle for the shader of interest.
*/
void GLSLProgram::getShaderLog(GLuint shader)
{
	GLint logLen;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0)
	{
		char* log = new char[logLen];
		glGetShaderInfoLog(shader, logLen, NULL, log);
		logString = std::string(log);
		delete[] log;
		logger.addMessage(Log::SHADER, LOG_TAG, logString);
		logger.write();
	}
}

void GLSLProgram::readShaderUniforms()
{
	GLint count;
	GLchar name[16];
	GLenum type;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &count);
	for (auto i = 0; i < count; i++)
	{
		glGetActiveUniform(program, (GLuint)i, 16, NULL, NULL, &type, name);
		shaderUniforms.insert(std::pair<std::string, ShaderUniform>(std::string(name), ShaderUniform(i, type)));
	}
}
