#pragma once
#include"resource_manager.h"
#include"sprite_renderer.h"
#include"game_object.h"
#include<vector>
enum Dir
{
	Down=0,
	Left,
	Right,
	Up
};
class Player :public GameObject
{
public:
	float time;
	Dir dir;//�泯״̬
	int Tex_nur;//һ����������֡
	float ve;//һ֡������
	bool isIdle[4];
	int currentframe;
	std::vector<Texture2D> Tex[4];
	Player();
	Player(glm::vec3 pos, glm::vec3 size, int tex, float v,\
		Dir d=Dir::Down
		, glm::vec3 color = glm::vec3(1.0f), \
		glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f),float t=0.0f);
	void updata(float dt);
	void Draw(SpriteRenderer& renderer);

private:
	void init();
};
