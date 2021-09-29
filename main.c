#include "raylib.h"
#include <stdlib.h>

#define PHYSAC_IMPLEMENTATION

#include "physac.h"

#define VELOCITY        0.5f


#define MAPWIDTH        18
#define MAPHEIGHT       10


int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "My Epic Game written in C! Haha yes");

    /* how this map works:
    1 denotes a block that you can't go into, and 0 is empty space. You can configure it with raylib's texture loader library to have multiple textures and stuff. */
    int map[MAPHEIGHT][MAPWIDTH] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1},
        {1,1,0,0,0,0,0,1,0,0,0,0,0,1,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
        {1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    int tileWidth = screenWidth / 80;
    int tileHeight = screenHeight / 80;

    PhysicsBody mapPhysics[MAPWIDTH][MAPHEIGHT];

    int x = 7;
    
    // populate the mapPhysics array with PhysicsBodies that I need
    for (int i = 0; i < MAPHEIGHT; ++i)
        for (int j = 0; j < MAPWIDTH; ++j) {
            if(map[i][j] == 1){
                mapPhysics[j][i] = CreatePhysicsBodyRectangle((Vector2) {tileHeight * j * x + ((tileHeight * x)/ 2), tileWidth * i * x + ((tileWidth * x)/2)}, tileWidth * x, tileHeight*x, 10);
                mapPhysics[j][i]->enabled = false;
            }
        }

    int bodiesCount;

    while(!WindowShouldClose()) {

        BeginDrawing();
            ClearBackground(RAYWHITE);
            // draw the map
            int i, j;
            for (i = 0; i < MAPWIDTH; i++) {
                for (j = 0; j < MAPHEIGHT; j++) {

                    if (map[j][i] == 1) {
                        DrawRectangle(tileWidth * i * x, tileHeight * j * x, tileWidth*x, tileHeight*x, BLACK);
                    }

                }
            }

            // Draw the physics objects as green lines
            bodiesCount = GetPhysicsBodiesCount();
            for (int i = 0; i < bodiesCount; i++)
            {
                PhysicsBody body = GetPhysicsBody(i);

                if (body != NULL)
                {
                    int vertexCount = GetPhysicsShapeVerticesCount(i);
                    for (int j = 0; j < vertexCount; j++)
                    {
                        // Get physics bodies shape vertices to draw lines
                        // Note: GetPhysicsShapeVertex() already calculates rotation transformations
                        Vector2 vertexA = GetPhysicsShapeVertex(body, j);

                        int jj = (((j + 1) < vertexCount) ? (j + 1) : 0);   // Get next vertex or first to close the shape
                        Vector2 vertexB = GetPhysicsShapeVertex(body, jj);

                        DrawLineV(vertexA, vertexB, GREEN);     // Draw a line between two vertex positions
                    }
                }
            }

            DrawText("I really hope this works", 10, 80, 18, RED);
            DrawFPS(10,120);
        
        EndDrawing();

    }

    CloseWindow();

    return 0;
}