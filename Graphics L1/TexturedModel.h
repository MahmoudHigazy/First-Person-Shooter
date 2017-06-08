#ifndef TexturedModel_h__
#define TexturedModel_h__

#include "../../middleware/includes/glm/glm.hpp"
#include <vector>
#include "../../middleware/includes/gl\glew.h"
#include "texture.h"
#include "ShaderProgram.h"
#include "Model.h"

class TexturedModel : public Model
{
	
public:
	TexturedModel();
	~TexturedModel();
	Texture* texture;
	 void Draw();
};
#endif // Model_h__

