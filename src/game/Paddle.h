//
// Created by Luis on 05/04/2021.
//

#ifndef RAYLIB_C_SRC_PLAYER_H_
#define RAYLIB_C_SRC_PLAYER_H_

#include "raylib.h"
#include <Color.hpp>
#include <Vector2.hpp>

#include <string>

class Paddle
{
public:
    Paddle(std::string_view name, raylib::Color color, bool is_left_paddle);

    void reset();
    void updateScore();
    void draw() const;
    void processInput();

private:
    std::string m_Name;

public:
    [[nodiscard]] const raylib::Vector2& position() const
    {
        return m_Position;
    }

    [[nodiscard]] const raylib::Vector2& size() const
    {
        return m_Size;
    }

    [[nodiscard]] const std::string& name() const
    {
        return m_Name;
    }

    [[nodiscard]] const raylib::Color& color() const
    {
        return m_Color;
    }

    [[nodiscard]] int score() const
    {
        return m_Score;
    }

private:
    raylib::Vector2 m_Position;
    const raylib::Vector2 m_Size;
    const raylib::Color m_Color;
    int m_Score;
    const KeyboardKey m_KeyUp;
    const KeyboardKey m_KeyDown;
};

#endif // RAYLIB_C_SRC_PLAYER_H_
