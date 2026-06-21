#include <raylib.h>
#include <vector>
constexpr int rows = 40;
constexpr int cols = 30;
constexpr int cellSize = 20;
constexpr int cellDividerSize = 1;
constexpr int screenWidth = rows*cellSize;
constexpr int screenHeight = cols*cellSize;

enum Cell {
    Empty = 0,
    Wall = 1,
    Player = 2
};
Vector2 PlayerGrid = {0,0};
std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
Color GREY = {50,50,50};

void ResetGrid(){
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            grid[i][j] = Empty;
        }
    }
    grid[PlayerGrid.x][PlayerGrid.y] = Player;

}

bool MovePlayer(int mrows, int mcols){
    if((PlayerGrid.x + mrows < 0) || (PlayerGrid.x + mrows + 1 > rows) || (PlayerGrid.y + mcols < 0) || (PlayerGrid.y + mcols + 1 > cols)){
        return false;
    }
    if(grid[PlayerGrid.x+mrows][PlayerGrid.y+mcols] != Empty) {
        return false;
    }
    grid[PlayerGrid.x][PlayerGrid.y] = Empty;
    PlayerGrid.x += mrows;
    PlayerGrid.y += mcols;
    grid[PlayerGrid.x][PlayerGrid.y] = Player;
    return true;
}

int main() 
{
    
    
    ResetGrid();
    
    InitWindow(screenWidth, screenHeight, "Raylib Flow Field");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            int mouseRow = GetMousePosition().x /cellSize;
            int mouseCol = GetMousePosition().y /cellSize;
            if(grid[mouseRow][mouseCol] == Wall){
                grid[mouseRow][mouseCol] = Empty;
            } else if (grid[mouseRow][mouseCol] == Empty){
                grid[mouseRow][mouseCol] = Wall;
            }
        } else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            int mouseRow = GetMousePosition().x /cellSize;
            int mouseCol = GetMousePosition().y /cellSize;
            if(grid[mouseRow][mouseCol] == Empty){
                grid[PlayerGrid.x][PlayerGrid.y] = Empty;
                PlayerGrid = {(float)mouseRow, (float)mouseCol};
                grid[PlayerGrid.x][PlayerGrid.y] = Player;

            }
        }
        if(IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_A)){
            MovePlayer(-1,0);
        }
        if(IsKeyPressed(KEY_RIGHT)||IsKeyPressed(KEY_D)){
            MovePlayer(1,0);
        }
        if(IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_W)){
            MovePlayer(0, -1);
        }
        if(IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_S)){
            MovePlayer(0,1);
        }

        BeginDrawing();
            ClearBackground(GREY);
            for (int i = 0; i<rows; i++){
                for (int j = 0; j<cols; j++){
                    if(grid[i][j] == Empty){
                        DrawRectangle(i*cellSize+cellDividerSize, j*cellSize+cellDividerSize, cellSize-2*cellDividerSize, cellSize-2*cellDividerSize, BLACK);
                    } else if (grid[i][j] == Wall){
                        DrawRectangle(i*cellSize+cellDividerSize, j*cellSize+cellDividerSize, cellSize-2*cellDividerSize, cellSize-2*cellDividerSize, BLUE);
                    } else if (grid[i][j] == Player){
                        DrawRectangle(i*cellSize+cellDividerSize, j*cellSize+cellDividerSize, cellSize-2*cellDividerSize, cellSize-2*cellDividerSize, WHITE);
                    }
                }
            }
        EndDrawing();
    }
    
    CloseWindow();
}