#include "AABoundingBox.h"

AABoundingBox::AABoundingBox()
{
}

AABoundingBox::AABoundingBox(glm::vec3 fMinCoord, glm::vec3 fMaxCoord) {
	minCoord = fMinCoord;
	maxCoord = fMaxCoord;
	center = (fMaxCoord+fMinCoord);
	center /= 2.0f;
	size = glm::abs(fMaxCoord - fMinCoord);
	halfSize = glm::vec3(size.x / 2.0f, size.y / 2.0f, size.z / 2.0f);
}

glm::vec3  AABoundingBox::GetCenter() {
	return center;
}

glm::vec3 AABoundingBox::GetHalfSize() {
	return halfSize;
}

bool AABoundingBox::IsIntersecting(AABoundingBox box) {
	glm::vec3  difference = glm::abs(center - box.GetCenter());
	glm::vec3 addedSize = halfSize + box.GetHalfSize();
	if (difference.x <= addedSize.x && difference.y <= addedSize.y && difference.z <= addedSize.z) {
		return true;
	}
	return false;
}

void AABoundingBox::Transform(glm::mat4 transformation) {
	glm::vec4 temp = glm::vec4(minCoord, 1);
	temp = transformation*temp;
	glm::vec4 temp2 = glm::vec4(maxCoord, 1);
	temp2 = transformation*temp2;
	center = (glm::vec3(temp + temp2));
	center /= 2.0f;
	size = glm::vec3(glm::abs(temp2 - temp));
	halfSize = size;
	halfSize /= 2.0f;
}