#pragma once

#include "CollidableModel.h"
#include <vector>

using namespace std;

class CollisionManager {


public:
	vector <CollidableModel*> CollidableModels;
	void SetCollidableModels(vector <CollidableModel*> fCollidableModels);
	void AddCollidableModel(CollidableModel* model);
	void RemoveCollidableModel(int modelIndex);
	void RemoveCollidableModel(CollidableModel* model);
	bool UpdateCollisions();

};