#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state
    glm::vec3   Position, Size, Velocity;
    glm::vec3   Color;
    float       Rotation;
    bool        IsSolid;
    bool        Destroyed;
    // render state
    // constructor(s)
    GameObject();
    GameObject(glm::vec3 pos, glm::vec3 size, \
        Texture2D sprite, glm::vec3 color = glm::vec3(1.0f),\
        glm::vec3 velocity = glm::vec3(0.0f, 0.0f,0.0f));
    GameObject(glm::vec3 pos, glm::vec3 size, \
         glm::vec3 color = glm::vec3(1.0f), \
        glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f));
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);
private:
    Texture2D   Sprite;

};

#endif