//
// Created by Luis on 08/04/2021.
//

#ifndef RAY_PONG_C_SRC_ENTITIES_BALL_H_
#define RAY_PONG_C_SRC_ENTITIES_BALL_H_

#include "paddle.h"
#include "raylib-cpp.hpp"

class Ball
{
public:
    Ball();

    void Draw() const;
    void ProcessMovement();
    void CheckBorderCollision();
    void CheckPaddleCollision(const Paddle *p);

    [[nodiscard]] raylib::Vector2 m_position() const
    {
        return mPosition;
    }

    [[nodiscard]] float m_radius() const
    {
        return mRadius;
    }

    [[nodiscard]] bool m_collide_with_paddle_enabled() const
    {
        return mCollideWithPaddleEnabled;
    }

private:
    raylib::Vector2 mPosition;
    float mRadius;
    raylib::Color mColor;
    raylib::Vector2 mVelocity;
    bool mFrozen = true;
    bool mScreenEdgeCollision = false;
    bool mPaddleSideCollision = false;
    bool mPaddleTBCollision = false;
    bool mCollideWithPaddleEnabled = false;
};

#endif // RAY_PONG_C_SRC_ENTITIES_BALL_H_
