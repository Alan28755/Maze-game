#include"CollisionCheck.h"
bool collisionCheck::CheckCollision(GameObject& p, GameObject& o)
{
    // x�᷽����ײ��
    bool collisionX = p.Position.x + p.Size.x > o.Position.x &&
        o.Position.x + o.Size.x > p.Position.x;
    // y�᷽����ײ��
    bool collisionY = p.Position.y + p.Size.y > o.Position.y &&
        o.Position.y + o.Size.y > p.Position.y;
    // ֻ��������������ײʱ����ײ
    return collisionX && collisionY;
}

glm::vec2 collisionCheck::ColLen(GameObject& p, GameObject& o)
{
    float x = std::min(p.Position.x + p.Size.x - o.Position.x, o.Position.x + o.Size.x - p.Position.x);
    float y = std::min(p.Position.y + p.Size.y - o.Position.y, o.Position.y + o.Size.y - p.Position.y);

    return glm::vec2(x,y);
}


