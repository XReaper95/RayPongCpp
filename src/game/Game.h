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

    void processEvents();
    void processWonState() const;
    void draw() const;
    void reset();

    [[nodiscard]] bool hasWinner() const;

    [[nodiscard]] const Paddle& leftPaddle() const
    {
        return m_LeftPaddle;
    }

    [[nodiscard]] const Paddle& rightPaddle() const
    {
        return m_RightPaddle;
    }

private:
    void updateScore();
    void resetGame();
    void checkWinner(const Paddle& p);

    Paddle m_LeftPaddle;
    Paddle m_RightPaddle;
    Ball m_Ball;
    const Paddle* m_Winner = nullptr;
};

#endif // RAY_PONG_C_SRC_SYSTEM_GAME_H_
