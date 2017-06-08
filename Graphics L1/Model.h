#ifndef Model_h__
#define Model_h__

#include "../../middleware/includes/glm/glm.hpp"
#include <vector>
#include "../../middleware/includes/gl/glew.h"

class Model
{
public:
	//VAO
	GLuint mVertexArrayObjectID;
	
	//VBOs
	GLuint mVertexDataBufferID;
	GLuint mColorDataBufferID;
	GLuint mIndicesDataBufferID;
	GLuint mUVDataBufferID;
	GLuint mNormalsBufferID;
	Model();
	~Model();

	std::vector<glm::vec3> VertexData;
	std::vector<glm::vec3> ColorData;
	std::vector<glm::vec2> UVData;
	std::vector<glm::vec3> NormalsData;
	std::vector<unsigned short> IndicesData;

	void Initialize();
	virtual void Update();
	virtual void Draw();
	virtual void DrawStrip();
	virtual void DrawWireFrame();
	void Cleanup();
};
#endif // Model_h__