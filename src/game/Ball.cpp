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
    constexpr int half_forward_arc = kForwardArcAngle / 2;

    if (GetRandomValue(0, 1) == 0)
    {
        angle = GetRandomValue(180 - half_forward_arc, 180 + half_forward_arc);
    }
    else
    {
        angle = GetRandomValue(-half_forward_arc, half_forward_arc);
    }

    return DegreesToRadians(static_cast<float>(angle));
}
} // namespace

Ball::Ball()
    : m_Position{static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2},
      m_Radius{kFixedBallRadius},
      m_Color{YELLOW}
{
    const float initial_angle = GetInitialRandomAngle();
    m_Velocity = Vector2{kFixedBallSpeedFactor * cos(initial_angle), kFixedBallSpeedFactor * sin(initial_angle)};
}

void Ball::Draw() const
{
    DrawCircleV(m_Position, m_Radius, m_Color);
}

void Ball::ProcessMovement()
{
    if (IsKeyPressed(KEY_SPACE) && m_Frozen)
    {
        SoundManager::Instance()->StopScore();
        SoundManager::Instance()->PlayWhistle();
        m_Frozen = false;
    }

    if (!m_Frozen)
    {
        const raylib::Vector2 delta_velocity = {m_Velocity.x * GetFrameTime(), m_Velocity.y * GetFrameTime()};

        if (m_ScreenEdgeCollision)
        {
            SoundManager::Instance()->PlayBorderHit();
            m_Velocity.y *= -1.0f;
            m_ScreenEdgeCollision = false;
        }
        if (m_PaddleSideCollision)
        {
            SoundManager::Instance()->PlayPaddleHit();
            m_Velocity.x *= -1.0f;
            m_PaddleSideCollision = false;
        }
        if (m_PaddleTBCollision)
        {
            SoundManager::Instance()->PlayPaddleHit();
            m_Velocity.y *= -1.0f;
            m_PaddleTBCollision = false;
            m_CollideWithPaddleEnabled = true;
        }

        m_Position += delta_velocity;
    }
}

void Ball::CheckBorderCollision()
{
    const double delta_velocity_y = m_Velocity.y * GetFrameTime();

    // collide with bottom border
    if (m_Position.y + m_Radius + delta_velocity_y >= GetScreenHeight())
    {
        m_ScreenEdgeCollision = true;
    }

    // collide with top border
    if (m_Position.y - m_Radius + delta_velocity_y < 0)
    {
        m_ScreenEdgeCollision = true;
    }
}

void Ball::CheckPaddleCollision(const Paddle& p)
{
    const raylib::Vector2 delta_velocity{m_Velocity.x * GetFrameTime(), m_Velocity.y * GetFrameTime()};

    const float ball_x = m_Position.x + delta_velocity.x;
    const float ball_y = m_Position.y + delta_velocity.y;
    const float paddle_left_side = p.GetPosition().x;
    const float paddle_right_side = p.GetPosition().x + p.GetSize().x;
    const float paddle_top_side = p.GetPosition().y;
    const float paddle_bottom_side = p.GetPosition().y + p.GetSize().y;

    const float test_x = std::clamp(ball_x, paddle_left_side, paddle_right_side);
    const float test_y = std::clamp(ball_y, paddle_top_side, paddle_bottom_side);

    const float dist_x = ball_x - test_x;
    const float dist_y = ball_y - test_y;

    if (const float distance = sqrt(dist_x * dist_x + dist_y * dist_y); distance <= m_Radius)
    {
        if (dist_y == 0.0f)
        {
            m_PaddleSideCollision = true;
        }
        else
        {
            m_PaddleTBCollision = true;
        }
    }
}
