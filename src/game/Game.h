//
// Created by Luis on 13/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_GAME_H_
#define RAY_PONG_C_SRC_SYSTEM_GAME_H_

#include "Ball.h"
#include "Paddle.h"

class Game
{
public:
    Game();

    void ProcessEvents();
    void ProcessWonState() const;
    void Draw() const;
    void Reset();

    bool HasWinner() const;

    const Paddle& GetLeftPaddle() const
    {
        return m_LeftPaddle;
    }

    const Paddle& GetRightPaddle() const
    {
        return m_RightPaddle;
    }

private:
    void UpdateScore();
    void ResetGame();
    void CheckWinner(const Paddle& p);

    Paddle m_LeftPaddle;
    Paddle m_RightPaddle;
    Ball m_Ball;
    const Paddle* m_Winner = nullptr;
};

#endif // RAY_PONG_C_SRC_SYSTEM_GAME_H_
