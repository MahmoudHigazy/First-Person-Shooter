#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::LoadProgram()
{
	programID = LoadShaders("model.vertexshader", "model.fragmentshader");

	modelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	vpMatrixID = glGetUniformLocation(programID, "VP");
	clipID = glGetUniformLocation(programID, "clip");
	AmbientLightID = glGetUniformLocation(programID, "ambientLight");
	LightPositionID = glGetUniformLocation(programID, "lightPosition");
	EyePositionID = glGetUniformLocation(programID, "eyePosition");

	glm::vec4 p(0, 0, 0, 0);

	glUniform4fv(clipID, 1, &p[0]);
}

void ShaderProgram::BindModelMatrix(GLfloat* value)
{
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, value);
}

void ShaderProgram::BindClipPlane(GLfloat* value)
{
	glUniform4fv(clipID, 1, value);
}

void ShaderProgram::BindVPMatrix(GLfloat* value)
{
	glUniformMatrix4fv(vpMatrixID, 1, GL_FALSE, value);
}

void ShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

void ShaderProgram::BindAmbientLight(GLfloat* value) {
	glUniform3fv(AmbientLightID, 1, value);
}

void ShaderProgram::BindLightPosition(GLfloat* value) {
	glUniform3fv(LightPositionID, 1, value);
}

void ShaderProgram::BindEyePosition(GLfloat* value) {
	glUniform3fv(EyePositionID, 1, value);
}

void ShaderProgram::CleanUp()
{
	glDeleteProgram(programID);
}