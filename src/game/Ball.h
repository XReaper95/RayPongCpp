//
// Created by Luis on 08/04/2021.
//

#ifndef RAY_PONG_C_SRC_ENTITIES_BALL_H_
#define RAY_PONG_C_SRC_ENTITIES_BALL_H_

#include "raylib-cpp.hpp"

class Paddle;

class Ball
{
public:
    Ball();

    void Draw() const;
    void ProcessMovement();
    void CheckBorderCollision();
    void CheckPaddleCollision(const Paddle& p);

    const raylib::Vector2& GetPosition() const
    {
        return m_position;
    }

    float GetRadius() const
    {
        return m_radius;
    }

    bool IsCollisionWithPaddleEnabled() const
    {
        return m_collideWithPaddleEnabled;
    }

private:
    raylib::Vector2 m_position;
    float m_radius;
    raylib::Color m_color;
    raylib::Vector2 m_velocity;
    bool m_frozen = true;
    bool m_screenEdgeCollision = false;
    bool m_paddleSideCollision = false;
    bool m_paddleTbCollision = false;
    bool m_collideWithPaddleEnabled = false;
};

#endif // RAY_PONG_C_SRC_ENTITIES_BALL_H_
