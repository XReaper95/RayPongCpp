//
// Created by Luis on 13/04/2021.
//

#include "game.h"
#include "sounds.h"
#include "ui.h"

#define GAME_MAX_POINTS 5

static bool CheckWinner(const Paddle *p)
{
    if (p->m_score() >= GAME_MAX_POINTS)
    {
        SoundsPlayGameWon();
        return true;
    }

    return false;
}

static void ResetGame(Game *game)
{
    game->winner = nullptr;
    game->ball = Ball();
    game->leftPaddle.Reset(), game->rightPaddle.Reset(), SoundsStopScore();
    SoundsStopGameWon();
}

static void UpdateScore(Game *game)
{
    const float ballX = game->ball.m_position().x;
    const float ballRadius = game->ball.m_radius();
    const auto screenW = static_cast<float>(GetScreenWidth());
    bool scored = false;

    // right score
    if (ballX < 0 - ballRadius - 30)
    {
        scored = true;
        game->rightPaddle.UpdateScore();
        if (CheckWinner(&game->rightPaddle))
        {
            game->winner = &game->rightPaddle;
        }
    }

    // left score
    if (ballX > screenW + ballRadius + 30)
    {
        scored = true;
        game->leftPaddle.UpdateScore();
        if (CheckWinner(&game->leftPaddle))
        {
            game->winner = &game->leftPaddle;
        }
    }

    // reset ball position
    if (scored)
    {
        SoundsPlayScore();
        game->ball = Ball();
    }
}

Game GameCreate()
{
    return (Game){
        .leftPaddle = Paddle("Player 1", BLUE, true),
        .rightPaddle = Paddle("Player 2", RED, false),
        .ball = Ball()};
}

void GameProcessEvents(Game *game)
{
    game->leftPaddle.ProcessInput();
    game->rightPaddle.ProcessInput();

    game->ball.CheckBorderCollision();

    if (!game->ball.m_collide_with_paddle_enabled())
    {
        game->ball.CheckPaddleCollision(&game->leftPaddle);
        game->ball.CheckPaddleCollision(&game->rightPaddle);
    }

    game->ball.ProcessMovement();

    UpdateScore(game);
}

void GameDraw(const Game *game)
{
    UIDrawGameField();

    game->leftPaddle.Draw();
    game->rightPaddle.Draw();
    game->ball.Draw();
}

void GameReset(Game *game)
{
    if (GameHasWinner(game) && IsKeyPressed(KEY_SPACE))
    {
        ResetGame(game);
    }
}

void GameProcessWonState(Game *game)
{
    Paddle *p;

    if (game->winner == &game->leftPaddle)
    {
        p = &game->leftPaddle;
    }
    else
    {
        p = &game->rightPaddle;
    }

    UIDrawWinMessage(p);
    UIDrawResetMessage();
}

bool GameHasWinner(const Game *game)
{
    return game->winner != nullptr;
}
