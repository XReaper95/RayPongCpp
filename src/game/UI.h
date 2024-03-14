//
// Created by Luis on 19/04/2021.
//

#ifndef RAY_PONG_C_SRC_SYSTEM_UI_H_
#define RAY_PONG_C_SRC_SYSTEM_UI_H_

class Paddle;

namespace UI
{
void drawGameField();
void drawScoreBoard(const Paddle* left_paddle, const Paddle* right_paddle);
void drawWinMessage(const Paddle* p);
void drawResetMessage();
} // namespace UI

#endif // RAY_PONG_C_SRC_SYSTEM_UI_H_
