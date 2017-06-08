#ifndef GraphicsDevice_h__
#define GraphicsDevice_h__

#include "../../middleware/includes/gl/glew.h"
#include "../../middleware/includes/glm/glm.hpp"
#include "Shaders/shader.hpp"


class ShaderProgram
{
public:
	GLuint programID;

	GLuint modelMatrixID;
	GLuint vpMatrixID;
	GLuint clipID;
	GLuint AmbientLightID;
	GLuint LightPositionID;
	GLuint EyePositionID;

	ShaderProgram();
	~ShaderProgram();

	void BindModelMatrix(GLfloat* value);
	void BindClipPlane(GLfloat* value);
	void BindVPMatrix(GLfloat* value);
	void BindAmbientLight(GLfloat* value);
	void BindLightPosition(GLfloat* value);
	void BindEyePosition(GLfloat* value);

	//calls glUseProgram.
	void UseProgram();
	//load shaders from files.
	void LoadProgram();
	void CleanUp();
};

#endif // GraphicsDevice_h__