#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SDL_FLAGS SDL_INIT_VIDEO
#define WINDOW_TITLE "kebabb"
#define INIT_WINDOW_WIDTH 800
#define INIT_WINDOW_HEIGHT 600

typedef struct Game {
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool game_should_stop;
} Game;

bool game_init_sdl(Game *game);
void game_quit(Game *game);

int main() {
  bool exit_status = EXIT_FAILURE;
  Game kebabb = {0};

  if (game_init_sdl(&kebabb)) {
    exit_status = EXIT_SUCCESS;
  }

  while (!kebabb.game_should_stop) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_EVENT_QUIT:
        kebabb.game_should_stop = true;
        break;
      }
    };
  }

  game_quit(&kebabb);

  return exit_status;
}

bool game_init_sdl(Game *game) {
  if (!SDL_Init(SDL_FLAGS)) {
    fprintf(stderr, "Failed to initialize SDL3 with error: %s\n",
            SDL_GetError());
    return false;
  }
  game->window =
      SDL_CreateWindow(WINDOW_TITLE, INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, 0);
  if (!game->window) {
    fprintf(stderr, "Failed to initialize Window with error: %s\n",
            SDL_GetError());
    return false;
  }
  game->renderer = SDL_CreateRenderer(game->window, NULL);
  if (!game->renderer) {
    fprintf(stderr, "Failed to initialize Renderer with error: %s\n",
            SDL_GetError());
    return false;
  }
  game->game_should_stop = false;
  return true;
}

void game_quit(Game *game) {
  SDL_DestroyRenderer(game->renderer);
  SDL_DestroyWindow(game->window);
  SDL_Quit();
}
