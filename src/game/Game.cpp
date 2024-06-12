//
// Created by Luis on 13/04/2021.
//

#include "Game.h"
#include "SoundManager.h"
#include "UI.h"

constexpr int kMaxGamePoints = 1;

Game::Game()
    : m_leftPaddle{"Player 1", BLUE, true},
      m_rightPaddle{"Player 2", RED, false}
{
}

void Game::ResetGame()
{
    m_winner = nullptr;
    m_ball = Ball();
    m_leftPaddle.Reset();
    m_rightPaddle.Reset();
    SoundManager::Instance()->StopScore();
    SoundManager::Instance()->StopGameWon();
}

void Game::UpdateScore()
{
    const float ballX = m_ball.GetPosition().x;
    const float ballRadius = m_ball.GetRadius();
    const auto screenW = static_cast<float>(GetScreenWidth());
    bool scored = false;

    // right score
    if (ballX < 0 - ballRadius - 30)
    {
        scored = true;
        m_rightPaddle.UpdateScore();
        CheckWinner(m_rightPaddle);
    }

    // left score
    if (ballX > screenW + ballRadius + 30)
    {
        scored = true;
        m_leftPaddle.UpdateScore();
        CheckWinner(m_leftPaddle);
    }

    // reset ball position
    if (scored)
    {
        SoundManager::Instance()->PlayScore();
        m_ball = Ball();
    }
}

void Game::CheckWinner(const Paddle& p)
{
    if (p.Score() >= kMaxGamePoints)
    {
        m_winner = &p;
        SoundManager::Instance()->PlayGameWon();
    }
}

void Game::ProcessEvents()
{
    m_leftPaddle.ProcessInput();
    m_rightPaddle.ProcessInput();

    m_ball.CheckBorderCollision();

    if (!m_ball.IsCollisionWithPaddleEnabled())
    {
        m_ball.CheckPaddleCollision(m_leftPaddle);
        m_ball.CheckPaddleCollision(m_rightPaddle);
    }

    m_ball.ProcessMovement();

    UpdateScore();
}

void Game::Draw() const
{
    ui::DrawGameField();

    m_leftPaddle.Draw();
    m_rightPaddle.Draw();
    m_ball.Draw();
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
    const Paddle& p = m_winner == &m_leftPaddle ? m_leftPaddle : m_rightPaddle;

    ui::DrawWinMessage(p);
    ui::DrawResetMessage();
}

bool Game::HasWinner() const
{
    return m_winner != nullptr;
}
