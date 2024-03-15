#include "game/Game.h"
#include "game/SoundManager.h"
#include "game/UI.h"

#include "raylib-cpp.hpp"

#include <format>

int main()
{
    // CONFIGURATION
    constexpr int kScreenWidth = 800;
    constexpr int kScreenHeight = 600;
    constexpr int kTargetFps = 60;
    const auto kWindowsTitle = "Pong with Raylib and C++";

    // INITIALIZATION
    SetTraceLogLevel(LOG_INFO);

    auto window = raylib::Window{kScreenWidth, kScreenHeight, kWindowsTitle, FLAG_MSAA_4X_HINT};
    window.SetTargetFPS(kTargetFps);

    // load all the sounds, Note: loading the sounds and instantiating the singleton
    // should be two separate operations but since there is no resource manager just let it be
    SoundManager::Instance();

    // SHADERS
    raylib::RenderTexture2D render_target{kScreenWidth, kScreenHeight};
    raylib::Shader shader{nullptr, "resources/crt.fs"};
    const auto background_color{raylib::Color::FromHSV(207, 0.47f, 0.15f)};

    Game game;
    //
    // // Main game loop
    while (!window.ShouldClose()) // Detect window close button or ESC key
    {
        // UPDATE
        window.SetTitle(std::format("{} FPS - {}", kWindowsTitle, window.GetFPS()));

        if (!game.HasWinner())
        {
            game.ProcessEvents();
        }
        else
        {
            game.Reset();
        }

        // DRAW
        window.BeginDrawing();
        render_target.BeginMode();
        window.ClearBackground(background_color);
        game.Draw();
        render_target.EndMode();

        shader.BeginMode();
        render_target.GetTexture().Draw(0, 0, WHITE);
        shader.EndMode();

        ui::DrawScoreBoard(game.GetLeftPaddle(), game.GetRightPaddle());

        if (game.HasWinner())
        {
            game.ProcessWonState();
        }

        window.EndDrawing();
    }

    return 0;
}
