#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>

// THIS WILL BE SET AUTOMATICALL BY NOOB
// #define PLATFORM_WEB

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define SW 900
#define GRIDNUM 10
#define CELL ceil(SW / (1.0f * GRIDNUM))
#define GRAVITY 0.0f
#define BALLS 2

typedef struct ball {
  Vector2 position;
  Vector2 velocity;
  bool color;
} Ball;

void UpdateDrawFrame(void);

float fsign(float x) {
  if (x > 0.0f)
    return 1;
  return -1;
}

bool (*grid)[GRIDNUM];
Ball *balls;
Vector2 grav;

int main(int argc, char *argv[]) {
  // Build inital state
  grid = malloc(GRIDNUM * GRIDNUM * sizeof(bool));
  for (size_t x = 0; x < GRIDNUM; ++x) {
    for (size_t y = 0; y < GRIDNUM; ++y) {
      grid[x][y] = x + y < GRIDNUM;
    }
  }

  balls = (Ball *)malloc(BALLS * sizeof(Ball));
  balls[0] = (Ball){10.0f, 10.0f, 10.0f, 10.0f, true};
  balls[1] = (Ball){SW - 10.0f, SW - 10.0f, -10.0f, -10.0f, false};

  grav = (Vector2){0.0f, 0.0f};

  InitWindow(SW, SW, "ying yang ping pong");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();

  free(balls);
  free(grid);

  return EXIT_SUCCESS;
}

void UpdateDrawFrame() {
  BeginDrawing();

  for (size_t x = 0; x < GRIDNUM; ++x) {
    for (size_t y = 0; y < GRIDNUM; ++y) {
      // Grid Collisions
      Rectangle rec = {x * CELL, y * CELL, CELL, CELL};
      for (size_t i = 0; i < BALLS; ++i) {
        if (grid[x][y] != balls[i].color && CheckCollisionPointRec(balls[i].position, rec)) {
          if (fabs(balls[i].velocity.x) > fabs(balls[i].velocity.y))
            balls[i].velocity = Vector2Reflect(balls[i].velocity, (Vector2){1.0f * fsign(balls[i].velocity.x), 0.0f});
          else
            balls[i].velocity = Vector2Reflect(balls[i].velocity, (Vector2){0.0f, 1.0f * fsign(balls[i].velocity.x)});
          grid[x][y] = balls[i].color;
        }
      }

      // Grid Rendering
      if (grid[x][y])
        DrawRectangle(x * CELL, y * CELL, CELL, CELL, WHITE);
      else
        DrawRectangle(x * CELL, y * CELL, CELL, CELL, BLACK);
    }
  }

  // Side Collisions and Rendering
  grav.y = GRAVITY * GetFrameTime();

  for (size_t i = 0; i < BALLS; ++i) {
    balls[i].velocity = Vector2Add(balls[i].velocity, grav);
    balls[i].position = Vector2Add(balls[i].position, balls[i].velocity);

    if (balls[i].position.y >= SW)
      balls[i].velocity = Vector2Reflect(balls[i].velocity, (Vector2){0, 1});
    if (balls[i].position.y <= 0)
      balls[i].velocity = Vector2Reflect(balls[i].velocity, (Vector2){0, -1});
    if (balls[i].position.x >= SW)
      balls[i].velocity = Vector2Reflect(balls[i].velocity, (Vector2){1, 0});
    if (balls[i].position.x <= 0)
      balls[i].velocity = Vector2Reflect(balls[i].velocity, (Vector2){-1, 0});

    if (balls[i].color)
      DrawCircleV(balls[i].position, 10, BLACK);
    else
      DrawCircleV(balls[i].position, 10, WHITE);
  }

  DrawFPS(10, 10);

  EndDrawing();
}
