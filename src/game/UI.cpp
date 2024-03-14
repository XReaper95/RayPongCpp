//
// Created by Luis on 19/04/2021.
//

#include "UI.h"
#include "Paddle.h"

#include "raylib-cpp.hpp"

#include <format>

void UI::drawGameField()
{
    const raylib::Color field_color = LIGHTGRAY;

    // middle ring
    const Vector2 center = {static_cast<float>(GetScreenWidth()) / 2, static_cast<float>(GetScreenHeight()) / 2};
    constexpr float inner_radius = 165.0f;
    constexpr float outer_radius = 175.0f;
    constexpr float start_angle = 0.0f;
    constexpr float end_angle = 360.0f;
    constexpr int segments = 0;
    DrawRing(center, inner_radius, outer_radius, start_angle, end_angle, segments, field_color);

    constexpr int lines_thickness = 10;

    // middle circle
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 10, field_color);

    // middle line
    DrawRectangle(GetScreenWidth() / 2 - lines_thickness / 2, 0, 10, GetScreenHeight(), field_color);

    // top line
    DrawRectangle(0, 0, GetScreenWidth(), lines_thickness, field_color);

    // bottom line
    DrawRectangle(0, GetScreenHeight() - lines_thickness, GetScreenWidth(), lines_thickness, field_color);

    // left line
    DrawRectangle(0, 0, lines_thickness, GetScreenHeight(), Fade(BLUE, 0.4f));

    // right line
    DrawRectangle(GetScreenWidth() - lines_thickness, 0, lines_thickness, GetScreenHeight(), Fade(RED, 0.4f));
}

void UI::drawScoreBoard(const Paddle& left_paddle, const Paddle& right_paddle)
{
    constexpr int player_name_font_size = 29;
    constexpr int score_font_size = 60;

    // right side
    DrawText(left_paddle.name().c_str(), 75, 50, player_name_font_size, Fade(BLUE, 0.4f));

    std::string score_as_text = std::format("{}", left_paddle.score());
    DrawText(score_as_text.c_str(), 110, 80, score_font_size, Fade(BLUE, 0.4f));

    // left side
    DrawText(
        right_paddle.name().c_str(),
        GetScreenWidth() - MeasureText(right_paddle.name().c_str(), player_name_font_size) - 75,
        50,
        player_name_font_size,
        Fade(RED, 0.4f));

    score_as_text = std::format("{}", right_paddle.score());
    DrawText(
        score_as_text.c_str(),
        GetScreenWidth() - MeasureText(score_as_text.c_str(), score_font_size) - 110,
        80,
        score_font_size,
        Fade(RED, 0.4f));
}

void UI::drawWinMessage(const Paddle& p)
{
    DrawText(
        std::format("Player \"{}\" won!!!", p.name()).c_str(),
        110,
        GetScreenHeight() / 3,
        50,
        Fade(p.color(), 0.55f));
}

void UI::drawResetMessage()
{
    DrawText("Press SPACE to reset game or ESCAPE to exit", 40, 400, 30, Fade(WHITE, 0.55f));
}
