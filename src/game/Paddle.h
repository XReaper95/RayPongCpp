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
    Paddle(std::string_view name, raylib::Color color, bool is_left_paddle);

    void Reset();
    void UpdateScore();
    void Draw() const;
    void ProcessInput();

private:
    std::string m_Name;

public:
    const raylib::Vector2& GetPosition() const
    {
        return m_Position;
    }

    const raylib::Vector2& GetSize() const
    {
        return m_Size;
    }

    const std::string& Name() const
    {
        return m_Name;
    }

    const raylib::Color& Color() const
    {
        return m_Color;
    }

    int Score() const
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
