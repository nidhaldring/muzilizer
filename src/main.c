#include <raylib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WIDTH 800
#define HEIGHT 800

void drawWarning(const char *msg) {
  ClearBackground(RED);
  DrawText(msg, 20, HEIGHT / 2, 40, WHITE);
}

int main() {
  InitWindow(WIDTH, HEIGHT, "muzilizer");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    if (IsFileDropped()) {
      FilePathList files = LoadDroppedFiles();
      if (files.count > 1) {
        drawWarning("Only one file is supported for now!");
      } else {
        FILE *f = fopen(files.paths[0], "r");
        if (f == NULL) {
          char *msg = malloc(100);
          sprintf(msg, "File %s not found!", files.paths[0]);
          drawWarning(msg);
        }
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
