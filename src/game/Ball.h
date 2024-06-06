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

    raylib::Vector2 GetPosition() const
    {
        return m_Position;
    }

    float GetRadius() const
    {
        return m_Radius;
    }

    bool IsCollisionWithPaddleEnabled() const
    {
        return m_CollideWithPaddleEnabled;
    }

private:
    raylib::Vector2 m_Position;
    float m_Radius;
    raylib::Color m_Color;
    raylib::Vector2 m_Velocity;
    bool m_Frozen = true;
    bool m_ScreenEdgeCollision = false;
    bool m_PaddleSideCollision = false;
    bool m_PaddleTBCollision = false;
    bool m_CollideWithPaddleEnabled = false;
};

#endif // RAY_PONG_C_SRC_ENTITIES_BALL_H_
