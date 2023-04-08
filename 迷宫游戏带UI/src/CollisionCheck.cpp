#include"CollisionCheck.h"
bool collisionCheck::CheckCollision(GameObject& p, GameObject& o)
{
    // x轴方向碰撞？
    bool collisionX = p.Position.x + p.Size.x > o.Position.x &&
        o.Position.x + o.Size.x > p.Position.x;
    // y轴方向碰撞？
    bool collisionY = p.Position.y + p.Size.y > o.Position.y &&
        o.Position.y + o.Size.y > p.Position.y;
    // 只有两个轴向都有碰撞时才碰撞
    return collisionX && collisionY;
}

glm::vec2 collisionCheck::ColLen(GameObject& p, GameObject& o)
{
    float x = std::min(p.Position.x + p.Size.x - o.Position.x, o.Position.x + o.Size.x - p.Position.x);
    float y = std::min(p.Position.y + p.Size.y - o.Position.y, o.Position.y + o.Size.y - p.Position.y);

    return glm::vec2(x,y);
}


