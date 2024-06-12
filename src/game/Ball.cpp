//
// Created by Luis on 08/04/2021.
//

#include "Ball.h"
#include "Paddle.h"
#include "SoundManager.h"

#include <algorithm>

namespace
{
constexpr int kForwardArcAngle = 110;
constexpr float kFixedBallRadius = 15.0f;
constexpr float kFixedBallSpeedFactor = 530.0;

float DegreesToRadians(const float angle)
{
    return angle * DEG2RAD;
}

float GetInitialRandomAngle()
{
    int angle;
    constexpr int halfForwardArc = kForwardArcAngle / 2;

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
    : m_position{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2},
      m_radius{kFixedBallRadius},
      m_color{YELLOW}
{
    const float initialAngle = GetInitialRandomAngle();
    m_velocity = Vector2{kFixedBallSpeedFactor * cos(initialAngle), kFixedBallSpeedFactor * sin(initialAngle)};
}

void Ball::Draw() const
{
    DrawCircleV(m_position, m_radius, m_color);
}

void Ball::ProcessMovement()
{
    if (IsKeyPressed(KEY_SPACE) && m_frozen)
    {
        SoundManager::Instance()->StopScore();
        SoundManager::Instance()->PlayWhistle();
        m_frozen = false;
    }

    if (!m_frozen)
    {
        const raylib::Vector2 deltaVelocity = {m_velocity.x * GetFrameTime(), m_velocity.y * GetFrameTime()};

        if (m_screenEdgeCollision)
        {
            SoundManager::Instance()->PlayBorderHit();
            m_velocity.y *= -1.0f;
            m_screenEdgeCollision = false;
        }
        if (m_paddleSideCollision)
        {
            SoundManager::Instance()->PlayPaddleHit();
            m_velocity.x *= -1.0f;
            m_paddleSideCollision = false;
        }
        if (m_paddleTbCollision)
        {
            SoundManager::Instance()->PlayPaddleHit();
            m_velocity.y *= -1.0f;
            m_paddleTbCollision = false;
            m_collideWithPaddleEnabled = true;
        }

        m_position += deltaVelocity;
    }
}

void Ball::CheckBorderCollision()
{
    const double deltaVelocityY = m_velocity.y * GetFrameTime();

    // collide with bottom border
    if (m_position.y + m_radius + deltaVelocityY >= GetScreenHeight())
    {
        m_screenEdgeCollision = true;
    }

    // collide with top border
    if (m_position.y - m_radius + deltaVelocityY < 0)
    {
        m_screenEdgeCollision = true;
    }
}

void Ball::CheckPaddleCollision(const Paddle& p)
{
    const raylib::Vector2 deltaVelocity{m_velocity.x * GetFrameTime(), m_velocity.y * GetFrameTime()};

    const float ballX = m_position.x + deltaVelocity.x;
    const float ballY = m_position.y + deltaVelocity.y;
    const float paddleLeftSide = p.GetPosition().x;
    const float paddleRightSide = p.GetPosition().x + p.GetSize().x;
    const float paddleTopSide = p.GetPosition().y;
    const float paddleBottomSide = p.GetPosition().y + p.GetSize().y;

    const float testX = std::clamp(ballX, paddleLeftSide, paddleRightSide);
    const float testY = std::clamp(ballY, paddleTopSide, paddleBottomSide);

    const float distX = ballX - testX;
    const float distY = ballY - testY;

    if (const float distance = sqrt(distX * distX + distY * distY); distance <= m_radius)
    {
        if (distY == 0.0f)
        {
            m_paddleSideCollision = true;
        }
        else
        {
            m_paddleTbCollision = true;
        }
    }
}
