#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "level.h"
#include "CollisionCheck.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "player.h"

#include "ui.h"
// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN,
    GAME_QUIT,
    GAME_PAUSE
};

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    UI* ui;
    // game state
    GameState               State;
    bool                    Keys[1024];
    unsigned int            Width, Height;
    // constructor/destructor
    GameLevel* level;
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt,GLFWwindow* window);
    void Update(float dt);
    void Render(ImTextureID);
};

#endif