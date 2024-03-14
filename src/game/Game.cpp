//
// Created by Luis on 13/04/2021.
//

#include "Game.h"
#include "SoundManager.h"
#include "UI.h"

constexpr int maxGamePoints = 5;

Game::Game()
    : m_LeftPaddle{"Player 1", BLUE, true},
      m_RightPaddle{"Player 2", RED, false}
{
}

void Game::resetGame()
{
    m_Winner = nullptr;
    m_Ball = Ball();
    m_LeftPaddle.reset();
    m_RightPaddle.reset();
    SoundManager::instance()->stopScore();
    SoundManager::instance()->stopGameWon();
}

void Game::updateScore()
{
    const float ball_x = m_Ball.position().x;
    const float ball_radius = m_Ball.radius();
    const auto screen_w = static_cast<float>(GetScreenWidth());
    bool scored = false;

    // right score
    if (ball_x < 0 - ball_radius - 30)
    {
        scored = true;
        m_RightPaddle.updateScore();
        checkWinner(m_RightPaddle);
    }

    // left score
    if (ball_x > screen_w + ball_radius + 30)
    {
        scored = true;
        m_LeftPaddle.updateScore();
        checkWinner(m_LeftPaddle);
    }

    // reset ball position
    if (scored)
    {
        SoundManager::instance()->playScore();
        m_Ball = Ball();
    }
}

void Game::checkWinner(const Paddle& p)
{
    if (p.score() >= maxGamePoints)
    {
        m_Winner = &p;
        SoundManager::instance()->playGameWon();
    }
}

void Game::processEvents()
{
    m_LeftPaddle.processInput();
    m_RightPaddle.processInput();

    m_Ball.checkBorderCollision();

    if (!m_Ball.collideWithPPaddleEnabled())
    {
        m_Ball.checkPaddleCollision(m_LeftPaddle);
        m_Ball.checkPaddleCollision(m_RightPaddle);
    }

    m_Ball.processMovement();

    updateScore();
}

void Game::draw() const
{
    UI::drawGameField();

    m_LeftPaddle.draw();
    m_RightPaddle.draw();
    m_Ball.draw();
}

void Game::reset()
{
    if (hasWinner() && IsKeyPressed(KEY_SPACE))
    {
        resetGame();
    }
}

void Game::processWonState() const
{
    const Paddle& p = m_Winner == &m_LeftPaddle ? m_LeftPaddle : rightPaddle();

    UI::drawWinMessage(p);
    UI::drawResetMessage();
}

bool Game::hasWinner() const
{
    return m_Winner != nullptr;
}
