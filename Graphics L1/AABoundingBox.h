#pragma once
#include <vector>
#include "../../middleware/includes/glm/glm.hpp"
#include "../../middleware/includes/gl/glew.h"
#include"../middleware/includes/glm/glm.hpp"
#include"../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

class AABoundingBox {
	glm::vec3 center;
	glm::vec3 size;
	glm::vec3 halfSize;
	glm::vec3 minCoord, maxCoord;

public:
	AABoundingBox();
	AABoundingBox(glm::vec3 fMinCoord, glm::vec3 fMaxCoord);
	glm::vec3 GetCenter();
	glm::vec3 GetHalfSize();
	bool IsIntersecting(AABoundingBox box);
	void Transform(glm::mat4 translation);
};