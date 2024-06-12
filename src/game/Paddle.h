//
// Created by Luis on 05/04/2021.
//

#ifndef RAYLIB_C_SRC_PLAYER_H_
#define RAYLIB_C_SRC_PLAYER_H_

#include "raylib-cpp.hpp"

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
    std::string m_name;

public:
    const raylib::Vector2& GetPosition() const
    {
        return m_position;
    }

    const raylib::Vector2& GetSize() const
    {
        return m_size;
    }

    const std::string& Name() const
    {
        return m_name;
    }

    const raylib::Color& Color() const
    {
        return m_color;
    }

    int Score() const
    {
        return m_score;
    }

private:
    raylib::Vector2 m_position;
    const raylib::Vector2 m_size;
    const raylib::Color m_color;
    int m_score;
    const KeyboardKey m_keyUp;
    const KeyboardKey m_keyDown;
};

#endif // RAYLIB_C_SRC_PLAYER_H_
