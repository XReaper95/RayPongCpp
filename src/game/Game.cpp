//
// Created by Luis on 13/04/2021.
//

#include "game.h"
#include "SoundManager.h"
#include "UI.h"

#define GAME_MAX_POINTS 5

static bool CheckWinner(const Paddle *p)
{
    if (p->score() >= GAME_MAX_POINTS)
    {
        SoundManager::instance()->playGameWon();
        return true;
    }

    return false;
}

static void ResetGame(Game *game)
{
    game->winner = nullptr;
    game->ball = Ball();
    game->leftPaddle.reset();
    game->rightPaddle.reset();
    SoundManager::instance()->stopScore();
    SoundManager::instance()->stopGameWon();
}

static void UpdateScore(Game *game)
{
    const float ballX = game->ball.position().x;
    const float ballRadius = game->ball.radius();
    const auto screenW = static_cast<float>(GetScreenWidth());
    bool scored = false;

    // right score
    if (ballX < 0 - ballRadius - 30)
    {
        scored = true;
        game->rightPaddle.updateScore();
        if (CheckWinner(&game->rightPaddle))
        {
            game->winner = &game->rightPaddle;
        }
    }

    // left score
    if (ballX > screenW + ballRadius + 30)
    {
        scored = true;
        game->leftPaddle.updateScore();
        if (CheckWinner(&game->leftPaddle))
        {
            game->winner = &game->leftPaddle;
        }
    }

    // reset ball position
    if (scored)
    {
        SoundManager::instance()->playScore();
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
    game->leftPaddle.processInput();
    game->rightPaddle.processInput();

    game->ball.checkBorderCollision();

    if (!game->ball.collideWithPPaddleEnabled())
    {
        game->ball.checkPaddleCollision(&game->leftPaddle);
        game->ball.checkPaddleCollision(&game->rightPaddle);
    }

    game->ball.processMovement();

    UpdateScore(game);
}

void GameDraw(const Game *game)
{
    UI::drawGameField();

    game->leftPaddle.draw();
    game->rightPaddle.draw();
    game->ball.draw();
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

    UI::drawWinMessage(p);
    UI::drawResetMessage();
}

bool GameHasWinner(const Game *game)
{
    return game->winner != nullptr;
}
