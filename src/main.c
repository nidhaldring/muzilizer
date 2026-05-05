#include <raylib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 800

void drawWarning(const char *msg) {
  ClearBackground(RED);
  DrawText(msg, 20, HEIGHT / 2, 40, WHITE);
}

int main() {
  InitWindow(WIDTH, HEIGHT, "muzilizer");
  SetTargetFPS(60);
  InitAudioDevice();
  char *loadedFile = malloc(100);

  while (!WindowShouldClose()) {
    BeginDrawing();

    ClearBackground(BLACK);

    if (IsFileDropped()) {
      FilePathList files = LoadDroppedFiles();
      if (files.count > 1) {
        drawWarning("Only one file is supported for now!");
      } else {
        if (!loadedFile || strcmp(loadedFile, files.paths[0]) != 0) {
          printf("loaded file = %s\n", files.paths[0]);
          Sound s = LoadSound(files.paths[0]);
          strcpy(loadedFile, files.paths[0]);
        }
      }

      UnloadDroppedFiles(files);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
