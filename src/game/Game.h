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
        return m_leftPaddle;
    }

    const Paddle& GetRightPaddle() const
    {
        return m_rightPaddle;
    }

private:
    void UpdateScore();
    void ResetGame();
    void CheckWinner(const Paddle& p);

    Paddle m_leftPaddle;
    Paddle m_rightPaddle;
    Ball m_ball;
    const Paddle* m_winner = nullptr;
};

#endif // RAY_PONG_C_SRC_SYSTEM_GAME_H_
