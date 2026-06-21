#include <raylib.h>

int main() 
{
    const Color darkGreen = {20, 160, 133, 255};
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    
    InitWindow(screenWidth, screenHeight, "Raylib Flow Field");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            ClearBackground(darkGreen);
            DrawCircle(400,300,20,WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}