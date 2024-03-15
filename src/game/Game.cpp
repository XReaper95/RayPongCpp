//
// Created by Luis on 13/04/2021.
//

#include "Game.h"
#include "SoundManager.h"
#include "UI.h"

constexpr int kMaxGamePoints = 1;

Game::Game()
    : m_LeftPaddle{"Player 1", BLUE, true},
      m_RightPaddle{"Player 2", RED, false}
{
}

void Game::ResetGame()
{
    m_Winner = nullptr;
    m_Ball = Ball();
    m_LeftPaddle.Reset();
    m_RightPaddle.Reset();
    SoundManager::Instance()->StopScore();
    SoundManager::Instance()->StopGameWon();
}

void Game::UpdateScore()
{
    const float ball_x = m_Ball.GetPosition().x;
    const float ball_radius = m_Ball.GetRadius();
    const auto screen_w = static_cast<float>(GetScreenWidth());
    bool scored = false;

    // right score
    if (ball_x < 0 - ball_radius - 30)
    {
        scored = true;
        m_RightPaddle.UpdateScore();
        CheckWinner(m_RightPaddle);
    }

    // left score
    if (ball_x > screen_w + ball_radius + 30)
    {
        scored = true;
        m_LeftPaddle.UpdateScore();
        CheckWinner(m_LeftPaddle);
    }

    // reset ball position
    if (scored)
    {
        SoundManager::Instance()->PlayScore();
        m_Ball = Ball();
    }
}

void Game::CheckWinner(const Paddle& p)
{
    if (p.Score() >= kMaxGamePoints)
    {
        m_Winner = &p;
        SoundManager::Instance()->PlayGameWon();
    }
}

void Game::ProcessEvents()
{
    m_LeftPaddle.ProcessInput();
    m_RightPaddle.ProcessInput();

    m_Ball.CheckBorderCollision();

    if (!m_Ball.IsCollisionWithPaddleEnabled())
    {
        m_Ball.CheckPaddleCollision(m_LeftPaddle);
        m_Ball.CheckPaddleCollision(m_RightPaddle);
    }

    m_Ball.ProcessMovement();

    UpdateScore();
}

void Game::Draw() const
{
    ui::DrawGameField();

    m_LeftPaddle.Draw();
    m_RightPaddle.Draw();
    m_Ball.Draw();
}

void Game::Reset()
{
    if (HasWinner() && IsKeyPressed(KEY_SPACE))
    {
        ResetGame();
    }
}

void Game::ProcessWonState() const
{
    const Paddle& p = m_Winner == &m_LeftPaddle ? m_LeftPaddle : m_RightPaddle;

    ui::DrawWinMessage(p);
    ui::DrawResetMessage();
}

bool Game::HasWinner() const
{
    return m_Winner != nullptr;
}
