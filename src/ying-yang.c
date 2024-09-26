#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

#define SW 900
#define GRIDNUM 9
#define CELL SW / GRIDNUM
#define GRAVITY 9.8f

int main(int argc, char *argv[]) {
  InitWindow(SW, SW, "ying yang ping pong");

  SetTargetFPS(60);

  // Build inital state
  bool(*grid)[GRIDNUM] = calloc(GRIDNUM * GRIDNUM, sizeof(bool));
  for (size_t x = 0; x < GRIDNUM; ++x) {
    for (size_t y = 0; y < GRIDNUM; ++y) {
      if (x + y < GRIDNUM)
        grid[x][y] = true;
    }
  }

  Vector2 ball = {10.0f, 10.0f};
  Vector2 vel = {10.0f, 10.0f};

  Vector2 grav = {0.0f, 0.0f};

  while (!WindowShouldClose()) {
    BeginDrawing();

    for (size_t x = 0; x < GRIDNUM; ++x) {
      for (size_t y = 0; y < GRIDNUM; ++y) {
        if (grid[x][y])
          DrawRectangle(x * CELL, y * CELL, CELL, CELL, WHITE);
        else
          DrawRectangle(x * CELL, y * CELL, CELL, CELL, BLACK);
      }
    }

    grav.y = GRAVITY * GetFrameTime();

    vel = Vector2Add(vel, grav);
    ball = Vector2Add(ball, vel);

    if (ball.y >= SW)
      vel = Vector2Reflect(vel, (Vector2){0, 1});
    if (ball.y <= 0)
      vel = Vector2Reflect(vel, (Vector2){0, -1});
    if (ball.x >= SW)
      vel = Vector2Reflect(vel, (Vector2){1, 0});
    if (ball.x <= 0)
      vel = Vector2Reflect(vel, (Vector2){-1, 0});

    DrawCircleV(ball, 10, RED);

    DrawFPS(10, 10);

    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
