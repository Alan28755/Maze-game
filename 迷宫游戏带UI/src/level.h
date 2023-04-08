#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

#include"maze_builder.h"

/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.

class GameLevel
{
public:
    // level state
    std::vector<GameObject> tiles;
    // constructor
    GameLevel();
    // loads level from file
    void LoadFromFile(const char* file);
    void LoadFromBulid(int n);

    // render level
    void Draw(SpriteRenderer& renderer);

    void clearLevel();
    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData);
};

#endif