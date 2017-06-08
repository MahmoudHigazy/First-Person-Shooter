#pragma once
#include "AABoundingBox.h"
#include <vector>

using namespace std;

class CollidableModel {
	AABoundingBox boundingBox;
public:
	enum ObjectType {
		Fruit,
		House,
		Enemy,
		Gun,
		Player,
		Bullet,
		Tree
	};
	ObjectType objectType;
	virtual void Collided(ObjectType fObjectType)=0;
	CollidableModel();
	void SetBoundingBox(AABoundingBox fBoundingBox);
	AABoundingBox GetBoundingBox();
	static AABoundingBox CalculateBoundingBox( vector <glm::vec3> vertices);
};