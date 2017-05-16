#pragma once
#include "GL/glew.h"
#include <glm/glm.hpp>

class Shader
{
public:
	Shader();

	void CompileFromFile(const char* vertexSourchPath, const char* fragmentSourcePath);

	//Bind the Program
	void Bind() const;
	//Unbind the program
	void Unbind();

	//Get the location of a uniform using the uniforms name within the shader.
	GLint GetUniformLocationByName(const GLchar* uniformName) const;

	//Set a float value for a uniform variable within a shader
	void SetUniform(const GLchar* uniformName, GLfloat value) const;
	//Set a vec2 value for a uniform variable within a shader
	void SetUniform(const GLchar* uniformName, glm::vec2 value) const;
	//Set a vec3 value for a uniform variable within a shader
	void SetUniform(const GLchar* uniformName, glm::vec3 value) const;
	//Set a vec4 value for a uniform variable within a shader
	void SetUniform(const GLchar* uniformName, glm::vec4 value) const;
	//Set a mat2 value for a uniform variable within a shader
	void SetUniform(const GLchar* uniformName, glm::mat2 value, GLint count, GLboolean transpose) const;
	//Set a mat3 value for a uniform variable within a shader
	void SetUniform(const GLchar* uniformName, glm::mat3 value, GLint count, GLboolean transpose) const;
	//Set a mat4 value for a uniform variable within a shader
	void SetUniform(const GLchar* uniformName, glm::mat4 value, GLint count, GLboolean transpose) const;

	GLuint GetProgramID() const;

private:
	// The program ID
	void compile();
	GLuint program;
};
