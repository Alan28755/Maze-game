#include "level.h"

#include <fstream>
#include <sstream>
char c[50][50];



GameLevel::GameLevel()
{

}
void GameLevel::LoadFromBulid(int n)
{
    char* map[50];
    for (int i = 0; i < 50; i++)
    {
        map[i] = &c[i][0];
    }
    memset(c, 0, sizeof(c));
    buildMaze(map, n);

    std::vector<std::vector<unsigned int>> tileData;
    tiles.clear();
    for (int i = 0; i < n; i++)
    {
        std::vector<unsigned int> row;
        for (int j = 0; j < n; j++)
        {
            row.push_back(map[i][j]);
        }
        tileData.push_back(row);
    }
    if (tileData.size() > 0)
        this->init(tileData);
}

void GameLevel::LoadFromFile(const char* file)
{

    // clear old data

    tiles.clear();
    // load from file
    
    unsigned int tileCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;

    if (fstream)
    {

        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }

        if (tileData.size() > 0)
            this->init(tileData);
    }
}

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& tile : this->tiles)
    {
        if (!tile.Destroyed)
            tile.Draw(renderer);
    }
    
}

void GameLevel::clearLevel()
{
    memset(c, 0, sizeof(c));
    tiles.clear();
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile:this->tiles)
    {
        if (!tile.IsSolid && !tile.Destroyed)
            return false;
    }
    
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData)
{

    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = 64.f, unit_height = 64.f;
    // initialize level tiles based on tileData	
    for (unsigned int i = 0; i < height; i++)
    {
        for (unsigned int j = 0; j < width; j++)
        {
            //printf("%d ", tileData[i][j]);
            // check block type from level data (2D level array)
            glm::vec3 pos(unit_width * j, unit_width * (height - 1 - i), -7.0f);

            glm::vec3 size(unit_width, unit_height,1.0f);
            if (tileData[i][j] == 0)
            {

                GameObject o(pos, size, ResourceManager::GetTexture("block"));
                o.IsSolid = true;
                this->tiles.push_back(o);
                

            }
            else if (tileData[i][j] == 1)
            {
                GameObject o(pos, size, ResourceManager::GetTexture("way"));
                o.IsSolid = false;
                this->tiles.push_back(o);


            }
        }
        //printf("\n");

    }
}