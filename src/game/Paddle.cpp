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

Paddle::Paddle(const std::string_view name, const raylib::Color color, const bool isLeftPaddle)
    : m_name{name},
      m_size{kPaddleFixedWidth, kPaddleFixedHeight},
      m_color{color},
      m_score{0},
      m_keyUp{isLeftPaddle ? KEY_W : KEY_I},
      m_keyDown{isLeftPaddle ? KEY_S : KEY_K}
{
    m_position = Vector2{
        isLeftPaddle ? kPaddleWidthMargin
                       : static_cast<float>(GetScreenWidth()) - kPaddleWidthMargin - kPaddleFixedWidth,
        static_cast<float>(GetScreenHeight()) / 2 - kPaddleFixedHeight / 2};
}

void Paddle::Reset()
{
    m_position.y = static_cast<float>(GetScreenHeight()) / 2 - kPaddleFixedHeight / 2;
    m_score = 0;
}

void Paddle::Draw() const
{
    DrawRectangleV(m_position, m_size, m_color);
}

void Paddle::ProcessInput()
{
    // UP
    if (IsKeyDown(m_keyUp) && m_position.y + m_size.y < static_cast<float>(GetScreenHeight()))
    {
        m_position.y += kPaddleMovementFactor * GetFrameTime();
    }

    // Down
    if (IsKeyDown(m_keyDown) && m_position.y > 0.0f )
    {
        m_position.y -= kPaddleMovementFactor * GetFrameTime();
    }
}

void Paddle::UpdateScore()
{
    m_score++;
}
