//
// Created by Luis on 08/04/2021.
//

#include "ball.h"
#include "SoundManager.h"

#include <algorithm>

namespace
{
constexpr int forwardArcAngle = 110;
constexpr float fixedBallRadius = 15.0f;
constexpr float fixedBallSpeedFactor = 530.0;

float DegreesToRadians(const float angle)
{
    return angle * DEG2RAD;
}

float GetInitialRandomAngle()
{
    int angle;
    constexpr int halfForwardArc = forwardArcAngle / 2;

    if (GetRandomValue(0, 1) == 0)
    {
        angle = GetRandomValue(180 - halfForwardArc, 180 + halfForwardArc);
    }
    else
    {
        angle = GetRandomValue(-halfForwardArc, halfForwardArc);
    }

    return DegreesToRadians(static_cast<float>(angle));
}
} // namespace

Ball::Ball()
    : mPosition{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2},
      mRadius{fixedBallRadius},
      mColor{YELLOW}
{
    const float initialAngle = GetInitialRandomAngle();
    mVelocity = Vector2{fixedBallSpeedFactor * cos(initialAngle), fixedBallSpeedFactor * sin(initialAngle)};
}

void Ball::Draw() const
{
    DrawCircleV(mPosition, mRadius, mColor);
}

void Ball::ProcessMovement()
{
    if (IsKeyPressed(KEY_SPACE) && mFrozen)
    {
        SoundManager::instance()->stopScore();
        SoundManager::instance()->playWhistle();
        mFrozen = false;
    }

    if (!mFrozen)
    {
        const raylib::Vector2 deltaVelocity = {mVelocity.x * GetFrameTime(), mVelocity.y * GetFrameTime()};

        if (mScreenEdgeCollision)
        {
            SoundManager::instance()->playBorderHit();
            mVelocity.y *= -1.0f;
            mScreenEdgeCollision = false;
        }
        if (mPaddleSideCollision)
        {
            SoundsPlayPaddleHit();
            mVelocity.x *= -1.0f;
            mPaddleSideCollision = false;
        }
        if (mPaddleTBCollision)
        {
            SoundManager::instance()->playPaddleHit();
            mVelocity.y *= -1.0f;
            mPaddleTBCollision = false;
            mCollideWithPaddleEnabled = true;
        }

        mPosition += deltaVelocity;
    }
}

void Ball::CheckBorderCollision()
{
    const double velocityY = mVelocity.y * GetFrameTime();

    // collide with bottom border
    if (mPosition.y + mRadius + velocityY >= GetScreenHeight())
    {
        mScreenEdgeCollision = true;
    }

    // collide with top border
    if (mPosition.y - mRadius + velocityY < 0)
    {
        mScreenEdgeCollision = true;
    }
}

void Ball::CheckPaddleCollision(const Paddle *p)
{
    const float velocityX = mVelocity.x * GetFrameTime();
    const float velocityY = mVelocity.y * GetFrameTime();

    const float ballX = mPosition.x + velocityX;
    const float ballY = mPosition.y + velocityY;
    const float paddleLeftSide = p->m_position().x;
    const float paddleRightSide = p->m_position().x + p->m_size().x;
    const float paddleTopSide = p->m_position().y;
    const float paddleBottomSide = p->m_position().y + p->m_size().y;

    const float testX = std::clamp(ballX, paddleLeftSide, paddleRightSide);
    const float testY = std::clamp(ballY, paddleTopSide, paddleBottomSide);

    const float distX = ballX - testX;
    const float distY = ballY - testY;

    if (const float distance = sqrt(distX * distX + distY * distY); distance <= mRadius)
    {
        if (distY == 0.0f)
        {
            mPaddleSideCollision = true;
        }
        else
        {
            mPaddleTBCollision = true;
        }
    }
}
