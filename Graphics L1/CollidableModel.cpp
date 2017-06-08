#include "CollidableModel.h"

CollidableModel :: CollidableModel() {

}

void CollidableModel::SetBoundingBox(AABoundingBox fBoundingBox)
{
	boundingBox = fBoundingBox;
}

AABoundingBox CollidableModel::GetBoundingBox()
{
	return boundingBox;
}

AABoundingBox CollidableModel::CalculateBoundingBox(vector<glm::vec3> vertices)
{
	glm::vec3 minCoord = glm::vec3(9999, 9999, 9999), maxCoord = glm::vec3(-9999, -9999, -9999);
	for (int i = 0;i < vertices.size();i++) {
		for (int j = 0;j < 3;j++) {
			if (vertices[i][j] < minCoord[j]) {
				minCoord[j] = vertices[i][j];
			}
			if (vertices[i][j] > maxCoord[j]) {
				maxCoord[j] = vertices[i][j];
			}
		}
	}
	AABoundingBox temp(minCoord, maxCoord);
	return temp;
}