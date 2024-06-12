//
// Created by Luis on 19/04/2021.
//

#include "UI.h"
#include "Paddle.h"

#include "raylib-cpp.hpp"

#include <format>

void ui::DrawGameField()
{
    const raylib::Color fieldColor = LIGHTGRAY;

    // middle ring
    const raylib::Vector2 center = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    constexpr float innerRadius = 165.0f;
    constexpr float outerRadius = 175.0f;
    constexpr float startAngle = 0.0f;
    constexpr float endAngle = 360.0f;
    constexpr int segments = 0;
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, fieldColor);

    constexpr int linesThickness = 10;

    // middle circle
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, fieldColor);

    // middle line
    DrawRectangle(GetScreenWidth() / 2 - linesThickness / 2, 0, 10, GetScreenHeight(), fieldColor);

    // top line
    DrawRectangle(0, 0, GetScreenWidth(), linesThickness, fieldColor);

    // bottom line
    DrawRectangle(0, GetScreenHeight() - linesThickness, GetScreenWidth(), linesThickness, fieldColor);

    // left line
    DrawRectangle(0, 0, linesThickness, GetScreenHeight(), Fade(BLUE, 0.4f));

    // right line
    DrawRectangle(GetScreenWidth() - linesThickness, 0, linesThickness, GetScreenHeight(), Fade(RED, 0.4f));
}

void ui::DrawScoreBoard(const Paddle& leftPaddle, const Paddle& rightPaddle)
{
    constexpr int playerNameFontSize = 29;
    constexpr int scoreFontSize = 60;

    // right side
    raylib::DrawText(leftPaddle.Name(), 75, 50, playerNameFontSize, Fade(BLUE, 0.4f));

    std::string scoreAsText = std::format("{}", leftPaddle.Score());
    raylib::DrawText(scoreAsText, 110, 80, scoreFontSize, Fade(BLUE, 0.4f));

    // left side
    raylib::DrawText(
        rightPaddle.Name(),
        GetScreenWidth() - raylib::MeasureText(rightPaddle.Name(), playerNameFontSize) - 75,
        50,
        playerNameFontSize,
        Fade(RED, 0.4f));

    scoreAsText = std::format("{}", rightPaddle.Score());
    raylib::DrawText(
        scoreAsText,
        GetScreenWidth() - raylib::MeasureText(scoreAsText, scoreFontSize) - 110,
        80,
        scoreFontSize,
        raylib::Color::Red().Fade(0.4f));
}

void ui::DrawWinMessage(const Paddle& p)
{
    DrawText(
        std::format("Player \"{}\" won!!!", p.Name()).c_str(),
        110,
        GetScreenHeight() / 3,
        50,
        p.Color().Fade(0.55f));
}

void ui::DrawResetMessage()
{
    DrawText("Press SPACE to reset game or ESCAPE to exit", 40, 400, 30, Fade(WHITE, 0.55f));
}
