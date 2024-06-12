//
// Created by Luis on 19/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_UI_H_
#define RAY_PONG_C_SRC_SYSTEM_UI_H_

class Paddle;

namespace ui
{
void DrawGameField();
void DrawScoreBoard(const Paddle& leftPaddle, const Paddle& rightPaddle);
void DrawWinMessage(const Paddle& p);
void DrawResetMessage();
} // namespace UI

#endif // RAY_PONG_C_SRC_SYSTEM_UI_H_
