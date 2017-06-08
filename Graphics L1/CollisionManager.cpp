#include "CollisionManager.h"

void CollisionManager::SetCollidableModels(vector<CollidableModel*> fCollidableModels)
{
	CollidableModels = fCollidableModels;
}

void CollisionManager::AddCollidableModel(CollidableModel * model)
{
	CollidableModels.push_back(model);
}

void CollisionManager::RemoveCollidableModel(int modelIndex)
{
	CollidableModels.erase(CollidableModels.begin()+modelIndex);
}

void CollisionManager::RemoveCollidableModel(CollidableModel * model)
{
	CollidableModels.erase(find(CollidableModels.begin(),CollidableModels.end(),model));
}

bool CollisionManager::UpdateCollisions()
{
	bool GunCollided = false;
	for (int i = 0;i < CollidableModels.size();i++) {
		for (int j = i + 1;j < CollidableModels.size();j++) {
			if(CollidableModels[i]->GetBoundingBox().IsIntersecting(CollidableModels[j]->GetBoundingBox())){
				CollidableModel::ObjectType x = CollidableModels[i]->objectType;
				CollidableModel::ObjectType y = CollidableModels[j]->objectType;
				CollidableModels[i]->Collided(y);
				CollidableModels[j]->Collided(x);
				if ((x == 3 &&( y == 1||y==6) ||  ((x == 6||x==1) && y == 3)))
				{
					GunCollided = true;
				}
			}
		}
	}
	return GunCollided;
}