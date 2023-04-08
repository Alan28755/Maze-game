#include "game.h"
#include "list.h"
// Game-related State data
SpriteRenderer* Renderer;
Player* player;
GameLevel* level;
collisionCheck* col;
const glm::vec3 PLAYER_SIZE(64, 64, 1);
const GLfloat PLAYER_VELOCITY(150.f);
float lastX = 0, lastY = 0;
GameObject* playerBox;


static ImVec2 helpPos;
static ImVec2 helpSize;


Game::Game(unsigned int width, unsigned int height)
	: State(GAME_MENU), Keys(), Width(width), Height(height)
{

}
static int mazeSize=9;
Game::~Game()
{
	delete Renderer;
	delete player;
}

void Game::Init()
{


	// load shaders
	ResourceManager::LoadShader("sprite_color.vert", "sprite_color.frag", nullptr, "sprite");
	// configure shaders
	ResourceManager::GetShader("sprite").Use();

	float x = static_cast<float>(this->Width) / 2.f;
	float y = static_cast<float>(this->Height) / 2.f;
	glm::mat4 projection = glm::ortho(-x, x,
		-y, y, -32.0f, 32.0f);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("sprite").SetInteger("image", 0);

	/*glm::mat4 poj = glm::perspective(glm::radians(45.0f), (float)this->Width / (float)this->Height, 0.1f, 100.0f);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", poj);*/




	// set render-specific controls
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	// load textures
	ResourceManager::LoadTexture("1.png", true, "block");
	ResourceManager::LoadTexture("2.png", true, "way");
	ResourceManager::LoadTexture("bg2.png", true, "bg");



	glm::vec3 pos = glm::vec3(64.0f, 64.0f, -5.2f);

	//glm::vec3 pos = glm::vec3(this->Width / 2 - PLAYER_SIZE.x / 2, 0.0f, 0.0f);
	player = new Player(pos, PLAYER_SIZE, 4, 0.18f, Dir::Down);
	/*Player& p = *player;
	printf("%f\n", p.time);
	printf("%d\n", p.dir);
	printf("%d\n", p.Tex_nur);
	printf("%f\n", p.ve);
	printf("%d\n", p.currentframe);
	printf("%f %f %f\n", p.Position.x, p.Position.y, p.Position.z);
	printf("%f %f %f\n", p.Size.x, p.Size.y, p.Size.z);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d ", p.Tex[i][j].Width);
		}
		printf("\n");
	}
	printf("-------------------------------------\n");*/

	playerBox = new GameObject(glm::vec3(6, 0, 0) + pos, glm::vec3(52.f, 52.f, 1.f));
	level = new GameLevel();
	//level->Load("map.txt", this->Width, this->Height);
	col = new collisionCheck();
}

void Game::ProcessInput(float dt, GLFWwindow* window)
{
	switch (State)
	{
	case GAME_ACTIVE:
	{
		float velocity = PLAYER_VELOCITY * dt;
		// Move playerboard
		if (ImGui::IsKeyDown(ImGuiKey_A))
		{
			//if (player->Position.x >= 0)
			player->Position.x -= velocity;
			player->isIdle[Dir::Left] = false;
			player->dir = Dir::Left;
		}
		if (ImGui::IsKeyDown(ImGuiKey_D))
		{
			//if (player->Position.x <= this->Width - player->Size.x)
			player->Position.x += velocity;
			player->isIdle[Dir::Right] = false;
			player->dir = Dir::Right;

		}
		if (ImGui::IsKeyDown(ImGuiKey_W))
		{
			//if (player->Position.y <= this->Height - player->Size.y)
			player->Position.y += velocity;
			player->isIdle[Dir::Up] = false;
			player->dir = Dir::Up;

		}
		if (ImGui::IsKeyDown(ImGuiKey_S))
		{
			//if (player->Position.y >=0)
			player->Position.y -= velocity;
			player->isIdle[Dir::Down] = false;
			player->dir = Dir::Down;

		}
		if (ImGui::IsKeyReleased(ImGuiKey_A))
		{
			player->isIdle[Dir::Left] = true;
		}
		if (ImGui::IsKeyReleased(ImGuiKey_D))
		{
			player->isIdle[Dir::Right] = true;
		}
		if (ImGui::IsKeyReleased(ImGuiKey_W))
		{
			player->isIdle[Dir::Up] = true;
		}
		if (ImGui::IsKeyReleased(ImGuiKey_S))
		{
			player->isIdle[Dir::Down] = true;
		}
		if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			State = GameState::GAME_PAUSE;
		}
		break;
	}
	case GAME_MENU:
		if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			State = GameState::GAME_QUIT;
		}
		break;
	case GAME_WIN:
		break;
	case GAME_QUIT:
		*this->ui->isopen = false;
		break;
	case GAME_PAUSE:
		if (ImGui::IsKeyPressed(ImGuiKey_Escape))
		{
			State = GameState::GAME_ACTIVE;
		}
		break;
	default:
		break;
	}
}

