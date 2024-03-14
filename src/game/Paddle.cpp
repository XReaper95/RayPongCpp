//
// Created by Luis on 05/04/2021.
//
#include "Paddle.h"

namespace
{
constexpr float paddleFixedHeight = 100.0f;
constexpr float paddleFixedWidth = 30.0f;
constexpr float paddleWidthMargin = 15.0f;
constexpr float paddleMovementFactor = 300.0f;
} // namespace

Paddle::Paddle(const std::string_view name, const raylib::Color color, const bool is_left_paddle)
    : m_Name{name},
      m_Size{paddleFixedWidth, paddleFixedHeight},
      m_Color{color},
      m_Score{0},
      m_KeyUp{is_left_paddle ? KEY_W : KEY_I},
      m_KeyDown{is_left_paddle ? KEY_S : KEY_K}
{
    m_Position = Vector2{
        is_left_paddle ? paddleWidthMargin
                       : static_cast<float>(GetScreenWidth()) - paddleWidthMargin - paddleFixedWidth,
        static_cast<float>(GetScreenHeight()) / 2 - paddleFixedHeight / 2};
}

void Paddle::reset()
{
    m_Position.y = static_cast<float>(GetScreenHeight()) / 2 - paddleFixedHeight / 2;
    m_Score = 0;
}

void Paddle::draw() const
{
    DrawRectangleV(m_Position, m_Size, m_Color);
}

void Paddle::processInput()
{
    if (IsKeyDown(m_KeyUp) && m_Position.y > 0.0f)
    { // UP
        m_Position.y -= paddleMovementFactor * GetFrameTime();
    }
    if (IsKeyDown(m_KeyDown) && m_Position.y + m_Size.y < static_cast<float>(GetScreenHeight()))
    { // Down
        m_Position.y += paddleMovementFactor * GetFrameTime();
    }
}

void Paddle::updateScore()
{
    m_Score++;
}
