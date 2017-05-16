#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() {

}

void Shader::CompileFromFile(const char* vertexSourchPath, const char* fragmentSourcePath) {
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensures ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);
	try
	{
		// Open files
		vShaderFile.open(vertexSourchPath);
		fShaderFile.open(fragmentSourcePath);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar * fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders
	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];
	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// Print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// Print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// Shader Program
	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);
	// Print linking errors if any
	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	std::cout << "Shader '" << program << "' sucessfully compiled and linked\n";
}


void Shader::Bind() const
{
	glUseProgram(this->program);
}


void Shader::Unbind()
{
	glUseProgram(0);
}


GLint Shader::GetUniformLocationByName(const GLchar *uniformName) const {
	return glGetUniformLocation(program, uniformName);
}

void Shader::SetUniform(const GLchar *uniformName, GLfloat value) const {
	glUniform1f(GetUniformLocationByName(uniformName), value);
}

void Shader::SetUniform(const GLchar *uniformName, glm::vec2 value) const {
	glUniform2f(GetUniformLocationByName(uniformName), value.x, value.y);
}

void Shader::SetUniform(const GLchar *uniformName, glm::vec3 value) const {
	glUniform3f(GetUniformLocationByName(uniformName), value.x, value.y, value.z);
}

void Shader::SetUniform(const GLchar *uniformName, glm::vec4 value) const {
	glUniform4f(GetUniformLocationByName(uniformName), value.x, value.y, value.z, value.w);
}

void Shader::SetUniform(const GLchar *uniformName, glm::mat2 value, GLint count, GLboolean transpose) const {
	glUniformMatrix2fv(GetUniformLocationByName(uniformName), count, transpose, &value[0][0]);
}

void Shader::SetUniform(const GLchar *uniformName, glm::mat3 value, GLint count, GLboolean transpose) const {
	glUniformMatrix3fv(GetUniformLocationByName(uniformName), count, transpose, &value[0][0]);
}

void Shader::SetUniform(const GLchar *uniformName, glm::mat4 value, GLint count, GLboolean transpose) const {
	glUniformMatrix4fv(GetUniformLocationByName(uniformName), count, transpose, &value[0][0]);
}

GLuint Shader::GetProgramID() const {
	return this->program;
}