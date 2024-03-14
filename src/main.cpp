#include "game/SoundManager.h"
#include "game/UI.h"
#include "game/game.h"
#include "raylib.h"

int main() {
    // CONFIGURATION
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    constexpr int targetFPS = 60;
    const auto windowsTitle = "Pong with Raylib";

    // INITIALIZATION
    SetTraceLogLevel(LOG_INFO);
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, windowsTitle);
    SetTargetFPS(targetFPS); // Set desired framerate (frames-per-second)
    InitAudioDevice();
    SoundManager::instance(); // load all the sounds

    // SHADERS
    const RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    const Shader shader = LoadShader(0, "resources/crt.fs");
    const Color backgroundColor = ColorFromHSV(207, 0.47f, 0.15f);

    Game game = GameCreate();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // UPDATE
        SetWindowTitle(TextFormat("%s FPS - %d", windowsTitle, GetFPS()));

        // EVENTS
        if (!GameHasWinner(&game)) {
            GameProcessEvents(&game);
        } else {
            GameReset(&game);
        }

        ClearBackground(backgroundColor);

        // DRAW
        BeginDrawing();
        BeginTextureMode(target);
        ClearBackground(backgroundColor);
        GameDraw(&game);
        EndTextureMode();


        BeginShaderMode(shader);
        DrawTextureRec(target.texture,
                       (Rectangle) {0, 0, (float) target.texture.width, (float) -target.texture.height},
                       (Vector2) {0, 0},
                       WHITE);
        EndShaderMode();

        UI::drawScoreBoard(&game.leftPaddle, &game.rightPaddle);

        if (GameHasWinner(&game)) {
            GameProcessWonState(&game);
        }

        EndDrawing();
    }

    // DE-INITIALIZATION
    CloseAudioDevice();
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}
