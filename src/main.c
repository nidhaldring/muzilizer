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
  char *loadedFile = NULL;

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

          if (!loadedFile || strlen(files.paths[0]) > strlen(loadedFile)) {
            void *tmp = realloc(loadedFile, strlen(files.paths[0]) + 1);
            if (tmp == NULL) {
              fprintf(stderr, "Memory Allocation error: realloc failed!\n");
              exit(EXIT_FAILURE);
            }
            loadedFile = tmp;
          }

          strcpy(loadedFile, files.paths[0]);
          printf("saved file = %s\n", loadedFile);
        }
      }

      UnloadDroppedFiles(files);
    }

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
