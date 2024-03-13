//
// Created by Luis on 05/04/2021.
//
#include "paddle.h"

namespace
{
constexpr float paddleFixedHeight = 100.0f;
constexpr float paddleFixedWidth = 30.0f;
constexpr float paddleWidthMargin = 15.0f;
constexpr float paddleMovementFactor = 300.0f;
} // namespace

Paddle::Paddle(const std::string_view name, const raylib::Color color, const bool isLeftPaddle)
    : mName{name},
      mSize{paddleFixedWidth, paddleFixedHeight},
      mColor{color},
      mScore{0},
      mKeyUp{isLeftPaddle ? KEY_W : KEY_I},
      mKeyDown{isLeftPaddle ? KEY_S : KEY_K}
{
    mPosition = Vector2{
        isLeftPaddle ? paddleWidthMargin : static_cast<float>(GetScreenWidth()) - paddleWidthMargin - paddleFixedWidth,
        static_cast<float>(GetScreenHeight()) / 2 - paddleFixedHeight / 2};

    TraceLog(LOG_INFO, "%s position: {%f, %f}", mName.c_str(), mPosition.x, mPosition.y);
}

void Paddle::Reset()
{
    mPosition.y = static_cast<float>(GetScreenHeight()) / 2 - paddleFixedHeight / 2;
    mScore = 0;
}

void Paddle::Draw() const
{
    DrawRectangleV(mPosition, mSize, mColor);
}

void Paddle::ProcessInput()
{
    if (IsKeyDown(mKeyUp) && mPosition.y > 0.0f)
    { // UP
        mPosition.y -= paddleMovementFactor * GetFrameTime();
    }
    if (IsKeyDown(mKeyDown) && mPosition.y + mSize.y < static_cast<float>(GetScreenHeight()))
    { // Down
        mPosition.y += paddleMovementFactor * GetFrameTime();
    }
}

void Paddle::UpdateScore()
{
    mScore++;
}
