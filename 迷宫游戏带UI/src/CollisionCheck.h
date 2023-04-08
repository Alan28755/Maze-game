#pragma once
#include"game_object.h"
#include<glm/glm.hpp>
#include<algorithm>
class collisionCheck
{
private:

public:
	static bool CheckCollision(GameObject& one, GameObject& two); // AABB - AABB collision
	static glm::vec2 ColLen(GameObject& one, GameObject& two);

};