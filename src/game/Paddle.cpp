//
// Created by Luis on 05/04/2021.
//

#include "Paddle.h"

namespace
{
constexpr float kPaddleFixedHeight = 100.0f;
constexpr float kPaddleFixedWidth = 30.0f;
constexpr float kPaddleWidthMargin = 15.0f;
constexpr float kPaddleMovementFactor = 300.0f;
} // namespace

Paddle::Paddle(const std::string_view name, const raylib::Color color, const bool is_left_paddle)
    : m_Name{name},
      m_Size{kPaddleFixedWidth, kPaddleFixedHeight},
      m_Color{color},
      m_Score{0},
      m_KeyUp{is_left_paddle ? KEY_W : KEY_I},
      m_KeyDown{is_left_paddle ? KEY_S : KEY_K}
{
    m_Position = Vector2{
        is_left_paddle ? kPaddleWidthMargin
                       : static_cast<float>(GetScreenWidth()) - kPaddleWidthMargin - kPaddleFixedWidth,
        static_cast<float>(GetScreenHeight()) / 2 - kPaddleFixedHeight / 2};
}

void Paddle::Reset()
{
    m_Position.y = static_cast<float>(GetScreenHeight()) / 2 - kPaddleFixedHeight / 2;
    m_Score = 0;
}

void Paddle::Draw() const
{
    DrawRectangleV(m_Position, m_Size, m_Color);
}

void Paddle::ProcessInput()
{
    // UP
    if (IsKeyDown(m_KeyUp) && m_Position.y + m_Size.y < static_cast<float>(GetScreenHeight()))
    {
        m_Position.y += kPaddleMovementFactor * GetFrameTime();
    }

    // Down
    if (IsKeyDown(m_KeyDown) && m_Position.y > 0.0f )
    {
        m_Position.y -= kPaddleMovementFactor * GetFrameTime();
    }
}

void Paddle::UpdateScore()
{
    m_Score++;
}
