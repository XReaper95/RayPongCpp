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
    Paddle(std::string_view name, raylib::Color color, bool isLeftPaddle);

    void Reset();
    void UpdateScore();
    void Draw() const;
    void ProcessInput();

private:
    std::string mName;

public:
    [[nodiscard]] const raylib::Vector2 &m_position() const
    {
        return mPosition;
    }

    [[nodiscard]] const raylib::Vector2 &m_size() const
    {
        return mSize;
    }

    [[nodiscard]] const std::string &m_name() const
    {
        return mName;
    }

    [[nodiscard]] const raylib::Color &m_color() const
    {
        return mColor;
    }

    [[nodiscard]] int m_score() const
    {
        return mScore;
    }

private:
    raylib::Vector2 mPosition;
    const raylib::Vector2 mSize;
    const raylib::Color mColor;
    int mScore;
    const KeyboardKey mKeyUp;
    const KeyboardKey mKeyDown;
};

#endif // RAYLIB_C_SRC_PLAYER_H_
