#include <raylib.h>
#include <vector>
#include <algorithm>
#include <queue>

constexpr int rows = 40;
constexpr int cols = 30;
constexpr int cellSize = 30;
constexpr int cellDividerSize = 1;
constexpr int screenWidth = rows*cellSize;
constexpr int screenHeight = cols*cellSize;
int maxDist = 1;
enum CellTypes {
    Empty = 0,
    Wall = 1,
    Player = 2
};
struct Cell {int x, y;};

Cell PlayerGrid = {0,0};
std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
std::vector<std::vector<int>> distGrid(rows, std::vector<int>(cols));
Color GREY = {50,50,50};

void ResetGrid(){
    for (int i = 0; i<rows; i++){
        for (int j = 0; j<cols; j++){
            grid[i][j] = Empty;
        }
    }
    grid[PlayerGrid.x][PlayerGrid.y] = Player;

}
void BFSAlgorithm();

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
    BFSAlgorithm();
    return true;
}

void BFSAlgorithm(){
    maxDist = 1;
    for (int i = 0; i < rows; i ++){
        for (int j = 0; j < cols; j++){
            distGrid[i][j] = -1;
        }
    }

    std::queue<Cell> BFSqueue;
    int px = (int)PlayerGrid.x;
    int py = (int)PlayerGrid.y;

    distGrid[px][py] = 0;
    BFSqueue.push({PlayerGrid.x, PlayerGrid.y});

    int neighbours[4][2] = { {1,0}, {0,-1}, {-1,0}, {0,1}};

    while(!BFSqueue.empty()){
        Cell currentCell = BFSqueue.front();
        BFSqueue.pop();
        int currentX = currentCell.x;
        int currentY = currentCell.y;

        for (int i= 0; i < 4; i++){
            int nextX = currentX + neighbours[i][0];
            int nextY = currentY + neighbours[i][1];
            if((nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols)){
                continue;
            }
            if(distGrid[nextX][nextY] != -1 || grid[nextX][nextY] == Wall){
                continue;
            }
            distGrid[nextX][nextY] = distGrid[currentX][currentY] + 1;
            if(distGrid[nextX][nextY] > maxDist) maxDist = distGrid[nextX][nextY];
            BFSqueue.push({nextX, nextY});
        }
    }

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
                BFSAlgorithm();
            } else if (grid[mouseRow][mouseCol] == Empty){

                grid[mouseRow][mouseCol] = Wall;
                BFSAlgorithm();
            }
        } else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            int mouseRow = GetMousePosition().x /cellSize;
            int mouseCol = GetMousePosition().y /cellSize;
            if(mouseCol>=cols) mouseCol = cols-1;
            if(mouseRow>=rows) mouseRow = rows-1;
            if(mouseCol<0) mouseCol = 0;
            if(mouseRow < 0) mouseRow = 0;
            if(grid[mouseRow][mouseCol] == Empty){
                grid[PlayerGrid.x][PlayerGrid.y] = Empty;
                PlayerGrid = {mouseRow, mouseCol};
                grid[PlayerGrid.x][PlayerGrid.y] = Player;
                BFSAlgorithm();

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
                        
                        Color emptyColor = BLACK;
                        
                        if(distGrid[i][j] > 0){
                            float r = distGrid[i][j] / 30.0f;
                            if(r<0.0f) r = 0.0f;
                            if(r > 1.0f) r = 1.0f;
                            r = 255* (1-r);
                            emptyColor = {(unsigned char)r, 0, 0,255};
                        }
                        DrawRectangle(i*cellSize+cellDividerSize, j*cellSize+cellDividerSize, cellSize-2*cellDividerSize, cellSize-2*cellDividerSize, emptyColor);
                        DrawText(TextFormat("%d", distGrid[i][j]), i * cellSize, j* cellSize, 15, WHITE);
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