void Game::Update(float dt)
{
	switch (State)
	{
	case GAME_ACTIVE:
	{
		player->updata(dt);
		playerBox->Position = player->Position + glm::vec3(6.f, 0.f, 0.f);
		for (GameObject tile : level->tiles)
		{
			if (tile.IsSolid)
			{
				if (col->CheckCollision(tile, *playerBox))
				{
					//glm::vec2 v = col->ColLen(tile, *player);
					player->Position.x = lastX;
					player->Position.y = lastY;
					//printf("%f %f\n", v.x, v.y);
					/*player->Position.x -= v.x;
					player->Position.y -= v.y;*/
				}

			}
		}
		lastX = player->Position.x;
		lastY = player->Position.y;
		helpPos.x = glm::clamp(player->Position.x + PLAYER_SIZE.x * 0.5, this->Width * 0.5, mazeSize * 64 - this->Width * 0.5);
		helpPos.y = glm::clamp(player->Position.y + PLAYER_SIZE.y * 0.5, this->Height * 0.5, mazeSize * 64 - this->Height * 0.5);

		glm::mat4 view = glm::lookAt(glm::vec3(helpPos.x,helpPos.y,10), \
			glm::vec3(helpPos.x, helpPos.y, 10) + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ResourceManager::GetShader("sprite").SetMatrix4("view", view);
		if (player->Position.x >= (mazeSize - 2) * 64 && player->Position.y >= (mazeSize - 2) * 64)
		{
			State = GAME_WIN;
		}
		break;
	}
	case GAME_MENU:
		break;
	case GAME_WIN:
		break;
	case GAME_QUIT:
		break;
	default:
		break;
	}
	
}

void Game::Render(ImTextureID framebuffer)
{
	ImGui::Begin(u8"迷宫游戏", this->ui->isopen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize({ (float)this->Width,(float)this->Height });

	switch (State)
	{
	case GAME_ACTIVE:
	{
		level->Draw(*Renderer);
		player->Draw(*Renderer);
		helpPos = ImGui::GetCursorPos();
		//ImGui::SetCursorPos({ 0,0 });
		ImGui::Image(framebuffer, ImGui::GetContentRegionAvail(), { 0,1 }, { 1,0 });
		break;
	}
	case GAME_MENU:
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 8,20 });

		helpPos = ImGui::GetCursorPos();
		ImGui::Image((GLuint*)ResourceManager::GetTexture("bg").ID, ImGui::GetContentRegionAvail(), {0,1}, {1,0});
		ImGui::SetCursorPos(helpPos);


		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {});
		ImGui::PushStyleColor(ImGuiCol_Button, {});
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, {});
		ImGui::PushFont(ui->fonts["big"]);
		helpSize = { 64 * 4,64 };
		ImGui::SetCursorPosX((float)((this->Width - helpSize.x) / 2.f));
		//ImGui::Text(u8"随机迷宫");
		

		ImGui::Button(u8"随机迷宫",helpSize);
		ImGui::SetCursorPosY(150);
		ImGui::PushFont(ui->fonts["middle"]);
		helpSize = { 36 * 11,36 };
		ImGui::SetCursorPosX((float)((this->Width - helpSize.x) / 2.f));
		ImGui::Button(u8"请在下方输入迷宫的维数", helpSize);

		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		
		ImGui::PushItemWidth(100);
		ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.26f, 0.59f, 0.98f, 0.67f });
		ImGui::SetCursorPosX((float)((this->Width - 100) / 2.f));
		ImGui::DragInt("", &mazeSize,1,9,49);
		ImGui::PopStyleColor();
		if (mazeSize % 2 == 0)
		{
			mazeSize++;
		}
		ImGui::PopItemWidth();
		ImGui::PopFont();


		//ImGui::PushFont(ui->fonts["big"]);
		helpSize = { 60 * 4,60 };
		ImGui::SetCursorPosX((float)((this->Width - helpSize.x) / 2.f));
		if (ImGui::Button(u8"开始游戏",helpSize))
		{
			State = GAME_ACTIVE;
			level->LoadFromBulid(mazeSize);
		}
		ImGui::PopFont();
		ImGui::PopStyleVar();
	}
		break;
	case GAME_WIN:
		level->Draw(*Renderer);
		player->Draw(*Renderer);
		helpPos = ImGui::GetCursorPos();
		ImGui::Image(framebuffer, ImGui::GetContentRegionAvail(), { 0,1 }, { 1,0 });
		helpSize = { 200,300 };
		helpPos.x = (this->Width - helpSize.x) / 2;
		helpPos.y = (this->Height - helpSize.y) / 2;
		ImGui::SetCursorPos(helpPos);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 1,1,1,0.5 });
		ImGui::BeginChild("", helpSize, true);
		ImGui::SetCursorPos({ 0,0 });
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 4+10);
		ImGui::SetCursorPosY(ImGui::GetContentRegionAvail().y / 4);
		ImGui::PushFont(ui->fonts["middle"]);
		ImGui::TextColored({ 1,0,1,1 }, u8"你赢了！");
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 4);
		if (ImGui::Button(u8"退出游戏"))
		{
			State = GAME_QUIT;
		}
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 4);
		if (ImGui::Button(u8"再玩一遍"))
		{
			State = GAME_ACTIVE;
			level->clearLevel();
			player->Position = glm::vec3(64.0f, 64.0f, -5.2f);
			player->dir = Dir::Down;
			level->LoadFromBulid(mazeSize);
		}
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 4);
		if (ImGui::Button(u8"返回标题"))
		{
			State = GAME_MENU;
			level->clearLevel();
			player->Position = glm::vec3(64.0f, 64.0f, -5.2f);
			player->dir = Dir::Down;
		}
		ImGui::PopFont();
		ImGui::EndChild();
		ImGui::PopStyleColor();
		break;
	case GAME_QUIT:
		break;
	case GAME_PAUSE:
		level->Draw(*Renderer);
		player->Draw(*Renderer);
		helpPos = ImGui::GetCursorPos();
		ImGui::Image(framebuffer, ImGui::GetContentRegionAvail(), { 0,1 }, { 1,0 });
		helpSize = { 200,300 };
		helpPos.x = (this->Width - helpSize.x)/2;
		helpPos.y = (this->Height - helpSize.y) / 2;
		ImGui::SetCursorPos(helpPos);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 1,1,1,0.5 });
		ImGui::BeginChild("", helpSize, true);
		ImGui::SetCursorPos({0,0});
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 4);
		ImGui::SetCursorPosY(ImGui::GetContentRegionAvail().y / 4);
		ImGui::PushFont(ui->fonts["middle"]);
		if (ImGui::Button(u8"退出游戏"))
		{
			State = GAME_QUIT;
		}
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 4);
		if (ImGui::Button(u8"返回游戏"))
		{
			State = GAME_ACTIVE;
		}
		ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x / 4);
		if (ImGui::Button(u8"返回标题"))
		{
			State = GAME_MENU;
			level->clearLevel();
			player->Position = glm::vec3(64.0f, 64.0f, -5.2f);
			player->dir = Dir::Down;
		}
		ImGui::PopFont();
		ImGui::EndChild();
		ImGui::PopStyleColor();
		break;
	default:
		break;
	}

	

	ImGui::End();

}

