#include"player.h"
char pname[24], tname[24];
Player::Player()
	:Tex_nur(0), ve(0), dir(Dir::Down),time(0.0f)
{
	init();
}

Player::Player(glm::vec3 pos, glm::vec3 size,\
	int tex, float v, Dir d, glm::vec3 color, glm::vec3 velocity,float t)
	:Tex_nur(tex), ve(v), dir(d),time(t) ,GameObject(pos,size)
{
	init();
}

void Player::init()
{
	memset(isIdle, 0, sizeof(bool) * 4);
	isIdle[0] = true;
	currentframe = 0;
	for (int i = 0; i <4; i++)
	{
		for (int j = 1; j <= Tex_nur; j++)
		{
			sprintf_s(pname, "player/%d.png", i * 4 + j);
			Tex[i].push_back(ResourceManager::loadTextureFromFile(pname, true));
		}
	}
}
void Player::updata(float dt)
{
	time += dt;
	if (time >= ve)
	{
		time = 0.0f;
		currentframe++;
		currentframe %= Tex_nur;
	}
	if (isIdle[dir])
	{
		currentframe = 0;
	}
}
void Player::Draw(SpriteRenderer& renderer)
{
	
	renderer.DrawSprite(Tex[dir][currentframe],this->Position,this->Size,this->Rotation,this->Color);
}